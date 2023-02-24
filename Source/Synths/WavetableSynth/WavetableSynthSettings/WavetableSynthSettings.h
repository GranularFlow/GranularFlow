/*
  ==============================================================================

    WavetableSynthSettings.h
    Created: 3 Feb 2023 12:46:01pm
    Author:  honza

  ==============================================================================
*/

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
        CUBIC,
        HERMITE
    };

    // Class
	WavetableSynthSettings();
	~WavetableSynthSettings();

    // GUI
    void paint(Graphics& graphics) override;
    void resized() override;

    // Tools
    // Getters
    float getFreq();
    float getWaveCount();
    float getVolume();
    float getPan(int8);
    bool isCurrentMidiMode(WavetableSynthSettings::MidiMode);
    bool isCurrentInterpolationType(WavetableSynthSettings::InterpolationType);

    // Settings
    // (String nameIn, Colour guiColorIn, float startRangIn, float endRangeIn, float stepIn, float defaultValue)
    RadioBox midiModeRadioBox{ "MIDI", C_SUNFLOWER, MIDI_MODE };
    Knob freqKnob{ "FREQUENCY", C_SUNFLOWER, 100, 1000, 1, 400 }; // %
    Knob waveCountKnob{ "WAVE COUNT", C_SUNFLOWER, 2, 10, 2, 6 }; // %
    RadioBox interpolationRadioBox{ "ITERPOLATION", C_SUNFLOWER, INTERPOLATION_TYPE };

    // Master
    Knob volumeKnob{ "VOLUME", C_SUNFLOWER, 0, 100, 1, 50 }; // %
    Knob panKnob{ "PAN", C_BILLS, 0, 100, 1, 50 }; // %


private:
    // GUI
    Colour guiColour;
    OwnedArray<Separator> separators;


};
