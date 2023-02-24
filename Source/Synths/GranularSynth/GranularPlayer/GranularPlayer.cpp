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

    Random& random = Random::getSystemRandom();
    Colour guiColor = Colour(
        (int8)random.nextInt(255),
        (int8)random.nextInt(255),
        (int8)random.nextInt(255));

    // Cursor
    cursorPosition = random.nextInt((int)std::floor(totalSamples / 2) + (int)std::floor(totalSamples / 4));
    cursor.init(Utils::samplesToPercent(cursorPosition, totalSamples), guiColor);

    // Settings background
    //settings.setGuiColor(guiColor);    

    // Visibility
    addAndMakeVisible(cursor);
    addAndMakeVisible(settings);

    cursor.setListener(this);

    startTimer(1);
}

GranularPlayer::~GranularPlayer() {
    stopTimer();
}

void GranularPlayer::paint(Graphics& g) {
}

void GranularPlayer::resized()
{
    cursor.setBounds(getLocalBounds().withTrimmedBottom(getHeight() / 2));    
    settings.setBounds(getLocalBounds()
        .withTrimmedTop((getHeight() / 2) * (1.025))
        .withTrimmedLeft(getWidth() * 0.025)
        .withTrimmedRight(getWidth() * 0.025)
        .withTrimmedBottom(getWidth() * 0.025)
    );
}

void GranularPlayer::onCursorPositionChange(int cursorPositionIn)
{    
    cursorPosition = (int)(cursorPositionIn * totalSamples/100);
    //DBG("position" << cursorPosition);
}

bool GranularPlayer::isCurrentGranularMode(PlayerSettings::GranularMode mode)
{
    return settings.isGranularMode(mode);
}

bool GranularPlayer::isCurrentMidiMode(PlayerSettings::MidiMode mode)
{
    return settings.isMidiMode(mode);
}

bool GranularPlayer::isCurrentRunningMode(PlayerSettings::RunningMode mode)
{
    return settings.isRunningMode(mode);
}

int GranularPlayer::getMaxSamples() {
    return totalSamples;
}

void GranularPlayer::addGrain(int startPosition, int length) {    
    auto tmp_grain = new Grain(startPosition, Utils::msToSamples(length, sampleRate), 0, settings.getGrainPitch(), settings.getVolume() * settings.getPan(0), settings.getVolume() * settings.getPan(1));
    //DBG("adding grain " << Utils::msToSamples(length, sampleRate));
    grains.add(tmp_grain);
}

void GranularPlayer::timerCallback()
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

    // check if need to add grain
    if (grains.size() < settings.getNumGrains() && waitForNextGrain == false) {

        addGrain(cursorPosition, settings.getGrainLength());
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

}

int GranularPlayer::calculateStep()
{
    return 1;
}

int GranularPlayer::percentToSamplePosition(int8 newCursorPositionPercent)
{
    return (int)std::floor((newCursorPositionPercent /(float) 100) * totalSamples);
}

void GranularPlayer::fillNextBuffer(AudioBuffer<float>& toFill, AudioBuffer<float>& sourceSamples)
{
    fillNextBuffer(toFill, sourceSamples, 1.f);
}

void GranularPlayer::fillNextBuffer(AudioBuffer<float>& toFill, AudioBuffer<float>& sourceSamples, float increment)
{

    Array<int8> deleteArray;
    for (int i = 0; i < grains.size(); i++)
    {
        if (grains[i] != nullptr)
        {
            if (grains[i]->getDelete())
            {
                deleteArray.add(i);
            }
            else
            {
                grains[i]->fillNextSamples(sourceSamples, toFill, &settings, totalSamples, increment);
            }
        }        
    }

    for (int8 i = 0; i < deleteArray.size(); i++)
    {
        grains.remove(deleteArray[i], true);
    }
}

int GranularPlayer::getGrainNumSamples() {
    // calculate how many samples are in set ms length
    return Utils::msToSamples(settings.getGrainLength(), sampleRate);
}

PlayerCursor* GranularPlayer::getCursor() {
    return &cursor;
}

void GranularPlayer::changeTimer(int sampleRateIn)
{
    stopTimer();
    sampleRate = sampleRateIn;
    // sample rate is very high, need to reduce it to less drastic timing
    startTimerHz(std::floor(sampleRate/(float)10));
}
