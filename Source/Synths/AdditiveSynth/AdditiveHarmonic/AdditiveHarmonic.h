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

class AdditiveHarmonic : public Component, public Timer, public Slider::Listener
{
public:
    // Class
	AdditiveHarmonic(int);
	~AdditiveHarmonic() override;
    //GUI
    void paint(Graphics& g) override;
    void resized() override;
    // Listeners
    void addListeners();
    void removeListeners();
    void timerCallback() override;
    void sliderValueChanged(Slider*)override;
    // Tools
    void fillNextBuffer(AudioBuffer<float>&, juce::MidiBuffer&);
    void changeTimer(float);
    void setSampleRate(int);
    void calculateDelta();
    void handleMidi(MidiBuffer&);
    double getPhaseRads();
    double getPi();


private:
    int sampleRate = 48000;
    float phase = 0;
    float frequency = 440.0f;
    double angle = 0.0;
    double delta = 0.0;
    int lastMidiNote = -1;
    bool midiNoteOn = false;
    float midiNoteFrequency = 0.f;
    bool lastMidiMode = false;
    AdditiveHarmonicSettings harmonicSettings;
};
