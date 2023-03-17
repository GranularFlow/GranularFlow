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
    // -----------------------
    // Class
    MathSettings();
    ~MathSettings();
    // -----------------------
    // GUI
    void paint(Graphics&)override;
    void resized()override;
    // -----------------------
    // Listener
    // ---LFO TIMER
    void addRateListener(Slider::Listener*);
    void removeRateListener(Slider::Listener*);
    // ---Enter button
    void addEnterListener(Button::Listener*);
    void removeEnterListener(Button::Listener*);
    void clickEnterButton();
    // -----------------------
    // Get
    std::string getText();
    int getRate();
    float getDepth();
    bool isRateSlider(Slider*);
    bool isDepthSlider(Slider*);
    bool isEnterButton(Button*);
    // -----------------------

private:
    // -----------------------
    Knob rateKnob{ "RATE", C_SUNFLOWER, 1, 20, 1, 2, false };
    Knob depthKnob{ "DEPTH", C_BILLS, 0, 1, 0.1, 0.5, false };
    // -----------------------
    TextEditor textEditor;
    TextButton enterButton{ "ENTER" };
    // -----------------------
    OwnedArray<Separator> separators;
    // -----------------------
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MathSettings);
};