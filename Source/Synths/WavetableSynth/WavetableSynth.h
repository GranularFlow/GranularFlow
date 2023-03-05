/*
  ==============================================================================

    WavetableSynth.h
    Created: 3 Feb 2023 12:45:49pm
    Author:  honza

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "../../Utils/Constants.h"
#include "../../Utils/Utils.h"
#include "../../CustomComponents/CustomLooks/Knob.h"
#include "WavetableSynthSettings/WavetableSynthSettings.h"
#include "Canvas/Canvas.h"
#include "Visualiser/Visualiser.h"

class WavetableSynth : public Component, public Button::Listener, public Slider::Listener
{
public:
    // Class
	WavetableSynth();
	~WavetableSynth();

    // Listeners
    // Slider Listener ------------------------------
    void sliderValueChanged(Slider*) override;
    // ----------------------------------------------
    // Button Listener ------------------------------
    void buttonClicked(Button*) override;
    // ----------------------------------------------

    // GUI - Component ------------------------------
    void paint(Graphics&) override;
    void resized()override;
    // ----------------------------------------------
    
    // Synth ----------------------------------------
    void prepareToPlay(float, int);
    void processBlock(AudioBuffer<float>&, MidiBuffer&);
    // ----------------------------------------------
   
    // Tools
    void initSamples();
    void handleMidi(MidiBuffer&);


    void setKnobsListener(Knob::KnobListener*);


private:
    TextButton combineButton{ "SYNTHESIZE" };
    Canvas canvas1 { "FIRST WAVE" };
    Canvas canvas2 { "SECOND WAVE" };
    Canvas canvas3 { "THIRD WAVE" };
    Visualiser canvas4;
    WavetableSynthSettings wavetableSettings;
    Array<float> sampleY;

    float frequency = 440;
    float sampleRate = 48000;

    bool midiNoteOn = false;
    int lastMidiNote = -1;
    int midiNoteFrequency = 0;
    int currentPosition = 0;
    float increment = 1.0;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(WavetableSynth);
};
