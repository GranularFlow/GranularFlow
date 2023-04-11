#include "CustomClickableBox.h"

CustomClickableBox::CustomClickableBox(Colour colorIn, String textIn, bool fullSizeIn, int width, int height, int centerX, int centerY)
{
    fullSize = fullSizeIn;
    color = colorIn;
    text = textIn;    
    boxSize = getLocalBounds().withSize(width, height * 0.3f).withCentre(Point<int>(width / 2, height - height * 0.3f / (float)2.f));

    setBounds(centerX - width / 2.f, centerY - height / 2.f, width, height);

    path.startNewSubPath(boxSize.getTopLeft().x, boxSize.getTopLeft().y);
    path.lineTo(boxSize.getTopRight().x, boxSize.getTopRight().y);
    path.lineTo(boxSize.getTopRight().x, boxSize.getTopRight().y);
    path.lineTo(boxSize.getBottomRight().x, boxSize.getBottomRight().y * 0.9);
    path.addArc(boxSize.getBottomRight().x - (height * 0.1f), boxSize.getBottomRight().y * 0.9, (height * 0.1f), (height * 0.1f), MathConstants<float>::pi / 2, MathConstants<float>::pi, false);
    path.lineTo(boxSize.getBottomLeft().x * 1.5, boxSize.getBottomLeft().y);
    path.addArc(boxSize.getBottomLeft().x, boxSize.getBottomLeft().y - (height * 0.1f), (height * 0.1f), (height * 0.1f), MathConstants<float>::pi, MathConstants<float>::pi * 3 / 2, false);
    path.lineTo(boxSize.getTopLeft().x, boxSize.getTopLeft().y);
    path.closeSubPath();

    setBufferedToImage(true);
}

CustomClickableBox::~CustomClickableBox()
{
}

void CustomClickableBox::paint(Graphics& g)
{
   // DBG("CustomClickableBox::paint");
    g.setColour(C_GRAY);
    g.fillRoundedRectangle(getLocalBounds().withSizeKeepingCentre(getWidth(), getHeight()).toFloat(), (getHeight() * 0.1f));
    g.setColour(color);
    g.fillPath(path);
    g.setColour(C_WHITE);
    g.setFont(Font("Oswald", boxSize.getHeight(), 0));
    g.drawText(text, boxSize, Justification::centred, false);
}
