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
    // Listeners
    void addSlidersListener(Slider::Listener*);
    void removeSlidersListener(Slider::Listener*);
    void setKnobsListener(Knob::Listener*);
    void removeKnobsListener();
    // Getters
    float getFreq();
    float getWaveCount();
    float getVolume();
    float getPan(int);
    // Tools
    bool isCurrentMidiMode(WavetableSynthSettings::MidiMode);
    bool isCurrentInterpolationType(WavetableSynthSettings::InterpolationType);
    bool isWaveCountKnobSlider(Slider*);
    bool isFreqKnobSlider(Slider*);
    Knob& getWaveCountKnob();


private:
    RadioBox midiModeRadioBox { "MIDI", C_SUNFLOWER, MIDI_MODE };
    Knob freqKnob { "FREQUENCY", C_SUNFLOWER, 20, 8000, 0.001, 400, true };
    Knob waveCountKnob { "WAVE COUNT", C_SUNFLOWER, 2, 10, 2, 6 , true };
    RadioBox interpolationRadioBox { "ITERPOLATION", C_SUNFLOWER, INTERPOLATION_TYPE };
    Knob volumeKnob { "VOLUME", C_SUNFLOWER, 0, 100, 0.1, 50, true };
    Knob panKnob { "PAN", C_BILLS, 0, 100, 0.5, 50, true };
    // GUI
    Colour guiColour;
    OwnedArray<Separator> separators;


};
