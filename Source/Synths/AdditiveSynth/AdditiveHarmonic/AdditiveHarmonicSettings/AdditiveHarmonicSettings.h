#pragma once
#include <JuceHeader.h>
#include "../../../../Utils/Constants.h"
#include "../../../../Utils/Utils.h"
#include "../../../../CustomComponents/CustomLooks/RadioBox.h"
#include "../../../../CustomComponents/CustomLooks/Knob.h"
#include "../../../../CustomComponents/CustomLooks/Separator.h"

class AdditiveHarmonicSettings : public Component
{
public:

    static enum MidiMode
    {
        OFF,
        ON
    };
    // ----------------------
    // Class
	AdditiveHarmonicSettings();
	~AdditiveHarmonicSettings();
    // ----------------------
    // GUI
    void paint(Graphics& graphics) override;
    void resized() override;
    // ----------------------
    // Listeners
    // --- Knobs
    void setKnobsListener(Knob::Listener*);
    void removeKnobsListener();
    void resetDefaultValues();
    // --- Freq slider
    void addFreqSliderListener(Slider::Listener*);
    void removeFreqSliderListener(Slider::Listener*);
    // --- Phase slider
    void addPhaseSliderListener(Slider::Listener*);
    void removePhaseSliderListener(Slider::Listener*);
    // ----------------------
    // Get
    float getPhase();
    float getFreq();
    float getVolume();
    float getPan(bool);
    bool isCurrentMidiMode(AdditiveHarmonicSettings::MidiMode);
    bool isPhaseKnob(Slider*);
    bool isFreqKnob(Slider*);
private:
    // ----------------------
    // Parameters
    RadioBox midiModeRadioBox{ "MIDI", Colour::fromRGB(87, 88, 187), {"OFF", "ON"} };
    Knob phaseKnob{ "PHASE", Colour::fromRGB(237, 76, 103), 0, 360, 1, 0, true };
    Knob freqKnob{ "FREQUENCY", Colour::fromRGB(18, 203, 196), 10, 1000, 0.001, 440, true };
    Knob volumeKnob{ "VOLUME", Colour::fromRGB(247, 159, 31), 0, 100, 0.01, 50, true };
    Knob panKnob{ "PAN", Colour::fromRGB(196, 229, 56), 0, 100, 1, 50 , true };
    // ----------------------
    OwnedArray<Separator> separators;
};