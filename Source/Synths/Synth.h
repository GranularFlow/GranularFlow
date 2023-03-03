/*
  ==============================================================================

    Synth.h
    Created: 3 Mar 2023 8:00:12pm
    Author:  honza

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class Synth
{
public:
    Synth() {}
    ~Synth() {}

    virtual void prepareToPlay(float, int) = 0;
    virtual void processBlock(AudioBuffer<float>&, MidiBuffer&) = 0;

private:

};
