/*
  ==============================================================================

    ResetButton.cpp
    Created: 3 Mar 2023 11:52:26pm
    Author:  honza

  ==============================================================================
*/

#include "ResetButton.h"


ResetButton::ResetButton()
{
    addAndMakeVisible(reloadButton);

    /*  
    const bool resizeButtonNowToFitThisImage,
    const bool rescaleImagesWhenButtonSizeChanges,
    const bool preserveImageProportions,
    const Image& normalImage_,

    const float imageOpacityWhenNormal,
    Colour overlayColourWhenNormal,
    const Image& overImage_,

    const float imageOpacityWhenOver,
    Colour overlayColourWhenOver,
    const Image& downImage_,

    const float imageOpacityWhenDown,
    Colour overlayColourWhenDown,
    const float hitTestAlphaThreshold)
    */
    
}

ResetButton::~ResetButton()
{
}

void ResetButton::paint(Graphics& g)
{
    g.setColour(bgColor);
    int x = getLocalBounds().reduced(getHeight() * 0.1f).getHeight();
    g.fillRoundedRectangle(getLocalBounds().reduced(getHeight() * 0.1f).toFloat(), getHeight() * 0.1f);  

    buttonImage = buttonImage.rescaled(x, x, Graphics::highResamplingQuality);
    g.drawImageAt(buttonImage, getHeight() * 0.1f, getHeight() * 0.1f);
}

void ResetButton::resized()
{
    //reloadButton.setBounds(getLocalBounds().withSizeKeepingCentre(30, 30));
    repaint();
}

void ResetButton::mouseDown(const MouseEvent& e)
{
    if (getLocalBounds().contains(e.getPosition()))
    {
        bgColor = M_LIGHT;
        repaint();
        resetPntr->reseted(this);

    }
}

void ResetButton::mouseUp(const MouseEvent& e)
{
    bgColor = C_GRAY;
    repaint();
}
