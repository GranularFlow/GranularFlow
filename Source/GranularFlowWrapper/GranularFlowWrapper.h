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
#include "../CustomComponents/CustomLooks/Knob.h"
#include "../Synths/WavetableSynth/WavetableSynth.h"
#include "../Synths/GranularSynth/GranularSynth.h"
#include "../Synths/AdditiveSynth/AdditiveSynth.h"
#include "../LFOs/LFO.h"
#include "../LFOs/ColorLFO/ColorLFO.h"
#include "../LFOs/BounceLFO/BounceLFO.h"
//#include "../LFOs/MathLFO/MathLFO.h"
#include "../LFOs/WavetableLFO/WavetableLFO.h"

class GranularFlowWrapper : public Component, public ResetButton::ResetListener, public Knob::KnobListener
{
public:
    // Class
    GranularFlowWrapper();
	~GranularFlowWrapper();

    // GUI
    void paintJacks(Graphics&, int, int, int);
    void paintCables(Graphics&, int, int, int, int, int, int);
    void paint(Graphics&)override;
    void resized();

    // Process
    void prepareToPlay(float, int);
    void processBlock(AudioBuffer<float>&, MidiBuffer&);

    // Listeners
    void reseted(ResetButton*)override;
    void setLfoPointer(Knob*, int)override;
    void removeLfoPointer(Knob*, int)override;

    // Tools
    void closeWindows();
    void minimizeWindows();
    void mouseDown(const MouseEvent&);

    /*ADDD ALL KNOBS*/
    void setAllKnobs();


private:
    Path cableWavetable;
    Path cableGranular;
    Path cableAdditive;
    

    bool processWavetable = false;
    bool processGranular = false;
    bool processAdditive = false;

    // LFOS
    std::unique_ptr<ColorLFO> colorLfo = std::make_unique<ColorLFO>();
    std::unique_ptr<BounceLFO> bounceLfo = std::make_unique<BounceLFO>();
    //std::unique_ptr<MathLFO> mathLfo = std::make_unique<MathLFO>();
    std::unique_ptr<WavetableLFO> wavetableLfo = std::make_unique<WavetableLFO>();

    // Synths
    std::unique_ptr<WavetableSynth> wavetableSynth = std::make_unique<WavetableSynth>();
    std::unique_ptr<GranularSynth> granularSynth = std::make_unique<GranularSynth>();
    std::unique_ptr<AdditiveSynth> additiveSynth = std::make_unique<AdditiveSynth>();

   
    // -------------------------------------
    // GUI ONLY
    Separator topLine;
    // Synth
    ResetButton wavetableSynthReset;
    ResetButton granularSynthReset;
    ResetButton additiveSynthReset;
    Component::SafePointer<Component> wavetableSynthBox = new CustomClickableBox(C_MARINE, "WAVETABLE SYNTH", false);
    Component::SafePointer<Component> granularSynthBox = new CustomClickableBox(C_BILLS, "GRANULAR SYNTH", false);
    Component::SafePointer<Component> additiveSynthBox = new CustomClickableBox(C_ANDROID, "ADDITIVE SYNTH", false);
    // LFO
    ResetButton colorLfoReset;
    ResetButton bounceLfoReset;
    ResetButton mathLfoReset;
    ResetButton wavetableLfoReset;
    Component::SafePointer<Component> colorLfoBox = new CustomClickableBox(C_MARINE, "COLOR LFO", true);
    Component::SafePointer<Component> bounceLfoBox = new CustomClickableBox(C_BILLS, "BOUNCE LFO", true);
    Component::SafePointer<Component> mathLfoBox = new CustomClickableBox(C_ANDROID, "MATH LFO", true);
    Component::SafePointer<Component> wavetableLfoBox = new CustomClickableBox(C_ANDROID, "WAVETABLE LFO", true);
    // -------------------------------------

    // Abstract non-visible windows that open synths
    Array<Component::SafePointer<CustomWindow>> synthWindows;
    Array<Component::SafePointer<CustomWindow>> lfoWindows;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(GranularFlowWrapper);    
};
