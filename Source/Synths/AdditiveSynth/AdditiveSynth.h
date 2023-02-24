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
#include "AdditiveSynthSettings/AdditiveSynthSettings.h"
#include "AdditiveHarmonic/AdditiveHarmonic.h"
#include "AdditiveVisualiser/AdditiveVisualiser.h"
class AdditiveSynth : public Component, public Slider::Listener, public Button::Listener
{
public:
    // Class
	AdditiveSynth();
	~AdditiveSynth();
    // GUI
    void initGui();
    void paint(Graphics&) override;
    void resized()override;
    // Listeners
    void sliderValueChanged(Slider*) override;
    void buttonClicked(Button*) override;
    void addListeners();
    void removeListeners();

    // Tools
    void addNewHarmonic();
    void removeHarmonic();
    void selectHarmonic(int);

    // Getters
    void getNextBlock(AudioBuffer<float>&, juce::MidiBuffer&);
    // Setters
    void prepareToPlay(double, int);
private:
    int sampleRate = 48000;
    int bufferSize = 256;
    AdditiveSynthSettings additiveSynthSettings;
    AdditiveVisualiser additiveVisualiser;
    OwnedArray<AdditiveHarmonic> additiveHarmonics;

};
