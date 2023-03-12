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
    addAndMakeVisible(topSettings);
    addAndMakeVisible(visualiser);


    initPlayers();
    initAudioSamples(getNumTotalSamples());  

    topSettings.addSliderListener(this);
    topSettings.addButtonListener(this);
    
}

GranularSynth::~GranularSynth()
{
    topSettings.removeSliderListener(this);
    topSettings.removeButtonListener(this);

    players.clear();
    audioSamples.clear();

    fileChooser = nullptr;
    ringBufferPntr = nullptr;
    knobListener = nullptr;
}

void GranularSynth::paint(Graphics& g)
{
    // Background
    g.fillAll(C_DARK);
    Utils::paintLogo(g);
}

void GranularSynth::resized()
{   
    // Top GranularSynthSettings
    topSettings.setBounds(getLocalBounds().withTrimmedBottom(getHeight() - TOP_BAR_HEIGHT));

    // Players
    for (GranularPlayer* player : players)
    {
        player->setBounds(getLocalBounds());
    }

    // AudioVisualiser
    visualiser.setBounds(getLocalBounds().withTrimmedTop(TOP_BAR_HEIGHT).withTrimmedBottom(SETTINGS_SIZE.getHeight() + 30 + (CURSOR_BALL_RADIUS * 2.5) ));
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
        increment = std::pow((double)2, (midiMsg.getNoteNumber() - 69.f) /(double)12);
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
    AudioLoad audioLoad;
    audioSamples.setSize(2, getNumTotalSamples());
    // DOCS: The contents of the buffer will initially be undefined, so use clear() to set all the samples to zero.        
    audioSamples.clear();
   
    audioLoad.fillBuffer(audioSamples, getNumTotalSamples(), file);    
    visualiser.setWaveForm(audioSamples);
    waveFormWasSet = true;

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
    return 5 * sampleRate;
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
    }

}

void GranularSynth::initPlayers()
{
    for (size_t i = 0; i < topSettings.getPlayerCount(); i++)
    {
        players.add(new GranularPlayer(getNumTotalSamples(), sampleRate));
    }
}

void GranularSynth::clearAudioSamples() {
    audioSamples.clear();
}

void GranularSynth::sliderValueChanged(Slider* slider)
{
    if (topSettings.isPlayerCountSlider(slider)) {
        int val = static_cast<int>(slider->getValue());

        if (val > getPlayerCount())
        {
            addNewPlayer();
        }
        else if (val < getPlayerCount())
        {
            removePlayer();
        }
        
        topSettings.getPlayerSelectNum().setValue(val, sendNotification);
    }
    else if(topSettings.isPlayerSelectSlider(slider))
    {        
        int val = static_cast<int>(slider->getValue());

        if (getPlayerCount() > val - 1)
        {
            selectPlayer(val);
        }
        else
        {
            slider->setValue(val - 1);
        }

        for (int playerId = 0; playerId < players.size(); playerId++)
        {
            if (playerId != val-1)
            {
                players[playerId]->getCursor()->setOpacity(1);
            }
            else
            {
                players[playerId]->getCursor()->setOpacity(100);
            }
        }
    }
}

void GranularSynth::buttonClicked(Button* button)
{
    if (topSettings.isOpenAudioButton(button))
    {       
        inputFromFile = true;
        // Load file
        loadAudioIntoSamples();
        topSettings.enablePlayers();
        topSettings.getOpenAudioButton().setVisible(false);
        topSettings.getOpenBufferButton().setVisible(false);
    }
    if (topSettings.isOpenBufferButton(button))
    {
        inputFromFile = false;
        // Load from Buffer
        ringBufferPntr = std::make_shared<RingBuffer>();
        visualiser.setPntr(ringBufferPntr);
        waveFormWasSet = true;

        topSettings.enablePlayers();
        topSettings.getOpenAudioButton().setVisible(false);
        topSettings.getOpenBufferButton().setVisible(false);


    }
}

void GranularSynth::prepareToPlay(float sampleRateIn, int bufferSizeIn) {
    sampleRate = sampleRateIn;
    for (GranularPlayer* player : players)
    {
        player->changeTimer(sampleRateIn);
    }
}

void GranularSynth::addNewPlayer() {
    const MessageManagerLock mmLock;
    players.add(new GranularPlayer(getNumTotalSamples(), sampleRate));
    addAndMakeVisible(players.getLast(), 5);
    players.getLast()->setKnobsListener(knobListener);
    resized();
}

void GranularSynth::removePlayer() {
    players.removeLast();
    resized();
}

void GranularSynth::selectPlayer(int playerNumber) {
    players[playerNumber - 1]->toFront(true);
}

void GranularSynth::processBlock(AudioBuffer<float>& bufferToFill, MidiBuffer& midiMessages)
{
    if (!waveFormWasSet)
    {
        return;
    }

    if (inputFromFile)
    {
        for (GranularPlayer* player : players)
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
        for (GranularPlayer* player : players)
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

int GranularSynth::getPlayerCount()
{
    return static_cast<int>(players.size());
}

void GranularSynth::setKnobsListener(Knob::KnobListener* listenerPntr)
{
    knobListener = listenerPntr;
}

void GranularSynth::setWaveCallback() {
    visualiser.setWaveCallback();
}

void GranularSynth::movePositionCallback() {
    for (GranularPlayer player : players) {
        player.movePositionCallback();
    }
}
