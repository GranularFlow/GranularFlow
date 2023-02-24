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
    addAndMakeVisible(*imageHandler);

}

ColorLFO::~ColorLFO()
{
    settings->uploadButton.removeListener(this);
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

void ColorLFO::prepareToPlay(float sampleRate) {
    imageHandler->prepareToPlay(sampleRate);
}

void ColorLFO::getNext()
{
    return imageHandler->getNext();
}