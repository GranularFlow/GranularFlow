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
    // Getters
    bool isCurrentSelectedCoordinate(Coordinate);
    double getRate();
    double getDepth();

    Knob ballSpeedKnob { "BALL SPEED", C_BILLS, 1, 100, 1, 10, false };
    Knob rateKnob { "RATE", C_BILLS, 1, 20, 1, 2, false };
    Knob depthKnob { "DEPTH", C_BILLS, 0, 1, 0.1, 0.5, false };
    RadioBox coordinateRadioBox { "DIRECTION", C_BARARED, COORDINATE };
    TextButton clearButton { "CLEAR" };
    TextButton startButton{ "START" };

private:
    OwnedArray<Separator> separators;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(BounceSettings);
};
