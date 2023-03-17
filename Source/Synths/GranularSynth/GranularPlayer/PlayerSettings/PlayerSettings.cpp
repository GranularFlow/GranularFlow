/*
  ==============================================================================

    PlayerSettings.cpp
    Created: 31 Oct 2022 6:06:57pm
    Author:  honza

  ==============================================================================
*/

#include "PlayerSettings.h"


PlayerSettings::PlayerSettings()
{
    // GUI
    for (int i = 0; i < 2; i++)
    {
        separators.add(new Separator());
        addAndMakeVisible(separators.getLast());
    }

    // Play style
    addAndMakeVisible(granularModeRadioBox);
    addAndMakeVisible(runningModeRadioBox);
    addAndMakeVisible(midiModeRadioBox);
    addAndMakeVisible(windowTypeRadioBox);
    // Grains
    addAndMakeVisible(grainLengthKnob);
    addAndMakeVisible(grainPitchKnob);
    addAndMakeVisible(grainNumKnob);
    addAndMakeVisible(grainOffsetKnob);
    // Master
    addAndMakeVisible(volumeKnob);
    addAndMakeVisible(panKnob);
}

PlayerSettings::~PlayerSettings()
{
    separators.clear();
}

void PlayerSettings::paint(Graphics& g) {
    // Settings panel
    g.setColour(L_GRAY);
    g.fillRoundedRectangle(getLocalBounds().toFloat(), 30);
}

void PlayerSettings::resized() {


    FlexBox fb{
            FlexBox::Direction::row,
            FlexBox::Wrap::noWrap,
            FlexBox::AlignContent::center,
            FlexBox::AlignItems::flexStart,
            FlexBox::JustifyContent::spaceAround
    };

    FlexBox tmpFB{
            FlexBox::Direction::row,
            FlexBox::Wrap::wrap,
            FlexBox::AlignContent::center,
            FlexBox::AlignItems::center,
            FlexBox::JustifyContent::center
    };

    FlexBox tmpFB2{
        FlexBox::Direction::row,
        FlexBox::Wrap::noWrap,
        FlexBox::AlignContent::center,
        FlexBox::AlignItems::flexStart,
        FlexBox::JustifyContent::spaceAround
    };

    FlexBox tmpFB3{
        FlexBox::Direction::row,
        FlexBox::Wrap::noWrap,
        FlexBox::AlignContent::center,
        FlexBox::AlignItems::flexStart,
        FlexBox::JustifyContent::spaceAround
    };

    //float sectionWidth = (getWidth() * 0.9) / 3; //345
    //float sectionHeight = getHeight(); // 250
    Utils::addToFb(&tmpFB, granularModeRadioBox, 1, 172, 125);
    Utils::addToFb(&tmpFB, runningModeRadioBox, 2, 172, 125);
    Utils::addToFb(&tmpFB, midiModeRadioBox, 3, 172, 125);
    Utils::addToFb(&tmpFB, windowTypeRadioBox, 4, 172, 125);
    // Add column to final flex box    
    Utils::addToFb(&fb, FlexItem(tmpFB), 1, 345, 250);


    //tmpHeight = 250;
    Utils::addToFb(&tmpFB2, grainLengthKnob, 1, 125, 250);
    Utils::addToFb(&tmpFB2, grainPitchKnob, 2, 125, 250);
    Utils::addToFb(&tmpFB2, grainNumKnob, 3, 125, 250);
    Utils::addToFb(&tmpFB2, grainOffsetKnob, 4, 125, 250);

    
    Utils::addToFb(&tmpFB3, volumeKnob, 1, 125, 250);
    Utils::addToFb(&tmpFB3, panKnob, 2, 125, 250);

    
    Utils::addToFb(&fb, FlexItem(tmpFB2), 3, 500, 250);
    Utils::addToFb(&fb, FlexItem(tmpFB3), 5, 250, 250);


    // White lines
    for (int i = 0; i < separators.size(); i++)
    {
        Utils::addToFb(&fb, *separators[i], (i + 1) * 2, 1, 250);
    }

    fb.performLayout(getLocalBounds());
}

int PlayerSettings::getGrainLength()
{
    return (int)grainLengthKnob.getValue();
}

int PlayerSettings::getNumGrains()
{
    return (int)grainNumKnob.getValue();
}

bool PlayerSettings::isMidiMode(PlayerSettings::MidiMode mode) {
    return ((PlayerSettings::MidiMode)midiModeRadioBox.getValue() == mode);
}

bool PlayerSettings::isRunningMode(PlayerSettings::RunningMode mode) {
    return (PlayerSettings::RunningMode)runningModeRadioBox.getValue() == mode;
}

void PlayerSettings::resetDefaultValues()
{
    granularModeRadioBox.resetDefaultValue();
    runningModeRadioBox.resetDefaultValue();
    midiModeRadioBox.resetDefaultValue();
    windowTypeRadioBox.resetDefaultValue();
    grainLengthKnob.setDefaultValue();
    grainPitchKnob.setDefaultValue();
    grainNumKnob.setDefaultValue();
    grainOffsetKnob.setDefaultValue();
    volumeKnob.setDefaultValue();
    panKnob.setDefaultValue();
}

bool PlayerSettings::isGranularMode(PlayerSettings::GranularMode mode) {
    return (PlayerSettings::GranularMode)granularModeRadioBox.getValue() == mode;
}
bool PlayerSettings::isWindowType(PlayerSettings::WindowType mode) {
    return (PlayerSettings::WindowType)windowTypeRadioBox.getValue() == mode;
}

float PlayerSettings::getGrainPitch()
{
    return (float)grainPitchKnob.getValue();
}

float PlayerSettings::getGrainOffset()
{
    return (float)grainOffsetKnob.getValue();
}

float PlayerSettings::getVolume()
{
    return (float)volumeKnob.getValue() / 100;
}

float PlayerSettings::getPan(int channel)
{
    return  1 - abs(channel - ((float)panKnob.getValue() / 100));
}

PlayerSettings::GranularMode PlayerSettings::getGranularMode()
{
    return (PlayerSettings::GranularMode)granularModeRadioBox.getValue();
}

PlayerSettings::WindowType PlayerSettings::getWindowType()
{
    return (PlayerSettings::WindowType)windowTypeRadioBox.getValue();
}

void PlayerSettings::setGuiColor(Colour guiColourIn)
{
    guiColour = guiColourIn;
}

void PlayerSettings::setKnobsListener(Knob::Listener* knobListenerPntr)
{
    grainLengthKnob.setKnobListener(knobListenerPntr);
    grainPitchKnob.setKnobListener(knobListenerPntr);
    grainNumKnob.setKnobListener(knobListenerPntr);
    grainOffsetKnob.setKnobListener(knobListenerPntr);

    volumeKnob.setKnobListener(knobListenerPntr);
    panKnob.setKnobListener(knobListenerPntr);
}

