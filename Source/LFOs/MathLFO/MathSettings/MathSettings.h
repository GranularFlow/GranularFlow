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
    // Listener
    // ---LFO TIMER
    void addRateListener(Slider::Listener*);
    void removeRateListener(Slider::Listener*);
    // ---Enter button
    void addEnterListener(Button::Listener*);
    void removeEnterListener(Button::Listener*);
    // Get
    std::string getText();
    int getRate();
    bool isRateSlider(Slider*);
    bool isEnterButton(Button*);


private:    
    Knob rateKnob{ "RATE", C_BILLS, 1, 20, 1, 2, false };
    Knob depthKnob{ "DEPTH", C_BILLS, 1, 100, 1, 50, false };
    TextEditor textEditor;
    TextButton enterButton{ "ENTER" };
    // GUI
    OwnedArray<Separator> separators;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MathSettings);
};