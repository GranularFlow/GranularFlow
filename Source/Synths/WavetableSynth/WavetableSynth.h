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
#include "WavetableSynthSettings/WavetableSynthSettings.h"
#include "Canvas/Canvas.h"
#include "Visualiser/Visualiser.h"

#include "../../LFOs/LFO.h"
#include "../Synth.h"

class WavetableSynth : public Component, public Button::Listener, public Slider::Listener, public Synth
{
public:
    // Class
	WavetableSynth(LFO*);
	~WavetableSynth();

    // Listeners
    void addListeners();
    void removeListeners();
    void sliderValueChanged(Slider*) override;
    void buttonClicked(Button*) override;

    // GUI
    void paint(Graphics&) override;
    void resized()override;
    
    // --------
    void prepareToPlay(float, int)override;
    void processBlock(AudioBuffer<float>&, MidiBuffer&)override;
    // --------
   
    // Tools
    void initSamples();
    float interpolate(float x, float x1, float x2, float y1, float y2);
    float cubicInterpolate(float);
    double interpolateHermite(double);
    void handleMidi(MidiBuffer&);

private:
    LFO* colorLfoPntr = nullptr;
    TextButton combineButton{ "SYNTHESIZE" };
    Canvas canvas1 { "FIRST WAVE" };
    Canvas canvas2 { "SECOND WAVE" };
    Canvas canvas3 { "THIRD WAVE" };
    Visualiser canvas4;
    WavetableSynthSettings wavetableSettings;
    Array<float> sampleY;
    Array<float> sampleX;

    float frequency = 440;
    float sampleRate = 48000;

    bool midiNoteOn = false;
    int lastMidiNote = -1;
    int midiNoteFrequency = 0;
    int currentPosition = 0;
    float increment = 1.0;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(WavetableSynth);
};
