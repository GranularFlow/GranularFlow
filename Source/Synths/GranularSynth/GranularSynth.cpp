/*
  ==============================================================================

    GranularSynth.cpp
    Created: 30 Oct 2022 2:15:25pm
    Author:  honza

  ==============================================================================
*/

#include "GranularSynth.h"

GranularSynth::GranularSynth()
{
    initGui();
    addListeners();
    initAudioSamples(getNumTotalSamples());        
}

GranularSynth::~GranularSynth()
{
    removeListeners();
    audioSamples.clear();
    if (fileChooser != nullptr)
    {
        fileChooser = nullptr;
    }
    if (ringBufferPntr != nullptr)
    {
        delete ringBufferPntr;
        ringBufferPntr = nullptr;
    }
}

void GranularSynth::initGui()
{
    addAndMakeVisible(granularSettings, 0);
    addAndMakeVisible(granularVisualiser, 1);    
}

inline void GranularSynth::paint(Graphics& g)
{
    // Background
    g.fillAll(C_DARK);
    Utils::paintLogo(g);
}

void GranularSynth::resized()
{
   
    // Top GranularSynthSettings
    int8 topSettingsHeight = 50;

    granularSettings.setBounds(getLocalBounds().withTrimmedBottom(getHeight() - topSettingsHeight));

    // Players
    for (int i = 0; i < granularPlayers.size(); i++)
    {
        granularPlayers[i]->setBounds(getLocalBounds().withTrimmedTop(topSettingsHeight));
    }

    // AudioVisualiser
    granularVisualiser.setBounds(getLocalBounds().withTrimmedTop(topSettingsHeight).withTrimmedBottom(((getHeight() - topSettingsHeight ) / 2) + (CURSOR_BALL_RADIUS * 2.5) ));
}

void GranularSynth::addListeners() {
    granularSettings.openAudioButton.addListener(this);
    granularSettings.openBufferButton.addListener(this);
    granularSettings.timeLengthNum.slider.addListener(this);
    granularSettings.playerSelectNum.slider.addListener(this);
    granularSettings.playerCountNum.slider.addListener(this);
}

void GranularSynth::removeListeners(){
    granularSettings.timeLengthNum.slider.removeListener(this);
    granularSettings.openAudioButton.removeListener(this);
    granularSettings.playerSelectNum.slider.removeListener(this);
    granularSettings.playerCountNum.slider.removeListener(this);
}

void GranularSynth::handleMidi(MidiBuffer& midiMessages)
{
    MidiBuffer::Iterator iter(midiMessages);
    MidiMessage midiMsg;
    int midiPos;
    iter.getNextEvent(midiMsg, midiPos);
    if (midiMsg.isNoteOn() && midiMsg.getNoteNumber() != lastMidiNote)
    {
        midiNoteOn = true;
        lastMidiNote = midiMsg.getNoteNumber();
        increment = std::powf(2.f, (midiMsg.getNoteNumber() - 69.f) / 12.f);
    }
    else if (midiMsg.isNoteOff() && midiMsg.getNoteNumber() == lastMidiNote)
    {
        midiNoteOn = false;
        lastMidiNote = -1;
        increment = 1.0f;
    }
}

void GranularSynth::loadAudioFromFile(File file)
{   
    DBG("loadAudioFromFile " << file.getFullPathName());

    AudioLoad audioLoad;

    audioSamples.setSize(2, getNumTotalSamples());

    // DOCS: The contents of the buffer will initially be undefined, so use clear() to set all the samples to zero.        
    audioSamples.clear();
   
    audioLoad.fillBuffer(audioSamples, getNumTotalSamples(), file);    

    // Push into visualiser only one channel
    granularVisualiser.setWaveForm(audioSamples);

    // Check to start playing
    waveFormWasSet = true;

    // Get rid off audioLoader - otherwise causes crashes and leaks
    audioLoad.clear();
}

void GranularSynth::loadAudioIntoSamples()
{    
    File audioFile;

    fileChooser = std::make_unique<juce::FileChooser>("Select a Wave file...", juce::File{}, "*.wav");

    fileChooser->launchAsync({}, [this](const FileChooser& fc) {
        loadAudioFromFile(fc.getResult());
    });
}

int GranularSynth::getNumTotalSamples() {
    // how long i want to play * current sample rate = numberOfSamples
    // example 48 khz * 3s = 144 000 samples;
    return maxPlayTime * sampleRate;
}

void GranularSynth::initAudioSamples(int numberToInit) {
    AudioBuffer<float> tmpBuffer;
    if (waveFormWasSet)
    {        
        tmpBuffer.makeCopyOf(audioSamples);
    }

    audioSamples.setSize(2, numberToInit);
    audioSamples.clear();

    if (waveFormWasSet)
    {
        int minSamples = jmin(numberToInit, audioSamples.getNumSamples());
        //int destChannel, int destStartSample, const AudioBuffer &source, int sourceChannel, int sourceStartSample, int numSample
        audioSamples.copyFrom(0, 0, tmpBuffer, 0, 0, minSamples);
        audioSamples.copyFrom(1, 0, tmpBuffer, 1, 0, minSamples);
        DBG("pause");
    }

}

