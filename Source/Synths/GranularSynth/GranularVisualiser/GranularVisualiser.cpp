/*
  ==============================================================================

    GranularVisualiser.cpp
    Created: 31 Oct 2022 10:50:00pm
    Author:  honza

  ==============================================================================
*/

#include "GranularVisualiser.h"

GranularVisualiser::GranularVisualiser()
{
    
}

GranularVisualiser::~GranularVisualiser()
{
    stopTimer();
    ringBufferPointer = nullptr;
    DBG("~GranularVisualiser");
}

void GranularVisualiser::paint(Graphics& g) {
    // Draw outlines
    g.setColour(L_GRAY);
    g.drawLine(0, 0, getWidth(), 0, 2.0);
    g.drawLine(0, getHeight(), getWidth(), getHeight(), 2.0);

    // Draw samples
    if (waveformSet){
        g.setColour(C_WHITE);       

        int sampleCount = waveForm.size();
        float yOffset = (float)getHeight() / (float) 2;
        int step = std::ceil( (float)sampleCount / (float)getWidth());
        int index = 0;

        Path p;
        p.startNewSubPath(0, yOffset);

        for (int i = 0; i < sampleCount; i+= step) {
            float y = yOffset + (yOffset * (-waveForm[i])); // 0 ; 200
            if (y > 200 || y < 0)
            {
                y = yOffset;
            }
            p.lineTo(index, y);
            //g.drawLine(index, y, index, yOffset, 2.0f); // Draw from peak to middle
            index++;
            if (i + step > sampleCount){
                break;
            }
        }
        g.strokePath(p, PathStrokeType(PathStrokeType::curved), AffineTransform::identity);     
        
    }
}

void GranularVisualiser::setPntr(RingBuffer* ringPointer)
{
    ringBufferPointer = ringPointer;
    startTimer(1000);
}

void GranularVisualiser::timerCallback()
{
    if (ringBufferPointer != nullptr)
    {
        setWaveForm(ringBufferPointer->getBuffer());
    }
}

void GranularVisualiser::setWaveForm(AudioBuffer<float>& audioBuffer) {

    waveForm.clear();

    const float* leftChannel = audioBuffer.getReadPointer(0);
    const float* rightChannel = audioBuffer.getReadPointer(1);

    for (int i = 0; i < audioBuffer.getNumSamples(); ++i) {
        waveForm.add(leftChannel[i] > rightChannel[i] ? leftChannel[i] : rightChannel[i]);
    }

    waveformSet = true;
    repaint();
}