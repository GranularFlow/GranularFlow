/*
  ==============================================================================

    BounceLFO.cpp
    Created: 16 Feb 2023 7:29:42pm
    Author:  honza

  ==============================================================================
*/

#include "BounceLFO.h"

BounceLFO::BounceLFO()
{
   addAndMakeVisible(settings);
   addAndMakeVisible(canvas);
   settings.addButtonsListener(this);
}

BounceLFO::~BounceLFO()
{
    settings.removeButtonsListener(this);
}


void BounceLFO::paint(Graphics& g)
{
    g.fillAll(C_DARK);
    Utils::paintLogo(g);
}

void BounceLFO::resized()
{
    Rectangle<int> settingsBounds = getLocalBounds().withTrimmedTop((getHeight() - 50) * 4 / 5).withTrimmedBottom(10).withTrimmedLeft(getWidth() * 1 / 4).withTrimmedRight(getWidth() * 1 / 4);

    settings.setBounds(settingsBounds);
    canvas.setBounds(getLocalBounds().withTrimmedTop(90).withTrimmedBottom(settingsBounds.getHeight() + 40).withTrimmedLeft(200).withTrimmedRight(200));
}

void BounceLFO::addTimerListener(Slider::Listener* listener) {
    settings.addRateListener(listener);
}

void BounceLFO::removeTimerListener(Slider::Listener* listener) {
    settings.removeRateListener(listener);
}


void BounceLFO::moveBall()
{
    canvas.moveBall();
}

void BounceLFO::buttonClicked(Button* button)
{
    if (settings.isClearButton(button))
    {
        canvas.clearLines();
    }

    if (settings.isStartButton(button))
    {
        settings.setBallSpeed(settings.getBallSpeed() == 0 ? 60 : 0);
    }
}

double BounceLFO::getNext()
{
    return canvas.getOutput(settings.isCurrentSelectedCoordinate(BounceSettings::X)) * settings.getDepth();
}

int BounceLFO::getTimerHz() {
    return settings.getRate();
}

void BounceLFO::timeCallback() {
    updateKnobs(getNext());
}

void BounceLFO::addBallSpeedListener(Slider::Listener* listener)
{
    settings.addBallSpeedListener(listener);
}

void BounceLFO::removeBallSpeedListener(Slider::Listener* listener)
{
    settings.removeBallSpeedListener(listener);
}

bool BounceLFO::isTimerSlider(Slider* slider)
{
    return settings.isRateSlider(slider);
}

bool BounceLFO::isBallSpeedSlider(Slider* slider)
{
    return settings.isBallSpeedSlider(slider);
}

int BounceLFO::getBallSpeed()
{
    return settings.getBallSpeed();
}
