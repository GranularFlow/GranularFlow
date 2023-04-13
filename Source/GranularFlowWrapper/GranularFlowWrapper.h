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
#include "../LFOs/MathLFO/MathLFO.h"
#include "../LFOs/WavetableLFO/WavetableLFO.h"

class GranularFlowWrapper : public Component, public Slider::Listener, public ResetButton::Listener, public Knob::Listener, public Timer
{
public:
    // ----------------------
    // Class
    GranularFlowWrapper();
	~GranularFlowWrapper();
    // ----------------------
    // GUI
    void paintJacks(Graphics&);
    void paintCables(Graphics&);
    void paint(Graphics&)override;
    void resized();
    // ----------------------
    // Process
    void prepareToPlay(float, int);
    void processBlock(AudioBuffer<float>&, MidiBuffer&);
    // ----------------------
    // Listeners
    void sliderValueChanged(Slider*)override;
    void reseted(ResetButton*)override;
    void setKnobToLfo(Knob*, int)override;
    void removeKnobFromLfo(Knob*, int)override;
    void timerCallback();
    // ----------------------
    // Tools
    void initGui();
    void makeWindowsIgnoreClicks();
    // -- LISTENERS
    void addAllListeners();
    void removeAllListeners();
    // ----------------------
    void removeThisFromAllListeners();
    void closeWindows();
    void minimizeWindows();
    void mouseDown(const MouseEvent&);
    // ----------------------
    /*ADDD ALL KNOBS*/
    void setAllKnobs();
private:
    // ----------------------
    int colorLfoTimer = 0;
    int bounceLfoTimer = 0;
    int mathLfoTimer = 0;
    int wavetableLfoTimer = 0;
    // CursorMovement
    int granularPlayerTimer = 0;
    // Visualiser repaint
    int granularRepaintTimer = 0;
    // Visualiser repaint
    int additiveRepaintTimer = 0;
    // Bounce ball movement
    int bounceLfoBallMoveTimer = 0;
    // ColorLFO repaint
    int colorLfoRepaintTimer = 0;
    // Ball speed repaint
    int bounceLfoRepaintTimer = 10;
    
    // -------------------------------------------------------
    // PROCESS
    // ----------------------
    Path cableWavetable;
    Path cableGranular;
    Path cableAdditive;
    // ----------------------
    bool processWavetable = false;
    bool processGranular = false;
    bool processAdditive = false;
    bool additiveBoxIsVisible = false;
    // ----------------------
    juce::Rectangle<float> cableColorLfo;
    juce::Rectangle<float> cableBounceLfo;
    juce::Rectangle<float> cableMathLfo;
    juce::Rectangle<float> cableWavetableLfo;
    // ----------------------
    bool processColorLfo = false;
    bool processBounceLfo = false;
    bool processMathLfo = false;
    bool processWavetableLfo = false;
    // -------------------------------------------------------
    // LFOS
    std::unique_ptr<ColorLFO> colorLfo = std::make_unique<ColorLFO>();
    std::unique_ptr<BounceLFO> bounceLfo = std::make_unique<BounceLFO>();
    std::unique_ptr<MathLFO> mathLfo = std::make_unique<MathLFO>();
    std::unique_ptr<WavetableLFO> wavetableLfo = std::make_unique<WavetableLFO>();
    // -------------------------------------
    // Synths
    std::unique_ptr<WavetableSynth> wavetableSynth = std::make_unique<WavetableSynth>();
    std::unique_ptr<GranularSynth> granularSynth = std::make_unique<GranularSynth>();
    std::unique_ptr<AdditiveSynth> additiveSynth = std::make_unique<AdditiveSynth>();
    // -------------------------------------
    // Synth
    ResetButton wavetableSynthReset{ 40, 40, 190, 110 };
    ResetButton granularSynthReset{ 40, 40, 600, 110 };
    ResetButton additiveSynthReset{ 40, 40, 1010, 110 };
    // ----------------------
    Component::SafePointer<Component> wavetableSynthBox = new CustomClickableBox(C_PROTOSS_PYLON, "WAVETABLE", false, 320, 180, 190, 180);
    Component::SafePointer<Component> granularSynthBox = new CustomClickableBox(C_PUFFINS_BILL, "GRANULAR", false, 320, 180, 600, 180);
    Component::SafePointer<Component> additiveSynthBox = new CustomClickableBox(C_ANDROID_GREEN, "ADDITIVE", false, 320, 180, 1010, 180);
    // -------------------------------------
    // LFO
    ResetButton colorLfoReset{ 30, 30, 292, 595 };
    ResetButton bounceLfoReset{ 30, 30, 498, 595 };
    ResetButton mathLfoReset{ 30, 30, 704, 595 };
    ResetButton wavetableLfoReset{ 30, 30, 910, 595 };
    // ----------------------
    Component::SafePointer<Component> colorLfoBox = new CustomClickableBox(C_ANDROID_GREEN.darker(0.15), "COLOR LFO", false, 185, 105, 292, 630);
    Component::SafePointer<Component> bounceLfoBox = new CustomClickableBox(C_SUNFLOWER.darker(0.15), "BOUNCE LFO", false, 185, 105, 498, 630);
    Component::SafePointer<Component> mathLfoBox = new CustomClickableBox(C_VANADYL_BLUE.brighter(0.15), "MATH LFO", false, 185, 105, 704, 630);
    Component::SafePointer<Component> wavetableLfoBox = new CustomClickableBox(C_RED_PIGMENT.brighter(0.15), "WAVETABLE LFO", false, 185, 105, 910, 630);
    // -------------------------------------
    // Abstract non-visible windows that open synths
    Array<Component::SafePointer<CustomWindow>> synthWindows;
    Array<Component::SafePointer<CustomWindow>> lfoWindows;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(GranularFlowWrapper);    
};
