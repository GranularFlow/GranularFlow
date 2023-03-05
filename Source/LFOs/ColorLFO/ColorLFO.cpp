/*
  ==============================================================================

    ColorLFO.cpp
    Created: 8 Feb 2023 4:43:34pm
    Author:  honza

  ==============================================================================
*/

#include "ColorLFO.h"


ColorLFO::ColorLFO()
{
    addAndMakeVisible(settings);
    settings->uploadButton.addListener(this);
    settings->rateKnob.slider.addListener(this);
    addAndMakeVisible(*imageHandler);
    imageHandler->setListener(this);
}

ColorLFO::~ColorLFO()
{
    imageHandler->removeListener();
    stopTimer();
    settings->uploadButton.removeListener(this);
    settings->rateKnob.slider.removeListener(this);
    delete imageHandler;
    delete settings;
}

void ColorLFO::paint(Graphics& g)
{
    g.fillAll(C_DARK);
    Utils::paintLogo(g);
}

void ColorLFO::resized()
{
    Rectangle<int> settingsBounds = getLocalBounds().withTrimmedTop((getHeight() - 50) * 4 / 5).withTrimmedBottom(10).withTrimmedLeft(getWidth() * 1 / 4).withTrimmedRight(getWidth() * 1 / 4);
    settings->setBounds(settingsBounds);
    imageHandler->setBounds(getLocalBounds().withTrimmedTop(60).withTrimmedBottom(settingsBounds.getHeight() + 20).withTrimmedLeft(20).withTrimmedRight(20));
}

void ColorLFO::buttonClicked(Button* button)
{
    if (button == &settings->uploadButton)
    {
        imageHandler->loadImage();        
    }
}

void ColorLFO::timerCallback()
{
    updateKnobs(imageHandler->getNext());
}

void ColorLFO::sliderValueChanged(Slider* slider)
{
    if (slider == &settings->rateKnob.slider)
    {
        if (imageHandler->isImageSet()) {
            stopTimer();
            startTimerHz(settings->rateKnob.getValue());
        }
    }
}

void ColorLFO::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    imageHandler->prepareToPlay(sampleRate);
}

void ColorLFO::imageLoaded()
{
    stopTimer();
    startTimerHz(settings->rateKnob.getValue());
}
