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
    // ------------------
    // Class
	WavetableLfoSettings();
	~WavetableLfoSettings();
    // ------------------
    // GUI
    void paint(Graphics& graphics) override;
    void resized() override;
    // Listener
    // ---LFO TIMER
    void addRateListener(Slider::Listener*);
    void removeRateListener(Slider::Listener*);
    // --- WaveCount
    void addWaveCountListener(Slider::Listener*);
    void removeWaveCountListener(Slider::Listener*);
    // Tools
    // Getters
    double getRate();
    double getDepth();
    int getWaveCount();
    bool isWaveCountSlider(Slider*);
    bool isRateSlider(Slider*);


private:
    // Settings
    Knob rateKnob{ "RATE", Colour::fromRGB(255, 195, 18), 0.1, 99, 0.01, 1, false };
    Knob depthKnob{ "DEPTH", Colour::fromRGB(247, 159, 31), 0.1, 1, 0.01, 0.5, false };
    Knob waveCountKnob{ "WAVE COUNT", Colour::fromRGB(196, 229, 56), 2, 10, 2, 6, false };

    // GUI
    Colour guiColour;
    OwnedArray<Separator> separators;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(WavetableLfoSettings);
};
