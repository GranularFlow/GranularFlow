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
    // ----------------------------------------
    // Class
    BounceSettings();
    ~BounceSettings();
    // ----------------------------------------
    // GUI
    void paint(Graphics&) override;
    void resized()override;
    // ----------------------------------------
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
    // ----------------------------------------
    // Get    
    int getBallSpeed();
    double getRate();
    double getDepth();
    bool isCurrentSelectedCoordinate(Coordinate);
    bool isRateSlider(Slider*);
    bool isBallSpeedSlider(Slider*);
    bool isClearButton(Button*);
    bool isStartButton(Button*);
    // ----------------------------------------
    // Set
    void setBallSpeed(int);
private:
    // ----------------------------------------
    // Knobs
    Knob ballSpeedKnob{ "BALL SPEED", C_BLUE_MARTINA, 0, 33, 1, 50, false };
    Knob rateKnob{ "RATE", C_SUNFLOWER, 0.1, 49, 0.01, 1, false };
    Knob depthKnob{ "DEPTH", C_PUFFINS_BILL, 0, 1, 0.001, 0.5, false };
    // ----------------------------------------
    // Buttons
    RadioBox coordinateRadioBox{ "DIRECTION", C_ENERGOS, { "X", "Y" } };
    TextButton clearButton{ "CLEAR" };
    TextButton startButton{ "START" };
    // ----------------------------------------
    OwnedArray<Separator> separators;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(BounceSettings);
};
