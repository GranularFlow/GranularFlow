/*
  ==============================================================================

    AdditiveSynth.h
    Created: 1 Feb 2023 9:36:43pm
    Author:  honza

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "../../Utils/Constants.h"
#include "../../CustomComponents/CustomLooks/Knob.h"
#include "AdditiveSynthSettings/AdditiveSynthSettings.h"
#include "AdditiveHarmonic/AdditiveHarmonic.h"
#include "AdditiveVisualiser/AdditiveVisualiser.h"
#include "../Synth.h"

class AdditiveSynth : public Component, public Slider::Listener, public Synth
{
public:
    // Class
	AdditiveSynth();
	~AdditiveSynth();
    // GUI
    void paint(Graphics&) override;
    void resized()override;
    // Listeners
    void sliderValueChanged(Slider*) override;
    // ----------------------
    // ProcessBlock
    // ----------------------
    void prepareToPlay(float, int)override;
    void processBlock(AudioBuffer<float>&, juce::MidiBuffer&)override;
    // ----------------------    
    // Tools
    void addNewHarmonic();
    void removeHarmonic();
    void selectHarmonic(int);    
    // Get
    // Set
    void setKnobsListener(Knob::Listener*) override;
    void removeKnobsListener()override;
    
private:

    int activeHarmonics = 0;
    int selectedHarmonic = 0;

    AdditiveSynthSettings settings;
    AdditiveVisualiser visualiser;
    OwnedArray<AdditiveHarmonic> harmonics;
};
