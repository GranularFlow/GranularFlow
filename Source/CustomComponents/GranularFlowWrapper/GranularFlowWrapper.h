/*
  ==============================================================================

    Wrapper.h
    Created: 21 Feb 2023 3:43:03pm
    Author:  honza

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "../../Utils/Constants.h"
#include "../CustomWindow/CustomWindow.h"
#include "../CustomLfoPanel/CustomLfoPanel.h"
#include "../CustomClickableBox/CustomClickableBox.h"
#include "../../Synths/WavetableSynth/WavetableSynth.h"
#include "../../Synths/GranularSynth/GranularSynth.h"
#include "../../Synths/AdditiveSynth/AdditiveSynth.h"


class GranularFlowWrapper : public Component
{
public:
    // Class
    GranularFlowWrapper();
	~GranularFlowWrapper();
    // GUI
    void paint(Graphics&)override;
    void resized();

    // Process
    void prepareToPlay(float);
    void processBlock(juce::AudioBuffer<float>&, juce::MidiBuffer&);

    // Tools
    void closeWindows();
    void minimizeWindows();
    void mouseDown(const MouseEvent&);

private:
    Path cableWavetable;
    Path cableGranular;
    Path cableAdditive;
    

    bool processWavetable = false;
    bool processGranular = false;
    bool processAdditive = false;

    // GUI windows
    Component::SafePointer<Component> wavetableSynthBox = new CustomClickableBox(C_MARINE, "WAVETABLE SYNTH");
    Component::SafePointer<Component> granularSynthBox = new CustomClickableBox(C_BILLS, "GRANULAR SYNTH");
    Component::SafePointer<Component> additiveSynthBox = new CustomClickableBox(C_ANDROID, "ADDITIVE SYNTH");

    CustomLfoPanel lfoPanel;

    // Synths
    Component::SafePointer<Component> wavetableSynth = new WavetableSynth;
    Component::SafePointer<Component> granularSynth = new GranularSynth;
    Component::SafePointer<Component> additiveSynth = new AdditiveSynth;

    // Open windows
    Array<Component::SafePointer<CustomWindow>> windows;
};
