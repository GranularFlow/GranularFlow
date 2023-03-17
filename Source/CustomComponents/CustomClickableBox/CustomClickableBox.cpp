#include "CustomClickableBox.h"

CustomClickableBox::CustomClickableBox(Colour colorIn, String textIn, bool fullSizeIn)
{
    fullSize = fullSizeIn;
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

    Rectangle<int> boxSize = getLocalBounds().withSize(width, height * 0.3f).withCentre(Point<int>(width / 2, height - (height * 0.3f)/(float)2.f));

    g.setColour(L_GRAY);
    if (fullSize){ g.setColour(color); }
    
    g.fillRoundedRectangle(getLocalBounds().withSizeKeepingCentre(width, height).toFloat(), cornerSize);
    g.setColour(color);

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

    g.setColour(C_WHITE);

   
    // TODO TEXT DRAW
    if (fullSize)
    {
        g.setFont(Font("Oswald", getHeight() * 0.4, 0));
        g.drawFittedText(text, getLocalBounds(), Justification::centred, 1);
    }
    else
    {
        g.setFont(Font("Oswald", boxSize.getHeight(), 0));
        g.drawText(text, boxSize, Justification::centred, false);
    }    
}
