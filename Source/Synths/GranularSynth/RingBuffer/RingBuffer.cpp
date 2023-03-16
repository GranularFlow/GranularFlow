/*
  ==============================================================================

    RingBuffer.cpp
    Created: 25 Jan 2023 8:32:50pm
    Author:  honza

  ==============================================================================
*/

#include "RingBuffer.h"

RingBuffer::RingBuffer()
{
    ringBuffer.clear();
}

RingBuffer::~RingBuffer()
{
    
}

void RingBuffer::addBuffer(AudioBuffer<float>& inputBuffer)
{
    for (int i = 0; i < inputBuffer.getNumSamples(); i++)
    {
        ringBuffer.setSample(0, writePosition, inputBuffer.getSample(0, i));
        ringBuffer.setSample(1, writePosition, inputBuffer.getSample(0, i));
        writePosition = (writePosition + 1) % BUFFER_SAMPLES;
    }
}

AudioBuffer<float>& RingBuffer::getBuffer()
{
    return ringBuffer;
}

int RingBuffer::getSize()
{
    return readPosition;
}

bool RingBuffer::readyToBeConsumed()
{
    return readPosition == 100;
}
