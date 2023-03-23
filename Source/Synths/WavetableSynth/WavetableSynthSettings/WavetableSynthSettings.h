#pragma once
#include <JuceHeader.h>
#include "../../../Utils/Constants.h"
#include "../../../Utils/Utils.h"
#include "../../../CustomComponents/CustomLooks/RadioBox.h"
#include "../../../CustomComponents/CustomLooks/Knob.h"
#include "../../../CustomComponents/CustomLooks/Separator.h"

class WavetableSynthSettings : public Component
{
public:
    static enum MidiMode
    {
        OFF,
        ON
    };

    static enum InterpolationType
    {
        LINEAR,
        CUBIC
    };
    // ----------------------
    // Class
	WavetableSynthSettings();
	~WavetableSynthSettings();
    // ----------------------
    // GUI
    void paint(Graphics& graphics) override;
    void resized() override;
    // ----------------------
    // Listeners
    void addSlidersListener(Slider::Listener*);
    void removeSlidersListener(Slider::Listener*);
    // --- Knobs
    void setKnobsListener(Knob::Listener*);
    void removeKnobsListener();
    // Getters
    float getFreq();
    float getWaveCount();
    float getVolume();
    float getPan(int);
    // Tools
    // ----------------------
    bool isCurrentMidiMode(WavetableSynthSettings::MidiMode);
    bool isCurrentInterpolationType(WavetableSynthSettings::InterpolationType);
    bool isWaveCountKnobSlider(Slider*);
    bool isFreqKnobSlider(Slider*);

private:
    // ----------------------
    RadioBox midiModeRadioBox { "MIDI", Colour::fromRGB(87, 88, 187), {"OFF", "ON"} };
    RadioBox interpolationRadioBox{ "ITERPOLATION", Colour::fromRGB(18, 137, 167), { "LINEAR", "CUBIC"} };
    // ----------------------
    Knob freqKnob { "FREQUENCY", Colour::fromRGB(247, 159, 31), 20, 8000, 0.001, 400, true };
    Knob waveCountKnob { "WAVE COUNT", Colour::fromRGB(196, 229, 56), 2, 10, 2, 6 , false };
    // ----------------------    
    Knob volumeKnob { "VOLUME", Colour::fromRGB(255, 195, 18), 0, 100, 0.01, 50, true };
    Knob panKnob { "PAN", Colour::fromRGB(238, 90, 36), 0, 100, 0.5, 50, true };
    // ----------------------  
    Colour guiColour;
    OwnedArray<Separator> separators;
    // ----------------------  
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(WavetableSynthSettings);
};
