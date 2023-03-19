#include "Visualiser.h"

Visualiser::Visualiser()
{
}

Visualiser::~Visualiser()
{
}

void Visualiser::paint(Graphics& g)
{
    g.fillAll(M_DARK);

    g.setColour(C_WHITE);
    
    int sampleCount = waveForm.size();
    float yOffset = getHeight() / 2;
    float step = getWidth() / (float)sampleCount;
    float index = 0;

    Path p;
    p.startNewSubPath(0, yOffset);

    for (int i = 0; i < sampleCount; i++) {
        float y = yOffset - (yOffset * waveForm[i]);
        p.lineTo(index, y);
        index += step;
    }
    g.strokePath(p, PathStrokeType(PathStrokeType::curved), AffineTransform::identity);
}

void Visualiser::setWaveForm(Array<float> inputArray)
{
    waveForm.clear();
    waveForm = inputArray;
    repaint();
}
