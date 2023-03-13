
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
    addAndMakeVisible(imageHandler);
    settings.addDirectionListener(this);
    settings.addColorListener(this);
}

ColorLFO::~ColorLFO()
{
    settings.removeDirectionListener();
    settings.removeColorListener();
}

void ColorLFO::paint(Graphics& g)
{
    g.fillAll(C_DARK);
    Utils::paintLogo(g);
}

void ColorLFO::resized()
{
    //Rectangle<int> settingsBounds = getLocalBounds().withTrimmedTop((getHeight() - 50) * 4 / 5).withTrimmedBottom(10).withTrimmedLeft(getWidth() * 1 / 4).withTrimmedRight(getWidth() * 1 / 4);
    settings.setBounds(SETTINGS_SIZE);
    imageHandler.setBounds(getLocalBounds().withTrimmedTop(60).withTrimmedBottom(SETTINGS_SIZE.getHeight() + 40).withTrimmedLeft(20).withTrimmedRight(20));
}

void ColorLFO::buttonClicked(Button* button)
{
    if (settings.isUploadButton(button))
    {
        imageHandler.loadImage();
    }
}
void ColorLFO::timeCallback()
{
    updateKnobs(imageHandler.getNext() * settings.getDepth());
}


void ColorLFO::onValueChange(RadioBox* radioBox, int selectedButton)
{
    DBG("selectedButton " << selectedButton);
    
}

int ColorLFO::getTimerHz() {
    return settings.getRate();
}

void ColorLFO::addTimerListener(Slider::Listener* listener) {
    settings.addRateListener(listener);
}

void ColorLFO::removeTimerListener(Slider::Listener* listener) {
    settings.removeRateListener(listener);
}