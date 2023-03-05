/*
  ==============================================================================

    MathSettings.h
    Created: 20 Feb 2023 9:02:07pm
    Author:  honza

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "../../../Utils/Constants.h"
#include "../../../Utils/Utils.h"
#include "../../../CustomComponents/CustomLooks/Separator.h"
#include "../../../CustomComponents/CustomLooks/Knob.h"
#include "../../../CustomComponents/CustomLooks/RadioBox.h"


class MathSettings : public Component
{
public:

    // Class
    MathSettings();
    ~MathSettings();
    // GUI
    void paint(Graphics&)override;
    void resized()override;

    Knob rateKnob{ "RATE", C_BILLS, 1, 20, 1, 2 };
    Knob depthKnob{ "DEPTH", C_BILLS, 1, 100, 1, 50 };

    TextEditor textEditor;
    TextButton enterButton{ "ENTER" };
private:    
    // GUI
    OwnedArray<Separator> separators;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MathSettings);
};