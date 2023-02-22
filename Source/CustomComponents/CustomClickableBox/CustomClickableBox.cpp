/*
  ==============================================================================

    CustomClickableBox.cpp
    Created: 22 Feb 2023 8:25:22pm
    Author:  honza

  ==============================================================================
*/

#include "CustomClickableBox.h"

CustomClickableBox::CustomClickableBox(Colour colorIn, String textIn)
{
    color = colorIn;
    text = textIn;
}

CustomClickableBox::~CustomClickableBox()
{
}

void CustomClickableBox::paint(Graphics& g)
{
    float cornerSize = getHeight() * 0.1;
    int width = getWidth();
    int height = getHeight();

    Rectangle<int> boxSize = getLocalBounds().withSize(width * 0.8, height * 0.3).withCentre(Point<int>(width / 2, (height * 0.75)));

    g.setColour(L_GRAY);
    g.fillRoundedRectangle(getLocalBounds().withSizeKeepingCentre(width * 0.8, height * 0.8).toFloat(), cornerSize);
    g.setColour(color);
    //g.fillRoundedRectangle(boxSize.toFloat(), getHeight() * 0.1);

    Path path;
    path.startNewSubPath(boxSize.getTopLeft().x, boxSize.getTopLeft().y);
    path.lineTo(boxSize.getTopRight().x, boxSize.getTopRight().y);
    path.lineTo(boxSize.getTopRight().x, boxSize.getTopRight().y);
    path.lineTo(boxSize.getBottomRight().x, boxSize.getBottomRight().y * 0.9);
    path.addArc(boxSize.getBottomRight().x - cornerSize, boxSize.getBottomRight().y * 0.9, cornerSize, cornerSize, MathConstants<float>::pi / 2, MathConstants<float>::pi, false);
    path.lineTo(boxSize.getBottomLeft().x * 1.5, boxSize.getBottomLeft().y);
    path.addArc(boxSize.getBottomLeft().x , boxSize.getBottomLeft().y - cornerSize, cornerSize, cornerSize, MathConstants<float>::pi, MathConstants<float>::pi * 3/2 , false);
    path.lineTo(boxSize.getTopLeft().x, boxSize.getTopLeft().y);

    g.fillPath(path);
    //g.strokePath(path, PathStrokeType(2.f, PathStrokeType::curved), AffineTransform::identity);

    g.setColour(C_WHITE);
    g.setFont(Font("Oswald", boxSize.getHeight() * 0.5, 0));
    g.drawFittedText(text, boxSize, Justification::centred, 1);
}

void CustomClickableBox::mouseDown(const MouseEvent&)
{
    color = C_GRASS;
    repaint();
}
