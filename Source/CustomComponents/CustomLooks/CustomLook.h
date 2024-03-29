#pragma once
#include <JuceHeader.h>
#include "../../Utils/Constants.h"

class CustomLook : public LookAndFeel_V4
{
public:
    CustomLook();
	~CustomLook();
    void drawPopupMenuItem(Graphics&, const juce::Rectangle<int>&, const bool, const bool, const bool, const bool, const bool, const String&, const String&, const Drawable*, const Colour* const)override;
    void drawComboBox(Graphics&, int, int, bool, int, int, int, int, ComboBox&) override;
    void drawRotarySlider(juce::Graphics&, int, int, int, int, float, const float, const float, juce::Slider&) override;
    void drawLinearSlider(Graphics& , int, int, int, int, float, float, float, const Slider::SliderStyle, Slider&) override;
    void drawTickBox(Graphics&, Component&, float, float, float, float, bool, bool, bool, bool) override;
};
