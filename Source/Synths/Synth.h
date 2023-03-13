/*
  ==============================================================================

    Synth.h
    Created: 3 Mar 2023 8:00:12pm
    Author:  honza

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "../CustomComponents/CustomLooks/Knob.h"

class Synth
{
public:
    virtual void prepareToPlay(float, int) = 0;
    virtual void processBlock(AudioBuffer<float>&, MidiBuffer&) = 0;
    virtual void setKnobsListener(Knob::Listener* knobListenerPntr) = 0;
    virtual void removeKnobsListener() = 0;
private:

};
