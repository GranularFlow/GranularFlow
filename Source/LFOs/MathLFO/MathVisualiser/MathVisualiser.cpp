/*
  ==============================================================================

    MathVisualiser.cpp
    Created: 20 Feb 2023 9:02:16pm
    Author:  honza

  ==============================================================================
*/

#include "MathVisualiser.h"

MathVisualiser::MathVisualiser()
{
    samples.clear();
}

MathVisualiser::~MathVisualiser()
{
}

void MathVisualiser::initGui()
{
}

void MathVisualiser::paint(Graphics& g)
{
    g.fillAll(L_GRAY);
    g.setColour(C_WHITE);
    if (samples.size() == 256)
    {
        int sampleCount = 256;
        float yOffset = 200.f;
        int step = std::ceil(1000 / (float)sampleCount);
        int index = 0;

        Path p;
        p.startNewSubPath(0, yOffset);

        for (int i = 0; i < sampleCount; i++) {
            DBG("samples[i]" << samples[i]);
            float y = yOffset - (yOffset * samples[i]); // 0 ; 200
            p.lineTo(index, y);
            //g.drawLine(index, y, index, yOffset, 2.0f); // Draw from peak to middle
            index+=step;
        }
        g.strokePath(p, PathStrokeType(PathStrokeType::curved), AffineTransform::identity);
    }
}

void MathVisualiser::setSamples(Array<float> samplesIn)
{
    samples.clear();
    samples.addArray(samplesIn);

    repaint();
}

Array<float> MathVisualiser::getSamples()
{
    return samples;
}
