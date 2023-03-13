/*
  ==============================================================================

    GranularPlayer.cpp
    Created: 30 Oct 2022 4:54:30pm
    Author:  honza

  ==============================================================================
*/

#include "GranularPlayer.h"

GranularPlayer::GranularPlayer(int totalSamplesIn, int sampleRateIn) {

    totalSamples = totalSamplesIn;
    sampleRate = sampleRateIn;

    init();
}

GranularPlayer::~GranularPlayer() {
    grains.clear();
}

void GranularPlayer::paint(Graphics& g) {
}

void GranularPlayer::resized()
{
    cursor.setBounds(getLocalBounds().withTrimmedBottom(SETTINGS_SIZE.getHeight() + 30));
    settings.setBounds(SETTINGS_SIZE.withCentre(Point<int>(SETTINGS_SIZE.getCentreX(), SETTINGS_SIZE.getCentreY() - TOP_BAR_HEIGHT - 10)).withSizeKeepingCentre(SETTINGS_SIZE.getWidth(), SETTINGS_SIZE.getHeight()+25));
}

void GranularPlayer::onCursorPositionChange(int cursorPositionIn)
{    
    cursorPosition = (int)(cursorPositionIn * totalSamples/100);
}

bool GranularPlayer::isCurrentRunningMode(PlayerSettings::RunningMode mode)
{
    return settings.isRunningMode(mode);
}

bool GranularPlayer::isCurrentMidiMode(PlayerSettings::MidiMode mode)
{
    return settings.isMidiMode(mode);
}

void GranularPlayer::init()
{
    Random& random = Random::getSystemRandom();
    Colour guiColor = Colour(
        (int)random.nextInt(255),
        (int)random.nextInt(255),
        (int)random.nextInt(255));

    // Cursor
    cursorPosition = W_WIDTH / 2;
    cursor.init(50, guiColor);

    // Settings background
    //settings.setGuiColor(guiColor);    

    // Visibility
    addAndMakeVisible(cursor);
    addAndMakeVisible(settings);

    cursor.setListener(this);

    initGrains();
}

void GranularPlayer::initGrains()
{
    for (int i = 0; i < 10; i++)
    {
        grains.add(new Grain());
    }
}

void GranularPlayer::reset()
{
    init();
    settings.resetDefaultValues();
}

void GranularPlayer::addGrain(int startPosition) {
    for (Grain* grain : grains)
    {
        if (grain->isSkipped())
        {
            grain->setNewGrain(
                startPosition,
                Utils::msToSamples(settings.getGrainLength(), sampleRate),
                Utils::msToSamples(settings.getGrainOffset(), sampleRate),
                settings.getGrainPitch(),
                settings.getVolume() * settings.getPan(0),
                settings.getVolume() * settings.getPan(1),
                settings.getGranularMode(),
                settings.getWindowType()
            );
            break;
        }
    }
}

void GranularPlayer::removeGrain()
{
}

void GranularPlayer::movePositionCallback()
{
    //check if running

    if (cursorPosition >= totalSamples) {
        cursorPosition = 0;
    }
    if (cursorPosition <= 0 ) {
        cursorPosition = totalSamples;
    }

    if (settings.isRunningMode(PlayerSettings::RUNNING))
    {
        if (settings.isGranularMode(PlayerSettings::ORDER) || settings.isGranularMode(PlayerSettings::MIRROR))
        {
            cursorPosition += 10;
        }
        else if (settings.isGranularMode(PlayerSettings::REV_ORDER) || settings.isGranularMode(PlayerSettings::REV_MIRROR))
        {
            cursorPosition -= 10;
        }
        
        cursor.setCursorPosition(100 * cursorPosition/(float)totalSamples);
    }  

}

int GranularPlayer::getActiveGrains()
{

    int tmpCount = 0;
    for (Grain* grain : grains)
    {
        if (!grain->isSkipped())
        {
            tmpCount++;
        }
    }
    return tmpCount;
}

void GranularPlayer::fillNextBuffer(AudioBuffer<float>& toFill, AudioBuffer<float>& sourceSamples)
{
    fillNextBuffer(toFill, sourceSamples, 1.f);
}

void GranularPlayer::fillNextBuffer(AudioBuffer<float>& toFill, AudioBuffer<float>& sourceSamples, float increment)
{
    // check if need to add grain
    if (getActiveGrains() < settings.getNumGrains() && waitForNextGrain == false) {
        addGrain(cursorPosition);
        waitForNextGrain = true;
    }

    if (waitForNextGrain && grainTimer >= settings.getGrainOffset())
    {
        waitForNextGrain = false;
        grainTimer = 0;
    }

    if (waitForNextGrain)
    {
        grainTimer += 1;
    }

    for (Grain* grain : grains)
    {
        if (!grain->isSkipped())
        {
            grain->fillNextSamples(sourceSamples, toFill, increment);
        }
    }
}

PlayerCursor* GranularPlayer::getCursor() {
    return &cursor;
}

void GranularPlayer::changeTimer(int sampleRateIn)
{
    sampleRate = sampleRateIn;
}

void GranularPlayer::setKnobsListener(Knob::Listener* knobListenerPntr)
{
    settings.grainLengthKnob.setKnobListener(knobListenerPntr);
    settings.grainPitchKnob.setKnobListener(knobListenerPntr);
    settings.grainNumKnob.setKnobListener(knobListenerPntr);
    settings.grainOffsetKnob.setKnobListener(knobListenerPntr);

    settings.volumeKnob.setKnobListener(knobListenerPntr);
    settings.panKnob.setKnobListener(knobListenerPntr);
}
