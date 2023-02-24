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
   initGui();
}

PlayerSettings::~PlayerSettings()
{
}

void PlayerSettings::initGui() {
    // GUI
    for (int8 i = 0; i < 2; i++)
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
    //addAndMakeVisible(cursorPositionKnob);
    // Master
    addAndMakeVisible(volumeKnob);
    addAndMakeVisible(panKnob);
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

    float sectionWidth = (getWidth() * 0.9) / 3;
    float sectionHeight = getHeight();

    float tmpHeight = sectionHeight / 2;
    float tmpWidth = sectionWidth / 2;
    Utils::addToFb(&tmpFB, granularModeRadioBox, 1, tmpWidth, tmpHeight);
    Utils::addToFb(&tmpFB, runningModeRadioBox, 2, tmpWidth, tmpHeight);
    Utils::addToFb(&tmpFB, midiModeRadioBox, 3, tmpWidth, tmpHeight);
    Utils::addToFb(&tmpFB, windowTypeRadioBox, 4, tmpWidth, tmpHeight);
    // Add column to final flex box    
    Utils::addToFb(&fb, tmpFB, 1, sectionWidth, sectionHeight);


    tmpHeight = sectionHeight;
    sectionWidth = floor((2 /(float) 3) * (getWidth() / (float)6));
    tmpWidth = sectionWidth;
    Utils::addToFb(&tmpFB2, grainLengthKnob, 1, tmpWidth, tmpHeight);
    Utils::addToFb(&tmpFB2, grainPitchKnob, 2, tmpWidth, tmpHeight);
    Utils::addToFb(&tmpFB2, grainNumKnob, 3, tmpWidth, tmpHeight);
    Utils::addToFb(&tmpFB2, grainOffsetKnob, 4, tmpWidth, tmpHeight);

    
    Utils::addToFb(&tmpFB3, volumeKnob, 1, tmpWidth, tmpHeight);
    Utils::addToFb(&tmpFB3, panKnob, 2, tmpWidth, tmpHeight);

    
    Utils::addToFb(&fb, tmpFB2, 3, sectionWidth * 4, sectionHeight);
    Utils::addToFb(&fb, tmpFB3, 5, sectionWidth * 2, sectionHeight);


    // White lines
    for (int8 i = 0; i < separators.size(); i++)
    {
        Utils::addToFb(&fb, *separators[i], (i + 1) * 2, 1, sectionHeight);
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

/*int PlayerSettings::getOffset()
{
    return cursorPositionKnob.getValue();
}*/

float PlayerSettings::getVolume()
{
    return (float)volumeKnob.getValue() / 100;
}

float PlayerSettings::getPan(int8 channel)
{
    return  1 - abs(channel - ((float)panKnob.getValue() / 100));
}

void PlayerSettings::setGuiColor(Colour guiColourIn)
{
    guiColour = guiColourIn;
}

