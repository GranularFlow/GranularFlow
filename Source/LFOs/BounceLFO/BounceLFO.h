/*
  ==============================================================================

    BounceLFO.h
    Created: 16 Feb 2023 7:29:42pm
    Author:  honza

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include <JuceHeader.h>
#include "../../Utils/Utils.h"
#include "../../Utils/Constants.h"
#include "../LFO.h"
#include "BounceSettings/BounceSettings.h"
#include "BounceCanvas/BounceCanvas.h"


class BounceLFO : public Component, public LFO, public Button::Listener
{
public:
    // ----------------------------------------
    // Class
	BounceLFO();
	~BounceLFO();
    // ----------------------------------------
    // GUI
    void paint(Graphics&) override;
    void resized() override;
    // ----------------------------------------
    // Listeners
    // --- LFO Timer
    void addTimerListener(Slider::Listener*)override;
    void removeTimerListener(Slider::Listener*)override;
    // -> CallBack
    void timeCallback()override;
    // --- Ball Position
    void addBallSpeedListener(Slider::Listener*);
    void removeBallSpeedListener(Slider::Listener*);
    void moveBall();
    // ----------------------------------------
    // Buttons
    void buttonClicked(Button*);
    // ----------------------------------------
    // Get
    int getBallSpeed();
    double getNext();
    int getTimerHz();
    bool isTimerSlider(Slider*);
    bool isBallSpeedSlider(Slider*);
private:
    BounceSettings settings;
    BounceCanvas canvas;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(BounceLFO);
};
