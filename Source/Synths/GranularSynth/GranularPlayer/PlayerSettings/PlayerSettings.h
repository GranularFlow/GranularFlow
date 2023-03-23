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
    // ----------------------
    // Getters
    int getNumGrains();
    int getGrainLength();
    float getGrainPitch();
    float getGrainOffset();
    float getVolume();
    float getPan(int channel);
    PlayerSettings::GranularMode getGranularMode();
    PlayerSettings::RunningMode getRunningMode();
    PlayerSettings::MidiMode getMidiMode();
    PlayerSettings::WindowType getWindowType();
    // ----------------------
    // Setters
    void setGuiColor(Colour colour);
private:
    // ----------------------
    RadioBox granularModeRadioBox{ "MODE", Colour::fromRGB(0, 168, 255), {"ORDER", "REV.ORDER", "MIRROR", "REV.MIRROR"} };
    RadioBox runningModeRadioBox{ "CURSOR", Colour::fromRGB(253, 167, 223), {"STATIC", "RUNNING"} };
    RadioBox midiModeRadioBox{ "MIDI", Colour::fromRGB(87, 88, 187), {"OFF", "ON"} };
    RadioBox windowTypeRadioBox{ "WINDOW", Colour::fromRGB(18, 137, 167), { "HALF SINE", "HANN", "TRIANGLE"} };
    // ----------------------
    Knob grainLengthKnob{ "LENGTH", Colour::fromRGB(18, 203, 196), 1, 2000, 1, 1000, true };
    Knob grainPitchKnob{ "PITCH", Colour::fromRGB(247, 159, 31), 0.1, 1.9, 0.001, 1, true };
    Knob grainNumKnob{ "GRAINS", Colour::fromRGB(196, 229, 56), 1, 20, 1, 2, true };
    Knob grainOffsetKnob{ "OFFSET", Colour::fromRGB(237, 76, 103), 300, 10000, 10, 1000, true };
    Knob volumeKnob{ "VOLUME", Colour::fromRGB(255, 195, 18), 0, 100, 0.01, 50, true };
    Knob panKnob{ "PAN", Colour::fromRGB(238, 90, 36), 0, 100, 1, 50, true };
    // ----------------------
	Colour guiColour;
    OwnedArray<Separator> separators;
};
