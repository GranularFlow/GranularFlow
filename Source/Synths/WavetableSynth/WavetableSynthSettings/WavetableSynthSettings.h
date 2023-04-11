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
    RadioBox midiModeRadioBox { "MIDI", C_CIRCUMORBITAL_RING, {"OFF", "ON"} };
    RadioBox interpolationRadioBox{ "ITERPOLATION", C_MEDITERRANEAN_SEA, { "LINEAR", "CUBIC"} };
    // ----------------------
    Knob freqKnob { "FREQUENCY", C_RADIANT_YELLOW, 20, 8000, 0.001, 400, true };
    Knob waveCountKnob { "WAVE COUNT", C_ENERGOS, 2, 10, 2, 6 , false };
    // ----------------------    
    Knob volumeKnob { "VOLUME", C_SUNFLOWER, 0, 100, 0.01, 50, true };
    Knob panKnob { "PAN", C_PUFFINS_BILL, 0, 100, 0.5, 50, true };
    // ----------------------  
    Colour guiColour;
    OwnedArray<Separator> separators;
    // ----------------------  
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(WavetableSynthSettings);
};
