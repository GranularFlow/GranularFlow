/*
  ==============================================================================

    GranularVisualiser.h
    Created: 31 Oct 2022 10:49:50pm
    Author:  honza

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "../../../Utils/Constants.h"
#include "../RingBuffer/RingBuffer.h"

class GranularVisualiser : public Component, public Timer
{
public:
    // Class
    GranularVisualiser();
	~GranularVisualiser();
    // GUI
    void paint(Graphics& g) override;
    // Callbacks
    void setPntr(RingBuffer*);
    void timerCallback() override;
    // Setters
    void setWaveForm(AudioBuffer<float>&);

private:
    RingBuffer* ringBufferPointer = nullptr;
    Array<float> waveForm;
    bool waveformSet = false;
};

