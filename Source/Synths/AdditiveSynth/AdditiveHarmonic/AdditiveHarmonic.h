/*
  ==============================================================================

    AdditiveHarmonic.h
    Created: 1 Feb 2023 11:01:49pm
    Author:  honza

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "AdditiveHarmonicSettings/AdditiveHarmonicSettings.h"
#include "../../../CustomComponents/CustomLooks/Knob.h"

class AdditiveHarmonic : public Component, public Slider::Listener
{
public:
    // Class
	AdditiveHarmonic();
	~AdditiveHarmonic() override;
    //GUI
    void paint(Graphics& g) override;
    void resized() override;
    // Listeners
    void sliderValueChanged(Slider*) override;
    // Tools
    void prepareToPlay(float, int);
    void processBlock(AudioBuffer<float>&, juce::MidiBuffer&);

    
    void calculateDelta();
    void handleMidi(MidiBuffer&);
    void setAngle(double);
    double getAngle();
    void reset();
    void setKnobsListener(Knob::KnobListener* knobListenerPntr);
    void removeKnobsListener();
private:
    // Wave parameters
    int sampleRate = SAMPLE_RATE;
    double phase = 0;
    float frequency = 440.0f;
    double angle = 0.0;
    double delta = 0.0;
    //
    int8 lastMidiNote = -1;
    bool midiNoteOn = false;
    float midiNoteFrequency = 0.f;
    bool lastMidiMode = false;
    AdditiveHarmonicSettings settings;
};
