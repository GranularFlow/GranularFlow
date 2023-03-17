#include "BounceSettings.h"


BounceSettings::BounceSettings()
{
    addAndMakeVisible(ballSpeedKnob);
    addAndMakeVisible(rateKnob);
    addAndMakeVisible(depthKnob);
    addAndMakeVisible(coordinateRadioBox);
    addAndMakeVisible(clearButton);
    addAndMakeVisible(startButton);


    for (int i = 0; i < 5; i++)
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
            FlexBox::JustifyContent::spaceAround
    };

    Utils::addToFb(&fb, ballSpeedKnob, 1, 110, getHeight());
    Utils::addToFb(&fb, rateKnob, 3, 110, getHeight());
    Utils::addToFb(&fb, depthKnob, 5, 110, getHeight());
    Utils::addToFb(&fb, coordinateRadioBox, 7, 110, getHeight());
    Utils::addToFb(&fb, clearButton, 9, 95, 60);
    Utils::addToFb(&fb, startButton, 11, 95, 60);

    // Separators
    for (int i = 0; i < separators.size(); i++)
    {
        Utils::addToFb(&fb, *separators[i], (i + 1) * 2, 1, getHeight());
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

void BounceSettings::addButtonsListener(Button::Listener* listener)
{
    clearButton.addListener(listener);
    startButton.addListener(listener);
}

void BounceSettings::removeButtonsListener(Button::Listener* listener)
{
    clearButton.removeListener(listener);
    startButton.removeListener(listener);
}

void BounceSettings::addBallSpeedListener(Slider::Listener* listener)
{
    ballSpeedKnob.addSliderListener(listener);
}

void BounceSettings::removeBallSpeedListener(Slider::Listener* listener)
{
    ballSpeedKnob.removeSliderListener(listener);
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

bool BounceSettings::isRateSlider(Slider* slider)
{
    return rateKnob.isCurrentSlider(slider);
}

bool BounceSettings::isBallSpeedSlider(Slider* slider)
{
    return ballSpeedKnob.isCurrentSlider(slider);
}

bool BounceSettings::isClearButton(Button* button)
{
    return button == &clearButton;
}

bool BounceSettings::isStartButton(Button* button)
{
    return button == &startButton;
}

void BounceSettings::setBallSpeed(int speed)
{
    ballSpeedKnob.setValue(speed);
}

int BounceSettings::getBallSpeed()
{
    return ballSpeedKnob.getValue();
}
