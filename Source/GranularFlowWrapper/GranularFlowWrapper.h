/*
  ==============================================================================

    Wrapper.h
    Created: 21 Feb 2023 3:43:03pm
    Author:  honza

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "../Utils/Constants.h"
#include "../CustomComponents/CustomWindow/CustomWindow.h"
#include "../CustomComponents/CustomClickableBox/CustomClickableBox.h"
#include "../CustomComponents/CustomLooks/ResetButton.h"
#include "../Synths/WavetableSynth/WavetableSynth.h"
#include "../Synths/GranularSynth/GranularSynth.h"
#include "../Synths/AdditiveSynth/AdditiveSynth.h"
#include "../LFOs/LFO.h"
#include "../LFOs/ColorLFO/ColorLFO.h"

class GranularFlowWrapper : public Component, public ResetButton::ResetListener
{
public:
    // Class
    GranularFlowWrapper();
	~GranularFlowWrapper();

    // GUI
    void paint(Graphics&)override;
    void resized();

    // Process
    void prepareToPlay(float, int);
    void processBlock(AudioBuffer<float>&, MidiBuffer&);

    // Listeners
    void reseted(ResetButton*)override;

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

    // LFOS
    std::unique_ptr<ColorLFO> colorLfo = std::make_unique<ColorLFO>();

    // Synths
    std::unique_ptr<WavetableSynth> wavetableSynth = std::make_unique<WavetableSynth>();
    std::unique_ptr<GranularSynth> granularSynth = std::make_unique<GranularSynth>();
    std::unique_ptr<AdditiveSynth> additiveSynth = std::make_unique<AdditiveSynth>();


    // GUI ONLY
    // Synth
    ResetButton wavetableSynthReset;
    ResetButton granularSynthReset;
    ResetButton additiveSynthReset;

    Component::SafePointer<Component> wavetableSynthBox = new CustomClickableBox(C_MARINE, "WAVETABLE SYNTH", false);
    Component::SafePointer<Component> granularSynthBox = new CustomClickableBox(C_BILLS, "GRANULAR SYNTH", false);
    Component::SafePointer<Component> additiveSynthBox = new CustomClickableBox(C_ANDROID, "ADDITIVE SYNTH", false);
    // LFO
    Component::SafePointer<Component> colorLfoBox = new CustomClickableBox(C_MARINE, "COLOR LFO", true);
    Component::SafePointer<Component> bounceLfoBox = new CustomClickableBox(C_BILLS, "BOUNCE LFO", true);
    Component::SafePointer<Component> mathLfoBox = new CustomClickableBox(C_ANDROID, "MATH LFO", true);
    Component::SafePointer<Component> wavetableLfoBox = new CustomClickableBox(C_ANDROID, "WAVETABLE LFO", true);


    // Abstract non-visible windows that open synths
    Array<Component::SafePointer<CustomWindow>> windows;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(GranularFlowWrapper);    
};
