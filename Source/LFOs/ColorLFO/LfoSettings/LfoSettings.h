/*
  ==============================================================================

    LfoSettings.h
    Created: 8 Feb 2023 6:01:27pm
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

class LfoSettings : public Component
{
public:
    static enum Direction {
        RANDOM,
        FORWARD,
        REVERSED
    };

    static enum SelectedColor {
        RED,
        GREEN,
        BLUE
    };

    // Class
    LfoSettings();
    ~LfoSettings();
    // GUI
    void paint(Graphics&)override;
    void resized()override;

    // Getters
    bool isCurrentDirection(Direction);
    bool isCurrentSelectedColor(SelectedColor);

    int getRate();
    int getDepth();

    //  -- Button
    TextButton uploadButton{ "LOAD" };
    // Settings
    RadioBox directionRadioBox{ "DIRECTION", C_BARARED, DIRECTION_MODE };
    Knob rateKnob{ "RATE", C_BILLS, 1000, 20000, 1000, 1000 };
    Knob depthKnob{ "DEPTH", C_BILLS, 1, 100, 1, 50 };
    RadioBox colorSelectRadioBox{ "SELECTED COLOR", C_BARARED, SELECTED_COLOR };
private:
    // GUI
    OwnedArray<Separator> separators;
};
