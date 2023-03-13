/*
  ==============================================================================

    BounceSettings.h
    Created: 16 Feb 2023 7:29:50pm
    Author:  honza

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "../../../Utils/Constants.h"
#include "../../../Utils/Utils.h"
#include "../../../CustomComponents/CustomLooks/RadioBox.h"
#include "../../../CustomComponents/CustomLooks/Knob.h"
#include "../../../CustomComponents/CustomLooks/Separator.h"

class BounceSettings : public Component
{
public:
    static enum Coordinate {
        X,
        Y
    };

    // Class
    BounceSettings();
    ~BounceSettings();

    // GUI
    void paint(Graphics&) override;
    void resized()override;
    // Listeners
    // ---LFO TIMER
    void addRateListener(Slider::Listener*);
    void removeRateListener(Slider::Listener*);
    // Button
    void addButtonsListener(Button::Listener*);
    void removeButtonsListener(Button::Listener*);
    // Sliders
    void addBallSpeedListener(Slider::Listener*);
    void removeBallSpeedListener(Slider::Listener*);
    // Getters
    bool isCurrentSelectedCoordinate(Coordinate);
    double getRate();
    double getDepth();
    bool isRateSlider(Slider*);
    bool isBallSpeedSlider(Slider*);
    bool isClearButton(Button*);
    bool isStartButton(Button*);
    int getBallSpeed();
    // Set
    void setBallSpeed(int);

private:
    Knob ballSpeedKnob{ "BALL SPEED", C_BILLS, 0, 100, 1, 60, false };
    Knob rateKnob{ "RATE", C_BILLS, 1, 20, 1, 2, false };
    Knob depthKnob{ "DEPTH", C_BILLS, 0, 1, 0.1, 0.5, false };
    RadioBox coordinateRadioBox{ "DIRECTION", C_BARARED, COORDINATE };
    TextButton clearButton{ "CLEAR" };
    TextButton startButton{ "START" };

    OwnedArray<Separator> separators;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(BounceSettings);
};
