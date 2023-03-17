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
    RadioBox directionRadioBox{ "DIRECTION", C_MARTINA, DIRECTION_MODE };
    RadioBox colorSelectRadioBox{ "SELECTED COLOR", C_ENERGOS, SELECTED_COLOR };
    // ----------------------------------------
    Knob rateKnob{ "RATE", C_SUNFLOWER, 0.1, 20, 1, 2, false };
    Knob depthKnob{ "DEPTH", C_BILLS, 0, 1, 0.001, 0.5, false };
    // ----------------------------------------
    TextButton uploadButton{ "UPLOAD" };
    // ----------------------------------------
    OwnedArray<Separator> separators;
    // ----------------------------------------
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(LfoSettings);
};
