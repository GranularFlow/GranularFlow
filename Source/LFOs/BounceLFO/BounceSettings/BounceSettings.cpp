/*
  ==============================================================================

    BounceSettings.cpp
    Created: 16 Feb 2023 7:29:50pm
    Author:  honza

  ==============================================================================
*/

#include "BounceSettings.h"


BounceSettings::BounceSettings()
{
    addAndMakeVisible(ballSpeedKnob);
    addAndMakeVisible(rateKnob);
    addAndMakeVisible(depthKnob);
    addAndMakeVisible(coordinateRadioBox);
    addAndMakeVisible(clearButton);
    addAndMakeVisible(startButton);


    for (int i = 0; i < 4; i++)
    {
        separators.add(new Separator());
        addAndMakeVisible(separators.getLast());
    }

}

BounceSettings::~BounceSettings()
{
}

void BounceSettings::paint(Graphics& g)
{
    g.setColour(L_GRAY);
    g.fillRoundedRectangle(getLocalBounds().toFloat(), 30);
}

void BounceSettings::resized()
{
    FlexBox fb{
            FlexBox::Direction::row,
            FlexBox::Wrap::noWrap,
            FlexBox::AlignContent::center,
            FlexBox::AlignItems::center,
            FlexBox::JustifyContent::spaceBetween
    };

    int tmpWidth = getWidth() * 1 / 6 * 0.85;
    int tmpHeight = getHeight() * 0.85;

    Utils::addToFb(&fb, ballSpeedKnob, 1, tmpWidth, tmpHeight);
    Utils::addToFb(&fb, rateKnob, 3, tmpWidth, tmpHeight);
    Utils::addToFb(&fb, depthKnob, 5, tmpWidth, tmpHeight);
    Utils::addToFb(&fb, coordinateRadioBox, 7, tmpWidth, tmpHeight);
    Utils::addToFb(&fb, clearButton, 8, tmpWidth, 60);
    Utils::addToFb(&fb, startButton, 9, tmpWidth, 60);
    

    

    // White lines
    for (int i = 0; i < separators.size(); i++)
    {
        fb.items.add(FlexItem(*separators[i]).withMinWidth(1).withHeight(tmpHeight).withOrder((i + 1) * 2));
    }

    fb.performLayout(getLocalBounds().withTrimmedLeft(15).withTrimmedRight(15));

}

void BounceSettings::addRateListener(Slider::Listener* listener)
{
    rateKnob.addSliderListener(listener);
}

void BounceSettings::removeRateListener(Slider::Listener* listener)
{
    rateKnob.removeSliderListener(listener);
}

bool BounceSettings::isCurrentSelectedCoordinate(Coordinate selectedCoord)
{
    return coordinateRadioBox.getValue() == selectedCoord;
}

double BounceSettings::getRate()
{
    return rateKnob.getValue();
}

double BounceSettings::getDepth()
{
    return depthKnob.getValue();
}
