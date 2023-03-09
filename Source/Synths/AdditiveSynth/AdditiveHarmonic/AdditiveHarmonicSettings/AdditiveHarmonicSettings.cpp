/*
  ==============================================================================

    AdditiveHarmonicsSettings.cpp
    Created: 1 Feb 2023 10:20:17pm
    Author:  honza

  ==============================================================================
*/

#include "AdditiveHarmonicSettings.h"

AdditiveHarmonicSettings::AdditiveHarmonicSettings()
{
    // GUI
    for (int8 i = 0; i < 3; i++)
    {
        separators.add(new Separator());
        addAndMakeVisible(separators.getLast());
    }

    // Settings
    addAndMakeVisible(midiModeRadioBox);
    addAndMakeVisible(phaseKnob);
    addAndMakeVisible(freqKnob);

    // Master
    addAndMakeVisible(volumeKnob);
    addAndMakeVisible(panKnob);

}

AdditiveHarmonicSettings::~AdditiveHarmonicSettings()
{
    separators.clear();
}

void AdditiveHarmonicSettings::paint(Graphics& g)
{
    g.setColour(L_GRAY);
    g.fillRoundedRectangle(getLocalBounds().toFloat(), 30);
}

void AdditiveHarmonicSettings::resized()
{

    FlexBox fb{
            FlexBox::Direction::row,
            FlexBox::Wrap::noWrap,
            FlexBox::AlignContent::center,
            FlexBox::AlignItems::flexStart,
            FlexBox::JustifyContent::spaceAround
    };


    int tmp_width = (getWidth() / 8) * 0.9;
    Utils::addToFb(&fb, midiModeRadioBox, 1, tmp_width, getHeight());
    Utils::addToFb(&fb, phaseKnob, 3, tmp_width, getHeight());
    Utils::addToFb(&fb, freqKnob, 5, tmp_width, getHeight());
    Utils::addToFb(&fb, volumeKnob, 7, tmp_width, getHeight());
    Utils::addToFb(&fb, panKnob, 9, tmp_width, getHeight());

    // White lines
    for (int8 i = 0; i < separators.size(); i++)
    {
        Utils::addToFb(&fb, *separators[i], (i + 1) * 2, 1, getHeight());
    }

    fb.performLayout(getLocalBounds().withTrimmedLeft(2/3 * getWidth()));
}

void AdditiveHarmonicSettings::setKnobsListener(Knob::KnobListener* knobListenerPntr)
{
    phaseKnob.setKnobListener(knobListenerPntr);
    freqKnob.setKnobListener(knobListenerPntr);
    volumeKnob.setKnobListener(knobListenerPntr);
    panKnob.setKnobListener(knobListenerPntr);
}

void AdditiveHarmonicSettings::removeKnobsListener()
{
    phaseKnob.removeKnobListener();
    freqKnob.removeKnobListener();
    volumeKnob.removeKnobListener();
    panKnob.removeKnobListener();
}

void AdditiveHarmonicSettings::resetDefaultValues()
{
    midiModeRadioBox.resetDefaultValue();
    phaseKnob.setDefaultValue();
    freqKnob.setDefaultValue();
    volumeKnob.setDefaultValue();
    panKnob.setDefaultValue();
}

float AdditiveHarmonicSettings::getPhase()
{
    return phaseKnob.getValue();
}

float AdditiveHarmonicSettings::getFreq()
{
    return freqKnob.getValue();
}

float AdditiveHarmonicSettings::getVolume()
{
    return (float)volumeKnob.getValue() / 100;
}

float AdditiveHarmonicSettings::getPan(bool leftChannel)
{
    return  1 - abs((int)leftChannel - ((float)panKnob.getValue() / 100));
}

bool AdditiveHarmonicSettings::isCurrentMidiMode(AdditiveHarmonicSettings::MidiMode mode)
{
    return ((AdditiveHarmonicSettings::MidiMode)midiModeRadioBox.getValue() == mode);
}

bool AdditiveHarmonicSettings::isPhaseKnob(Slider* slider)
{
    return phaseKnob.isCurrentSlider(slider);
}

bool AdditiveHarmonicSettings::isFreqKnob(Slider* slider)
{
    return freqKnob.isCurrentSlider(slider);
}

Knob& AdditiveHarmonicSettings::getPhaseKnob()
{
    return phaseKnob;
}

Knob& AdditiveHarmonicSettings::getFreqKnob()
{
    return freqKnob;
}
