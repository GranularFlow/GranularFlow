
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
    addAndMakeVisible(*imageHandler);

    settings->addListener(this);
    imageHandler->setListener(this);
}

ColorLFO::~ColorLFO()
{
    stopTimer();

    imageHandler->removeListener();    
    settings->removeListener(this);

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
    //Rectangle<int> settingsBounds = getLocalBounds().withTrimmedTop((getHeight() - 50) * 4 / 5).withTrimmedBottom(10).withTrimmedLeft(getWidth() * 1 / 4).withTrimmedRight(getWidth() * 1 / 4);
    settings->setBounds(SETTINGS_SIZE);
    imageHandler->setBounds(getLocalBounds().withTrimmedTop(60).withTrimmedBottom(SETTINGS_SIZE.getHeight() + 40).withTrimmedLeft(20).withTrimmedRight(20));
}

void ColorLFO::buttonClicked(Button* button)
{
    if (settings->isUploadButton(button))
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
    if (settings->isRateKnobSlider(slider))
    {
        if (imageHandler->isImageSet()) {
            stopTimer();
            startTimerHz(slider->getValue());
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
    startTimerHz(settings->getRate());
}
