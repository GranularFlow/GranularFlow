/*
  ==============================================================================

    Knob.cpp
    Created: 16 Nov 2022 1:43:43am
    Author:  honza

  ==============================================================================
*/

#include "Knob.h"

Knob::Knob(String nameIn, Colour guiColorIn, float startRangIn, float endRangeIn, float stepIn, float defaultValue)
{
    guiColor = guiColorIn;
    name = nameIn;
    value = defaultValue;

    setLookAndFeel(&customLook);

    slider.setRange(startRangIn, endRangeIn, stepIn);
    slider.setValue(defaultValue);
    slider.setColour(Slider::ColourIds::rotarySliderFillColourId, guiColorIn);
    slider.setColour(Slider::ColourIds::thumbColourId, guiColorIn);
    slider.setColour(Slider::ColourIds::textBoxBackgroundColourId, C_TRANSPARENT);
    slider.setColour(Slider::ColourIds::textBoxOutlineColourId, C_TRANSPARENT);

    addAndMakeVisible(slider);
}

Knob::~Knob()
{
    setLookAndFeel(nullptr);
}

void Knob::paint(Graphics& g)
{
    g.setColour(guiColor);
    g.fillRect(Rectangle<float>(50, 10).withCentre(Point<float>(getWidth()/(float)2.0, 0)));

    g.setColour(C_SMOKE);
    g.drawFittedText(name, getLocalBounds().withTrimmedTop(10).withTrimmedRight(getWidth() * 0.1).withTrimmedLeft(getWidth() * 0.1), Justification::centredTop, 1);
}

void Knob::resized()
{
    slider.setBounds(getLocalBounds().withTrimmedTop(30));
}


void Knob::addListener(Slider::Listener* listener)
{
    slider.addListener(listener);
}

void Knob::removeListener(Slider::Listener* listener)
{
    slider.removeListener(listener);
}

float Knob::getValue()
{
    return slider.getValue();
}