void GranularSynth::clearAudioSamples() {
    audioSamples.clear();
}

void GranularSynth::sliderValueChanged(Slider* slider)
{
    if (slider == &granularSettings.timeLengthNum.slider)
    {
        if (waveFormWasSet)
        {
        
            if (inputFromFile)
            {
                maxPlayTime = static_cast<int>(slider->getValue());
                initAudioSamples(getNumTotalSamples());
                loadAudioIntoSamples();
            }
            else if (!inputFromFile)
            {
                maxPlayTime = static_cast<int>(slider->getValue());
                initAudioSamples(getNumTotalSamples());                
            }
        }
    }
    else if (slider == &granularSettings.playerCountNum.slider) {
        int8 val = static_cast<int8>(slider->getValue());

        if (val > getPlayerCount())
        {
            addNewPlayer();
        }
        else if (val < getPlayerCount())
        {
            removePlayer();
        }
        
        // After adding, select this new player
        granularSettings.playerSelectNum.slider.setValue(val);
    }
    else if(slider == &granularSettings.playerSelectNum.slider)
    {        
        int8 val = static_cast<int8>(slider->getValue());

        if (getPlayerCount() > val - 1)
        {
            selectPlayer(val);
        }
        else
        {
            slider->setValue(val - 1);
        }

        for (int8 playerId = 0; playerId < granularPlayers.size(); playerId++)
        {
            if (playerId != val-1)
            {
                granularPlayers[playerId]->getCursor()->setOpacity(1);
            }
            else
            {
                granularPlayers[playerId]->getCursor()->setOpacity(100);
            }
        }
    }
}

void GranularSynth::buttonClicked(Button* buttonClicked)
{
    if (buttonClicked == &granularSettings.openAudioButton)
    {       
        inputFromFile = true;
        loadAudioIntoSamples();
        // Create new player after loading
        granularSettings.enablePlayers();
        granularSettings.openAudioButton.setVisible(false);
        granularSettings.openBufferButton.setVisible(false);
    }
    if (buttonClicked == &granularSettings.openBufferButton)
    {
        inputFromFile = false;
        // load from buffer
        // Create new player after loading
        granularSettings.enablePlayers();
        granularSettings.openAudioButton.setVisible(false);
        granularSettings.openBufferButton.setVisible(false);
        ringBufferPntr = new RingBuffer();
        granularVisualiser.setPntr(ringBufferPntr);
        waveFormWasSet = true;
    }
}

void GranularSynth::prepareToPlay(double sampleRateIn, int bufferSizeIn) {
    if (sampleRate != sampleRateIn) {
        sampleRate = sampleRateIn;
        for (GranularPlayer* player: granularPlayers)
        {
            player->changeTimer(sampleRateIn);
        }
    }
    if (bufferSize != bufferSizeIn) {
        bufferSize = bufferSizeIn;
    }
}

void GranularSynth::addNewPlayer() {
    const MessageManagerLock mmLock;
    granularPlayers.add(new GranularPlayer(getNumTotalSamples(), sampleRate));
    addAndMakeVisible(granularPlayers.getLast(), 5);
    resized();
}

void GranularSynth::removePlayer() {
    granularPlayers.removeLast();
    resized();
}

void GranularSynth::selectPlayer(int8 playerNumber) {
    granularPlayers[playerNumber - 1]->toFront(true);
}

void GranularSynth::getNextBlock(AudioBuffer<float>& bufferToFill, MidiBuffer& midiMessages)
{
    if (!waveFormWasSet)
    {
        bufferToFill.clear();
        return;
    }

    if (inputFromFile)
    {
        bufferToFill.clear();

        for (GranularPlayer* player : granularPlayers)
        {
            if (player->isCurrentMidiMode(PlayerSettings::MidiMode::ON))
            {
                handleMidi(midiMessages);
                if (midiNoteOn)
                {
                    player->fillNextBuffer(bufferToFill, audioSamples, increment);
                }
            }
            else
            {
                player->fillNextBuffer(bufferToFill, audioSamples);
            }
        }
    }
    else {
        ringBufferPntr->addBuffer(bufferToFill);
        bufferToFill.clear();
        for (GranularPlayer* player : granularPlayers)
        {
            if (player->isCurrentMidiMode(PlayerSettings::MidiMode::ON))
            {
                handleMidi(midiMessages);
                if (midiNoteOn)
                {
                    player->fillNextBuffer(bufferToFill, ringBufferPntr->getBuffer(), increment);
                }
            }
            else
            {
                player->fillNextBuffer(bufferToFill, ringBufferPntr->getBuffer());

            }
        }
             
    }
}

int8 GranularSynth::getPlayerCount()
{
    return static_cast<int8>(granularPlayers.size());
}
