#include "GranularPlayer.h"

GranularPlayer::GranularPlayer(int totalSamplesIn, int sampleRateIn) 
{
    totalSamples = totalSamplesIn;
    sampleRate = sampleRateIn;
    addAndMakeVisible(settings);

    cursorPosition = 72000;

    for (int i = 0; i < 20; i++)
    {
        grains.add(new Grain());
    }

    setBounds(0, 60, W_WIDTH, W_HEIGHT - 60);
}

GranularPlayer::~GranularPlayer() {
}

void GranularPlayer::paint(Graphics& g) {
  // DBG("GranularPlayer::paint");
   g.setColour(C_ENERGOS);
   g.fillRect((int)((cursorPosition / (float)totalSamples) * W_WIDTH) - 1.0, 0, 2.0, 340);
}

void GranularPlayer::resized()
{
    settings.setBounds(GRANULAR_PLAYER_SETTINGS_SIZE);
}

void GranularPlayer::mouseDown(const MouseEvent& event)
{
    if (event.x <= getWidth() && event.x >= 0)
    {
        if (mouseMovable)
        {
            cursorPosition = (event.x/(float)W_WIDTH) * totalSamples;
            repaint(0, 0, W_WIDTH, 340);

        }
    }
}

void GranularPlayer::disableCursorMovements(bool disable)
{
    mouseMovable = !disable;
}


void GranularPlayer::reset()
{    
    for (Grain* grain: grains)
    {
        grain->setSkip();
    }
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

void GranularPlayer::movePositionCallback()
{
    if (cursorPosition >= totalSamples) {
        cursorPosition = 0;
    }
    if (cursorPosition <= 0) {
        cursorPosition = totalSamples;
    }

    if (settings.getMidiMode() == PlayerSettings::GranularMode::ORDER || settings.getMidiMode() == PlayerSettings::GranularMode::MIRROR)
    {
        cursorPosition += 25;
    }
    else if (settings.getMidiMode() == PlayerSettings::GranularMode::REV_ORDER || settings.getMidiMode() == PlayerSettings::GranularMode::REV_MIRROR)
    {
        cursorPosition -= 25;
    }
    
}

bool GranularPlayer::isCursorMoving()
{
    return settings.getRunningMode() == PlayerSettings::RUNNING;
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
        grainTimer += toFill.getNumSamples();
    }

    for (Grain* grain : grains)
    {
        if (!grain->isSkipped())
        {
            grain->fillNextSamples(sourceSamples, toFill, increment);
        }
    }
}

int GranularPlayer::getCursorPosition()
{
    return cursorPosition;
}

PlayerSettings::MidiMode GranularPlayer::getMidiMode()
{
    return settings.getMidiMode();
}

void GranularPlayer::prepareToPlay(int sampleRateIn)
{
    sampleRate = sampleRateIn;
}

void GranularPlayer::setKnobsListener(Knob::Listener* knobListenerPntr)
{
    settings.setKnobsListener(knobListenerPntr);
}
