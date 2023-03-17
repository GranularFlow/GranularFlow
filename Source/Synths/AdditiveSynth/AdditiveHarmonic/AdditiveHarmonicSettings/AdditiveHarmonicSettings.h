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
    RadioBox midiModeRadioBox{ "MIDI", C_CIRCUMMORBITAL, MIDI_MODE };
    Knob phaseKnob{ "PHASE", C_BARARED, 0, 360, 1, 0, true };
    Knob freqKnob{ "FREQUENCY", C_MARTINA, 10, 1000, 0.001, 440, true };
    Knob volumeKnob{ "VOLUME", C_RADIANTYELLOW, 0, 100, 0.01, 50, true };
    Knob panKnob{ "PAN", C_ENERGOS, 0, 100, 1, 50 , true };
    // ----------------------
    OwnedArray<Separator> separators;
};