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
    // ----------------------------------------
    // Class
    LfoSettings();
    ~LfoSettings();
    // ----------------------------------------
    // GUI
    void paint(Graphics&)override;
    void resized()override;
    // ----------------------------------------
    // Listener
    // ---LFO Timer
    void addRateListener(Slider::Listener*);
    void removeRateListener(Slider::Listener*);
    // ---Direction selection
    void addDirectionListener(RadioBox::Listener*);
    void removeDirectionListener();
    // ---Color selection
    void addColorListener(RadioBox::Listener*);
    void removeColorListener();
    // ---Upload button
    void addButtonsListener(Button::Listener*);
    void removeButtonsListener(Button::Listener*);
    // ----------------------------------------
    // Get
    float getRate();
    float getDepth();
    bool isUploadButton(Button*);
    bool isRateSlider(Slider*);
    bool isColourRadioBox(RadioBox*);
    bool isDirectionRadioBox(RadioBox*);
private:
    // ----------------------------------------
    RadioBox directionRadioBox{ "DIRECTION", Colour::fromRGB(18, 203, 196), { "RANDOM", "FORWARD", "REVERSED" } };
    RadioBox colorSelectRadioBox{ "SELECTED COLOR", Colour::fromRGB(196, 229, 56), { "RED", "GREEN", "BLUE" } };
    // ----------------------------------------
    Knob rateKnob{ "RATE", Colour::fromRGB(255, 195, 18), 0.1, 49, 0.01, 1, false };
    Knob depthKnob{ "DEPTH", Colour::fromRGB(238, 90, 36), 0, 1, 0.001, 0.5, false };
    // ----------------------------------------
    TextButton uploadButton{ "UPLOAD" };
    // ----------------------------------------
    OwnedArray<Separator> separators;
    // ----------------------------------------
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(LfoSettings);
};
