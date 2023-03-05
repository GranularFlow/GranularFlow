/*
  ==============================================================================

    LFO.h
    Created: 1 Mar 2023 8:47:41pm
    Author:  honza

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "../CustomComponents/CustomLooks/Knob.h"

class LFO
{
public:
	LFO() {}
	~LFO() {

    }

    void updateKnobs(double value) {
        for (Knob* knob : knobPntrs)
        {
            if (knob != nullptr)
            {
                knob->setLfoValue(value);
            }
        }
    }
    void addKnobToListeners(Knob* knobPntrIn) { knobPntrs.add(knobPntrIn); }
    void removeKnobFromListeners(Knob* knobPntrIn) {
        DBG("knobPntrs.size() "<< knobPntrs.size());
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

        DBG("removed? ");
        DBG("knobPntrs.size() " << knobPntrs.size());
    }
    OwnedArray<Knob> knobPntrs;
    
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(LFO);
};
