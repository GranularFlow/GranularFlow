#pragma once
#include <JuceHeader.h>
#include "AdditiveHarmonicSettings/AdditiveHarmonicSettings.h"
#include "../../../CustomComponents/CustomLooks/Knob.h"

class AdditiveHarmonic : public Component, public Slider::Listener
{
public:
    // ----------------------
    // Class
	AdditiveHarmonic();
	~AdditiveHarmonic() override;
    // ----------------------
    //GUI
    void paint(Graphics& g) override;
    void resized() override;
    // ----------------------
    // Listeners
    // --- Knobs
    void setKnobsListener(Knob::Listener* knobListenerPntr);
    void removeKnobsListener();
    void sliderValueChanged(Slider*) override;
    // ----------------------
    // Process
    void prepareToPlay(float, int);
    void processBlock(AudioBuffer<float>&, juce::MidiBuffer&);
    // ----------------------
    // Get
    double getAngle();
    // ----------------------
    // Set
    void setAngle(double);
    void reset();
    // ----------------------
    // Tools    
    void calculateDelta();
    void handleMidi(MidiBuffer&);    
private:
    // ----------------------
    // To calculate next sample 
    float frequency = 440.0f;
    double phase = 0;    
    double angle = 0.0;
    double delta = 0.0;
    // ----------------------
    // MIDI
    int lastMidiNote = -1;
    bool midiNoteOn = false;
    float midiNoteFrequency = 0.f;
    // ----------------------
    AdditiveHarmonicSettings settings;
};
