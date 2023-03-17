#pragma once
#include <JuceHeader.h>
#include "../CustomComponents/CustomLooks/Knob.h"

class LFO
{
public:
	LFO() {}
	~LFO() {
        knobPntrs.clear();
    }

    virtual void addTimerListener(Slider::Listener*) = 0;
    virtual void removeTimerListener(Slider::Listener*) = 0;

    virtual void timeCallback() = 0;
    void updateKnobs(double value) {
        for (Knob* knob : knobPntrs)
        {
            if (knob != nullptr)
            {
                knob->setLfoValue(value);
            }
        }
    }
    // Listener
    void addKnobToListeners(Knob* knobPntrIn) { knobPntrs.add(knobPntrIn); }
    void removeKnobFromListeners(Knob* knobPntrIn) {
        int index = -666;

        for (int i = 0; i < knobPntrs.size(); i++)
        {
            if (knobPntrs[i] == knobPntrIn)
            {
                index = i;
            }
        }

        if (index != -666)
        {
            knobPntrs.remove(index, false);
        }
    }
    // -----------------------
    bool knobPntrsEmpty() { return knobPntrs.isEmpty(); }

private:
    OwnedArray<Knob> knobPntrs;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(LFO);
};
