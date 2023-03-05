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
   addListeners();
   settings.ballSpeedKnob.slider.setValue(1);
}

BounceLFO::~BounceLFO()
{
    stopTimer();
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

void BounceLFO::addListeners()
{
    //settings.depthKnob.slider.addListener(this);
    settings.rateKnob.slider.addListener(this);
    settings.ballSpeedKnob.slider.addListener(this);
    settings.clearButton.addListener(this);
}

void BounceLFO::removeListeners()
{
    //settings.depthKnob.slider.removeListener(this);
    settings.rateKnob.slider.removeListener(this);
    settings.ballSpeedKnob.slider.removeListener(this);
    settings.clearButton.removeListener(this);

}

void BounceLFO::timerCallback()
{
    checkNextCoordinate();
}

void BounceLFO::sliderValueChanged(Slider* slider)
{    
    if (slider == &settings.rateKnob.slider)
    {
        stopTimer();
        startTimerHz(slider->getValue());
    }
    if (slider == &settings.ballSpeedKnob.slider)
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
}

float BounceLFO::getOutputValue()
{
    return outputValue * (settings.getDepth() / (float)100);
}

void BounceLFO::checkNextCoordinate()
{
    outputValue = canvas.getCoord(settings.isCurrentSelectedCoordinate(BounceSettings::X));    
}
