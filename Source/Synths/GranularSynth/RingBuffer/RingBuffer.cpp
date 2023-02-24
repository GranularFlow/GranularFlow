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
        writePosition = (writePosition + 1) % maxSamples;
    }
}

void RingBuffer::fillBuffer(AudioBuffer<float>& bufferToFill)
{
    bufferToFill.addFrom(0, 0, ringBuffer, 0, readPosition, bufferToFill.getNumSamples());
    bufferToFill.addFrom(1, 0, ringBuffer, 1, readPosition, bufferToFill.getNumSamples());
    readPosition = (readPosition + bufferToFill.getNumSamples()) % maxSamples;
}

AudioBuffer<float>& RingBuffer::getBuffer()
{
    return ringBuffer;
}
