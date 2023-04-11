#include "ResetButton.h"

ResetButton::ResetButton(int width, int height, int centerX, int centerY)
{
    addAndMakeVisible(reloadButton);    
    setBounds(centerX - (width / 2.f), centerY - (height / 2.f), width, height);
    setBufferedToImage(true);
    setOpaque(true);
}

ResetButton::~ResetButton()
{
}

void ResetButton::paint(Graphics& g)
{
    g.fillAll(C_GRAY);
    buttonImage = buttonImage.rescaled(getLocalBounds().reduced(getHeight() * 0.1f).getHeight(), getLocalBounds().reduced(getHeight() * 0.1f).getHeight(), Graphics::highResamplingQuality);
    g.drawImageAt(buttonImage, getHeight() * 0.1f, getHeight() * 0.1f);
}

void ResetButton::resized()
{
}

void ResetButton::mouseDown(const MouseEvent& e)
{
    if (getLocalBounds().contains(e.getPosition()))
    {
        resetPntr->reseted(this);
    }
}

