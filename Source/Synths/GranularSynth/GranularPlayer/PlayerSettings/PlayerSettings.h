/*
  ==============================================================================

    PlayerSettings.h
    Created: 31 Oct 2022 6:05:49pm
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

class PlayerSettings : public Component
{
public:
    static enum GranularMode
    {
        ORDER,
        REV_ORDER,
        MIRROR,
        REV_MIRROR
    };

    static enum RunningMode
    {
        STATIC,
        RUNNING
    };

    static enum MidiMode
    {
        OFF,
        ON
    };

    static enum WindowType
    {
        HALF_SINE,
        HANN,
        TRIANGLE
    };

    // Class
	PlayerSettings();
	~PlayerSettings();
    // GUI
    void initGui();
	void paint(Graphics& graphics) override;
	void resized() override;
    // Tools
    bool isGranularMode(GranularMode);
    bool isRunningMode(RunningMode);
    bool isMidiMode(MidiMode);
    bool isWindowType(WindowType);
    // Getters
    int getNumGrains();
    int getGrainLength();
    float getGrainPitch();
    float getGrainOffset();
    //int getOffset();
    float getVolume();
    float getPan(int8 channel);
    // Setters
    void setGuiColor(Colour colour);

private:
    // GUI
	Colour guiColour;
    OwnedArray<Separator> separators;
    // Play style
    RadioBox granularModeRadioBox {"MODE", C_MARINE, GRANULAR_MODE};
    RadioBox runningModeRadioBox { "CURSOR", C_LAVENDER, RUNNING_MODE};
    RadioBox midiModeRadioBox { "MIDI", C_SUNFLOWER, MIDI_MODE};
    RadioBox windowTypeRadioBox{ "WINDOW", C_MEDITERRANEAN, WINDOW_TYPE };
    // Grains
    Knob grainLengthKnob{ "LENGTH", C_MARTINA, 1, 1000, 1, 50 }; // ms
    Knob grainPitchKnob{ "PITCH", C_RADIANTYELLOW, 0.1, 1.9, 0.001, 1 }; // - 1 ; 1 x 
    Knob grainNumKnob{ "GRAINS", C_ENERGOS, 1, 25, 1, 5 }; // ms
    Knob grainOffsetKnob { "OFFSET", C_BARARED, 1, 100, 1, 10 }; // ms how fast to generate new sample after creating last one
    //Knob cursorPositionKnob{ "POSITION", C_MEDITERRANEAN, 0, 50000, 10, 0 }; // cursor position

    // Master
    Knob volumeKnob {"VOLUME", C_SUNFLOWER, 0, 100, 1, 50 }; // %
    Knob panKnob { "PAN", C_BILLS, 0, 100, 1, 50 }; // %
    // ADSR
};
