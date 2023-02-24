/*
  ==============================================================================

    ColorTile.cpp
    Created: 15 Feb 2023 7:11:16pm
    Author:  honza

  ==============================================================================
*/

#include "ColorTile.h"


ColorTile::ColorTile()
{
}

ColorTile::~ColorTile()
{
}

void ColorTile::paint(Graphics& g)
{
    g.fillAll(color);

    g.setColour(C_WHITE);
    String colorName = colorInt == 0 ? "" : String(colorInt);
    g.drawFittedText(colorName, getLocalBounds(), Justification::centred, 1);
}

void ColorTile::setColor(int colorIntIn, Colour colorIn)
{
    colorInt = colorIntIn;
    color = colorIn;

    repaint();
}
