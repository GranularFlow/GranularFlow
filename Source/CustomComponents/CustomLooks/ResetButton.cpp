#include "ResetButton.h"

ResetButton::ResetButton()
{
    addAndMakeVisible(reloadButton);    
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
    bgColor = L_GRAY;
    repaint();
}
