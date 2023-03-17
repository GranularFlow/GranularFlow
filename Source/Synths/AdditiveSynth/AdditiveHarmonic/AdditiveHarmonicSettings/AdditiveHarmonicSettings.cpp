#include "AdditiveHarmonicSettings.h"

AdditiveHarmonicSettings::AdditiveHarmonicSettings()
{
    // Settings
    addAndMakeVisible(midiModeRadioBox);
    addAndMakeVisible(phaseKnob);
    addAndMakeVisible(freqKnob);
    // Master
    addAndMakeVisible(volumeKnob);
    addAndMakeVisible(panKnob);
    // GUI
    for (int i = 0; i < 4; i++)
    {
        separators.add(new Separator());
        addAndMakeVisible(separators.getLast());
    }
}

AdditiveHarmonicSettings::~AdditiveHarmonicSettings()
{
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
            FlexBox::AlignItems::center,
            FlexBox::JustifyContent::spaceAround
    };


    //int tmp_width = (getWidth() / 8) * 0.9; // 128
    Utils::addToFb(&fb, midiModeRadioBox, 1, 128, getHeight());
    Utils::addToFb(&fb, phaseKnob, 3, 128, getHeight());
    Utils::addToFb(&fb, freqKnob, 5, 128, getHeight());
    Utils::addToFb(&fb, volumeKnob, 7, 128, getHeight());
    Utils::addToFb(&fb, panKnob, 9, 128, getHeight());

    // White lines
    for (int i = 0; i < separators.size(); i++)
    {
        Utils::addToFb(&fb, *separators[i], (i + 1) * 2, 1, getHeight());
    }

    fb.performLayout(getLocalBounds().withTrimmedLeft(2/3 * getWidth()));
}

void AdditiveHarmonicSettings::setKnobsListener(Knob::Listener* knobListenerPntr)
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

void AdditiveHarmonicSettings::addFreqSliderListener(Slider::Listener* listener)
{
    freqKnob.addSliderListener(listener);
}

void AdditiveHarmonicSettings::removeFreqSliderListener(Slider::Listener* listener)
{
    freqKnob.removeSliderListener(listener);
}

void AdditiveHarmonicSettings::addPhaseSliderListener(Slider::Listener* listener)
{
    phaseKnob.addSliderListener(listener);
}

void AdditiveHarmonicSettings::removePhaseSliderListener(Slider::Listener* listener)
{
    phaseKnob.removeSliderListener(listener);
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
    return volumeKnob.getValue() / 100;
}

float AdditiveHarmonicSettings::getPan(bool leftChannel)
{
    return  1 - abs((int)leftChannel - (panKnob.getValue() / 100.f));
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
