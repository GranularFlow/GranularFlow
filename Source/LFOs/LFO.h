#pragma once
#include <JuceHeader.h>
#include "../CustomComponents/CustomLooks/Knob.h"

class LFO
{
public:
    LFO();
    ~LFO();

    virtual void addTimerListener(Slider::Listener*) = 0;
    virtual void removeTimerListener(Slider::Listener*) = 0;
    virtual void timeCallback() = 0;

    void updateKnobs(double value);
    // Listener
    void addKnobToListeners(Knob* knobPntrIn);
    void removeKnobFromListeners(Knob* knobPntrIn);
    // -----------------------
    bool knobPntrsEmpty();

private:
    OwnedArray<Knob> knobPntrs;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(LFO);
};
