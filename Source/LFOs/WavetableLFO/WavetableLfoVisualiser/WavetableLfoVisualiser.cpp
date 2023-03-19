#include "WavetableLfoVisualiser.h"

WavetableLfoVisualiser::WavetableLfoVisualiser()
{
}

WavetableLfoVisualiser::~WavetableLfoVisualiser()
{
}

void WavetableLfoVisualiser::paint(Graphics& g)
{
    g.fillAll(C_GRAY);

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

void WavetableLfoVisualiser::setWaveForm(Array<float> inputArray)
{
    waveForm.clear();
    waveForm = inputArray;
    repaint();
}
