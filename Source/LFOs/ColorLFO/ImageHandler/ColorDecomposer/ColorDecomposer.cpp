#include "ColorDecomposer.h"


ColorDecomposer::ColorDecomposer()
{
    addAndMakeVisible(centerTile);
    addAndMakeVisible(redTile);
    addAndMakeVisible(greenTile);
    addAndMakeVisible(blueTile);
    setRGB(10, 10, 10);
    setOpaque(true);
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
    //int tmp_height = (getHeight() * 1 / 3) * 0.85; // 100
    //int tmp_width = (getWidth() / 3) * 0.85; // 70
    Utils::addToFb(&fb, redTile,1, 70, 100);
    Utils::addToFb(&fb, greenTile, 1, 70, 100);
    Utils::addToFb(&fb, blueTile, 1, 70, 100);
    // top getHeight() * 2 / 3 = 231
    fb.performLayout(getLocalBounds().withTrimmedTop(231).withTrimmedRight(25).withTrimmedLeft(25));
}

void ColorDecomposer::setRGB(int redIn, int greenIn, int blueIn)
{
    if (redIn == 0 && greenIn == 0 && blueIn == 0)
    {
        return;
    }

    centerTile.setColor(0, Colour::fromRGB(redIn, greenIn, blueIn));

    redTile.setColor(redIn, Colour::fromRGB(redIn, 0, 0));
    greenTile.setColor(greenIn, Colour::fromRGB(0, greenIn, 0));
    blueTile.setColor(blueIn, Colour::fromRGB(0, 0, blueIn));

    resized();
}
