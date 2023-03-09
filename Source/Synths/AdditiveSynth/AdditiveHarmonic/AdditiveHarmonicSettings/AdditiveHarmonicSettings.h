/*
  ==============================================================================

    AdditiveHarmonicsSettings.h
    Created: 1 Feb 2023 10:20:17pm
    Author:  honza

  ==============================================================================
*/

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

    // Class
	AdditiveHarmonicSettings();
	~AdditiveHarmonicSettings();
    // GUI
    void paint(Graphics& graphics) override;
    void resized() override;
    // Knobs
    void setKnobsListener(Knob::KnobListener*);
    void removeKnobsListener();
    void resetDefaultValues();
    // Getters
    float getPhase();
    float getFreq();
    float getVolume();
    float getPan(bool);
    bool isCurrentMidiMode(AdditiveHarmonicSettings::MidiMode);
    // Get objects
    bool isPhaseKnob(Slider*);
    bool isFreqKnob(Slider*);
    Knob& getPhaseKnob();
    Knob& getFreqKnob();

private:
    Colour guiColour;
    OwnedArray<Separator> separators;
    // Parameters
    RadioBox midiModeRadioBox{ "MIDI", C_SUNFLOWER, MIDI_MODE };
    Knob phaseKnob{ "PHASE", L_AQUA, 0, 360, 1, 0, true };
    Knob freqKnob{ "FREQUENCY", L_ORANGE, 10, 1000, 1, 440, true };
    Knob volumeKnob{ "VOLUME", C_SUNFLOWER, 0, 100, 1, 50, true };
    Knob panKnob{ "PAN", C_BILLS, 0, 100, 1, 50 , true };
};