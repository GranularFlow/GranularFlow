#include "MathVisualiser.h"

MathVisualiser::MathVisualiser()
{
    samples.clear();
    setOpaque(true);
}

MathVisualiser::~MathVisualiser()
{
}

void MathVisualiser::initGui()
{
}

void MathVisualiser::paint(Graphics& g)
{
    g.fillAll(Colour::fromRGB(50, 50, 50));
    g.setColour(Colours::white);
    if (samples.size() > 0)
    {
        Path p;
        p.startNewSubPath(0, getHeight());

        for (int i = 0; i < samples.size(); i++) {
            p.lineTo((getWidth() / (float)samples.size()) * i, (getHeight()) * (1 - samples[i]));
        }
        g.strokePath(p, PathStrokeType(PathStrokeType::curved), AffineTransform::identity);
    }
    setBufferedToImage(true);
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
