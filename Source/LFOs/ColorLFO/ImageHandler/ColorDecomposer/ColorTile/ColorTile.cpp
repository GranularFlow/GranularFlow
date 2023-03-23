#include "ColorTile.h"


ColorTile::ColorTile()
{
    setOpaque(true);
}

ColorTile::~ColorTile()
{
}

void ColorTile::paint(Graphics& g)
{
    g.fillAll(color);
    g.setColour(Colours::white);

    String colorName = colorInt == 0 ? "" : String(colorInt);
    g.drawFittedText(colorName, getLocalBounds(), Justification::centred, 1);
}

void ColorTile::setColor(int colorIntIn, Colour colorIn)
{
    colorInt = colorIntIn;
    color = colorIn;
    repaint();
}
