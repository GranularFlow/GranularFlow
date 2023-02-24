/*
  ==============================================================================

    ColorDecomposer.cpp
    Created: 8 Feb 2023 6:28:46pm
    Author:  honza

  ==============================================================================
*/

#include "ColorDecomposer.h"


ColorDecomposer::ColorDecomposer()
{
    addAndMakeVisible(centerTile);
    addAndMakeVisible(redTile);
    addAndMakeVisible(greenTile);
    addAndMakeVisible(blueTile);
    setRGB(0, 0, 0);
}

ColorDecomposer::~ColorDecomposer()
{
}

void ColorDecomposer::paint(Graphics& g)
{
}

void ColorDecomposer::resized()
{
    centerTile.setBounds(getLocalBounds().withTrimmedBottom(getHeight() * 1/3).withTrimmedLeft(25).withTrimmedRight(25).withTrimmedTop(25));

    FlexBox fb{
            FlexBox::Direction::row,
            FlexBox::Wrap::noWrap,
            FlexBox::AlignContent::center,
            FlexBox::AlignItems::center,
            FlexBox::JustifyContent::spaceBetween
    };

    // Second column
    int tmp_height = (getHeight() * 1 / 3) * 0.85;
    int tmp_width = (getWidth() / 3) * 0.85;
    Utils::addToFb(&fb, redTile,1, tmp_width, tmp_height);
    Utils::addToFb(&fb, greenTile, 1, tmp_width, tmp_height);
    Utils::addToFb(&fb, blueTile, 1, tmp_width, tmp_height);

    fb.performLayout(getLocalBounds().withTrimmedTop(getHeight() * 2 / 3).withTrimmedRight(25).withTrimmedLeft(25));
}

void ColorDecomposer::setRGB(int redIn, int greenIn, int blueIn)
{
    centerTile.setColor(0, Colour::fromRGB(redIn, greenIn, blueIn));

    redTile.setColor(redIn, Colour::fromRGB(redIn, 0, 0));
    greenTile.setColor(redIn, Colour::fromRGB(0, greenIn, 0));
    blueTile.setColor(redIn, Colour::fromRGB(0, 0, blueIn));
}
