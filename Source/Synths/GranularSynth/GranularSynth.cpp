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
    topSettings.addSliderListener(this);
    topSettings.addButtonListener(this);   

    for (int i = 0; i < 3; i++)
    {
        players.add(new GranularPlayer(144000, 48000));
        addChildComponent(players.getLast());
    }
}

GranularSynth::~GranularSynth()
{
    topSettings.removeSliderListener(this);
    topSettings.removeButtonListener(this);

    fileChooser = nullptr;
    ringBufferPtr = nullptr;
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
        player->setBounds(getLocalBounds().withTrimmedTop(TOP_BAR_HEIGHT));
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
    audioSamples.setSize(2, BUFFER_SAMPLES);
    // DOCS: The contents of the buffer will initially be undefined, so use clear() to set all the samples to zero.        
    audioSamples.clear();
   
    audioLoad.fillBuffer(audioSamples, BUFFER_SAMPLES, file);
    visualiser.setWaveForm(audioSamples);
    waveFormWasSet = true;

    audioLoad.clear();
    showPlayers();
}

void GranularSynth::loadAudioIntoSamples()
{    
    File audioFile;

    fileChooser = std::make_unique<juce::FileChooser>("Select a Wave file...", juce::File{}, "*.wav");

    fileChooser->launchAsync({}, [this](const FileChooser& fc) {
        loadAudioFromFile(fc.getResult());

    });
}

void GranularSynth::clearAudioSamples() {
    audioSamples.clear();
}

void GranularSynth::sliderValueChanged(Slider* slider)
{
    if (topSettings.isPlayerCountSlider(slider)) {
        int val = static_cast<int>(slider->getValue());

        if (val > activePlayers)
        {
            addNewPlayer();
        }
        else if (val < activePlayers)
        {
            removePlayer();
        }
        
        topSettings.getPlayerSelectNum().setValue(val, sendNotification);
    }
    else if(topSettings.isPlayerSelectSlider(slider))
    {        
        int val = static_cast<int>(slider->getValue());

        if (activePlayers > val - 1)
        {
            selectPlayer(val);
        }
        else
        {
            slider->setValue(val - 1);
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
        ringBufferPtr = std::make_shared<RingBuffer>();
        visualiser.setPntr(ringBufferPtr);
        waveFormWasSet = true;
        
        topSettings.enablePlayers();
        topSettings.getOpenAudioButton().setVisible(false);
        topSettings.getOpenBufferButton().setVisible(false);
        showPlayers();
        disableCursorMovements();
    }
}

void GranularSynth::disableCursorMovements()
{
    for (GranularPlayer* player : players)
    {
        player->disableCursorMovements();
    }
}

void GranularSynth::showPlayers()
{
    players[0]->setVisible(true);
}

void GranularSynth::prepareToPlay(float sampleRateIn, int bufferSizeIn) {

    for (GranularPlayer* player : players)
    {
        player->changeTimer(sampleRateIn);
    }
}

void GranularSynth::addNewPlayer() 
{
    activePlayers++;
}

void GranularSynth::removePlayer() {
    activePlayers--;
    players[activePlayers]->reset();
}

void GranularSynth::selectPlayer(int playerNumber) 
{

    for (int playerId = 0; playerId < players.size(); playerId++)
    {
        if (playerId != playerNumber-1)
        {
            players[playerId]->setVisible(false);
        }
        else
        {
            players[playerId]->setVisible(true);
        }
    }
}

void GranularSynth::processBlock(AudioBuffer<float>& bufferToFill, MidiBuffer& midiMessages)
{
    if (!waveFormWasSet)
    {
        return;
    }

    if (inputFromFile)
    {
        for (size_t i = 0; i < activePlayers; i++)
        {
            if (players[i]->isCurrentMidiMode(PlayerSettings::MidiMode::ON))
            {
                handleMidi(midiMessages);
                if (!midiNoteOn)
                {                    
                    return;
                }                    
            }
            players[i]->fillNextBuffer(bufferToFill, audioSamples, increment);
        }
    }
    else {
        ringBufferPtr->addBuffer(bufferToFill);
        for (size_t i = 0; i < activePlayers; i++)
        {
            if (players[i]->isCurrentMidiMode(PlayerSettings::MidiMode::ON))
            {
                handleMidi(midiMessages);
                if (!midiNoteOn)
                {
                    return;
                }
            }
            players[i]->fillNextBuffer(bufferToFill, ringBufferPtr->getBuffer(), increment);
        }
    }
}

int GranularSynth::getPlayerCount()
{
    return static_cast<int>(players.size());
}

bool GranularSynth::isFileInput()
{
    return inputFromFile;
}

void GranularSynth::setKnobsListener(Knob::Listener* listenerPntr)
{
    for (GranularPlayer* player : players)
    {
        player->setKnobsListener(listenerPntr);
    }
}

void GranularSynth::removeKnobsListener()
{
  // DO NOTHING knobPntr get removed at deconstructor
}

void GranularSynth::setWaveCallback() {
    visualiser.setWaveCallback();
}

void GranularSynth::movePositionCallback() {
    for (GranularPlayer* player : players) {
        if (player->isCursorMoving())
        {
            player->movePositionCallback();
        }       
    }
}
