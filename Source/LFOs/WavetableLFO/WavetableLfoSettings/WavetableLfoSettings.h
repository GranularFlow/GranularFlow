/*
  ==============================================================================

    WavetableLfoSettings.h
    Created: 3 Feb 2023 12:46:01pm
    Author:  honza

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "../../../Utils/Constants.h"
#include "../../../CustomComponents/CustomLooks/RadioBox.h"
#include "../../../CustomComponents/CustomLooks/Knob.h"
#include "../../../CustomComponents/CustomLooks/Separator.h"

class WavetableLfoSettings : public Component
{
public:
 
    static enum InterpolationType
    {
        LINEAR,
        CUBIC,
        HERMITE
    };

    // Class
	WavetableLfoSettings();
	~WavetableLfoSettings();

    // GUI
    void paint(Graphics& graphics) override;
    void resized() override;

    // Tools
    // Getters
    double getRate();
    double getDepth();
    int getWaveCount();
    bool isCurrentInterpolationType(WavetableLfoSettings::InterpolationType);

    // Settings
    // (String nameIn, Colour guiColorIn, float startRangIn, float endRangeIn, float stepIn, float defaultValue)
    Knob rateKnob{ "RATE", C_SUNFLOWER, 1, 20, 1, 1, false}; // %
    Knob depthKnob{ "DEPTH", C_SUNFLOWER, 0, 1, 0.1, 0.5, false }; // %
    Knob waveCountKnob{ "WAVE COUNT", C_SUNFLOWER, 2, 10, 2, 6, false }; // %
    RadioBox interpolationRadioBox{ "ITERPOLATION", C_SUNFLOWER, INTERPOLATION_TYPE };

private:
    // GUI
    Colour guiColour;
    OwnedArray<Separator> separators;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(WavetableLfoSettings);
};