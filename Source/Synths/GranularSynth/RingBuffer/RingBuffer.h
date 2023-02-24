/*
  ==============================================================================

    RingBuffer.h
    Created: 25 Jan 2023 8:32:50pm
    Author:  honza

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class RingBuffer
{
public:
	RingBuffer();
	~RingBuffer();
    void addBuffer(AudioBuffer<float>&);
    void fillBuffer(AudioBuffer<float>&);
    AudioBuffer<float>& getBuffer();   
    
private:
    int maxSamples = 144000;
    AudioBuffer<float> ringBuffer { 2, 144000 };
    int writePosition = 77000;
    int readPosition = 0;
};

