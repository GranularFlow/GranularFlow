/*
  ==============================================================================

    WavetableSynthSettings.cpp
    Created: 3 Feb 2023 12:46:01pm
    Author:  honza

  ==============================================================================
*/

#include "WavetableSynthSettings.h"


WavetableSynthSettings::WavetableSynthSettings()
{
    addAndMakeVisible(midiModeRadioBox);
    addAndMakeVisible(freqKnob);
    addAndMakeVisible(waveCountKnob);
    addAndMakeVisible(volumeKnob);
    addAndMakeVisible(interpolationRadioBox);
    addAndMakeVisible(panKnob);

    for (int i = 0; i < 5; i++)
    {
        separators.add(new Separator());
        addAndMakeVisible(separators.getLast());
    }
}

WavetableSynthSettings::~WavetableSynthSettings()
{
}

void WavetableSynthSettings::paint(Graphics& g)
{
    g.setColour(L_GRAY);
    g.fillRoundedRectangle(getLocalBounds().toFloat(), 30);
}

void WavetableSynthSettings::resized()
{
    int sectionWidth = (getWidth() * 0.9) / 6;
    int sectionHeight = getHeight();

    FlexBox fb{
            FlexBox::Direction::row,
            FlexBox::Wrap::noWrap,
            FlexBox::AlignContent::center,
            FlexBox::AlignItems::flexStart,
            FlexBox::JustifyContent::spaceAround
    };

    // Second column
    int tmpheight = sectionHeight;
    int tmpWidth = 100;
    // addToFb(FlexBox* fb, Component& c, int8 order, int minWidth, int minHeight);
    Utils::addToFb(&fb, midiModeRadioBox, 1, tmpWidth, tmpheight);
    Utils::addToFb(&fb, freqKnob, 3, tmpWidth, tmpheight);
    Utils::addToFb(&fb, waveCountKnob, 5, tmpWidth, tmpheight);
    Utils::addToFb(&fb, interpolationRadioBox, 7, tmpWidth, tmpheight);
    Utils::addToFb(&fb, volumeKnob, 9, tmpWidth, tmpheight);
    Utils::addToFb(&fb, panKnob, 11, tmpWidth, tmpheight);


    // White lines
    for (int i = 0; i < separators.size(); i++)
    {
        Utils::addToFb(&fb, *separators[i], (i + 1) * 2, 1, tmpheight);        
    }

    fb.performLayout(getLocalBounds());

}


float WavetableSynthSettings::getFreq()
{
    return freqKnob.getValue();
}

float WavetableSynthSettings::getWaveCount()
{
    return waveCountKnob.getValue();
}

float WavetableSynthSettings::getVolume()
{
    return (float)volumeKnob.getValue() / 100;
}

float WavetableSynthSettings::getPan(int8 channel)
{
    return  1 - abs(channel - ((float)panKnob.getValue() / 100));
}

bool WavetableSynthSettings::isCurrentMidiMode(WavetableSynthSettings::MidiMode mode)
{
    return ((WavetableSynthSettings::MidiMode)midiModeRadioBox.getValue() == mode);
}

bool WavetableSynthSettings::isCurrentInterpolationType(WavetableSynthSettings::InterpolationType type)
{
    return ((WavetableSynthSettings::InterpolationType)interpolationRadioBox.getValue() == type);
}
