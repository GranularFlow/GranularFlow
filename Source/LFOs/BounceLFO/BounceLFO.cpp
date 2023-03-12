/*
  ==============================================================================

    BounceLFO.cpp
    Created: 16 Feb 2023 7:29:42pm
    Author:  honza

  ==============================================================================
*/

#include "BounceLFO.h"

BounceLFO::BounceLFO()
{
   addAndMakeVisible(settings);
   addAndMakeVisible(canvas);

   settings.rateKnob.addSliderListener(this);
   settings.ballSpeedKnob.addSliderListener(this);
   settings.clearButton.addListener(this);
   settings.startButton.addListener(this);
}

BounceLFO::~BounceLFO()
{
    settings.rateKnob.removeSliderListener(this);
    settings.ballSpeedKnob.removeSliderListener(this);
    settings.clearButton.removeListener(this);
    settings.startButton.removeListener(this);
}


void BounceLFO::paint(Graphics& g)
{
    g.fillAll(C_DARK);
    Utils::paintLogo(g);
}

void BounceLFO::resized()
{
    Rectangle<int> settingsBounds = getLocalBounds().withTrimmedTop((getHeight() - 50) * 4 / 5).withTrimmedBottom(10).withTrimmedLeft(getWidth() * 1 / 4).withTrimmedRight(getWidth() * 1 / 4);

    settings.setBounds(settingsBounds);
    canvas.setBounds(getLocalBounds().withTrimmedTop(90).withTrimmedBottom(settingsBounds.getHeight() + 40).withTrimmedLeft(200).withTrimmedRight(200));
}

void ColorLFO::addTimerListener(Slider::Listener* listener) {
    settings.addRateListener(listener);
}

void ColorLFO::removeTimerListener(Slider::Listener* listener) {
    settings.removeRateListener(listener);
}


void BounceLFO::sliderValueChanged(Slider* slider)
{    
    if (settings.rateKnob.isCurrentSlider(slider))
    {
        startTimerHz(slider->getValue());
    }
    if (settings.ballSpeedKnob.isCurrentSlider(slider))
    {
        canvas.setBallSpeed(slider->getValue());
    }
}

void BounceLFO::buttonClicked(Button* button)
{
    if (button == & settings.clearButton)
    {
        canvas.clearLines();
    }

    if (button == &settings.startButton)
    {
        if (){

        }
        settings.ballSpeedKnob.getValue();
    }
}

double BounceLFO::getNext()
{
    return canvas.getOutput(settings.isCurrentSelectedCoordinate(BounceSettings::X)) * settings.getDepth();
}

void BounceLFO::updateCallback() {
    updateKnobs(getNext());
}

