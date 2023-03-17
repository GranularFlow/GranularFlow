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
    if (samples.size() > 0)
    {
        int sampleCount = samples.size();
        float yOffset = getHeight() / 2;
        float step = getWidth() / (float)sampleCount;
        float index = 0;

        Path p;
        p.startNewSubPath(0, yOffset);

        for (int i = 0; i < sampleCount; i++) {
            float y = yOffset - (yOffset * samples[i]);
            p.lineTo(index, y);
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
