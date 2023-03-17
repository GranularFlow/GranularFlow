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
    settings.setBounds(SETTINGS_SIZE.withSizeKeepingCentre(750, 200));
    canvas.setBounds(getLocalBounds().withTrimmedTop(TOP_BAR_HEIGHT + 10).withTrimmedBottom(SETTINGS_SIZE.getHeight() + 20).withTrimmedLeft(100).withTrimmedRight(100));
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
