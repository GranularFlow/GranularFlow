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
    setOpaque(true);
}

WavetableSynthSettings::~WavetableSynthSettings()
{
}

void WavetableSynthSettings::paint(Graphics& g)
{
   // DBG("WavetableSynthSettings::paint");
    g.fillAll(Colour::fromRGB(33, 33, 33));
    g.setColour(Colour::fromRGB(50, 50, 50));
    g.fillRoundedRectangle(getLocalBounds().toFloat(), 25);
}

void WavetableSynthSettings::resized()
{
    FlexBox fb{
            FlexBox::Direction::row,
            FlexBox::Wrap::noWrap,
            FlexBox::AlignContent::center,
            FlexBox::AlignItems::flexStart,
            FlexBox::JustifyContent::spaceAround
    };
    // addToFb(FlexBox* fb, Component& c, int order, int minWidth, int minHeight);
    Utils::addToFb(&fb, midiModeRadioBox, 1, 100, 225);
    Utils::addToFb(&fb, freqKnob, 3, 100, 225);
    Utils::addToFb(&fb, waveCountKnob, 5, 100, 225);
    Utils::addToFb(&fb, interpolationRadioBox, 7, 100, 225);
    Utils::addToFb(&fb, volumeKnob, 9, 100, 225);
    Utils::addToFb(&fb, panKnob, 11, 100, 225);


    // White lines
    for (int i = 0; i < separators.size(); i++)
    {
        Utils::addToFb(&fb, *separators[i], (i + 1) * 2, 1, 225);        
    }

    fb.performLayout(getLocalBounds().withTrimmedLeft(15).withTrimmedRight(15));

}

void WavetableSynthSettings::addSlidersListener(Slider::Listener* listener)
{
    freqKnob.addSliderListener(listener);
    waveCountKnob.addSliderListener(listener);
}

void WavetableSynthSettings::removeSlidersListener(Slider::Listener* listener)
{
    freqKnob.removeSliderListener(listener);
    waveCountKnob.removeSliderListener(listener);
}

void WavetableSynthSettings::setKnobsListener(Knob::Listener* knobListenerPntr)
{
    freqKnob.setKnobListener(knobListenerPntr);
    waveCountKnob.setKnobListener(knobListenerPntr);
    volumeKnob.setKnobListener(knobListenerPntr);
    panKnob.setKnobListener(knobListenerPntr);
}

void WavetableSynthSettings::removeKnobsListener()
{
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

float WavetableSynthSettings::getPan(int channel)
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

bool WavetableSynthSettings::isWaveCountKnobSlider(Slider* slider)
{
    return waveCountKnob.isCurrentSlider(slider);
}

bool WavetableSynthSettings::isFreqKnobSlider(Slider* slider)
{
    return freqKnob.isCurrentSlider(slider);
}