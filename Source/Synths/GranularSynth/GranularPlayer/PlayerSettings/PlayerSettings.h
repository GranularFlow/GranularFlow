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
    // ----------------------
    // Class
	PlayerSettings();
	~PlayerSettings();
    // ----------------------
    // GUI
	void paint(Graphics&) override;
	void resized();
    // ----------------------
    // Listeners
    void setKnobsListener(Knob::Listener* knobListenerPntr);
    // ----------------------
    // Tools
    void resetDefaultValues();
    bool isGranularMode(GranularMode);
    bool isRunningMode(RunningMode);
    bool isMidiMode(MidiMode);
    bool isWindowType(WindowType);
    // ----------------------
    // Getters
    int getNumGrains();
    int getGrainLength();
    float getGrainPitch();
    float getGrainOffset();
    float getVolume();
    float getPan(int channel);
    PlayerSettings::GranularMode getGranularMode();
    PlayerSettings::WindowType getWindowType();
    // ----------------------
    // Setters
    void setGuiColor(Colour colour);


private:
    // ----------------------
    RadioBox granularModeRadioBox{ "MODE", C_MARINE, GRANULAR_MODE };
    RadioBox runningModeRadioBox{ "CURSOR", C_LAVENDER_ROSE, RUNNING_MODE };
    RadioBox midiModeRadioBox{ "MIDI", C_CIRCUMMORBITAL, MIDI_MODE };
    RadioBox windowTypeRadioBox{ "WINDOW", C_MEDITERRANEAN, WINDOW_TYPE };
    // ----------------------
    Knob grainLengthKnob{ "LENGTH", C_MARTINA, 1, 2000, 1, 1000, true };
    Knob grainPitchKnob{ "PITCH", C_RADIANTYELLOW, 0.1, 1.9, 0.001, 1, true };
    Knob grainNumKnob{ "GRAINS", C_ENERGOS, 1, 30, 1, 2, true };
    Knob grainOffsetKnob{ "OFFSET", C_BARARED, 300, 10000, 10, 1000, true };
    Knob volumeKnob{ "VOLUME", C_SUNFLOWER, 0, 100, 0.01, 50, true };
    Knob panKnob{ "PAN", C_BILLS, 0, 100, 1, 50, true };
    // ----------------------
	Colour guiColour;
    OwnedArray<Separator> separators;
};
