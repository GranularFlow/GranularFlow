/*
  ==============================================================================

    WavetableLfoVisualiser.cpp
    Created: 5 Feb 2023 2:53:14pm
    Author:  honza

  ==============================================================================
*/

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
    float yOffset = (float)getHeight() / (float)2;
    float step = (float)getWidth() / (float)sampleCount;
    int index = 0;

    for (int sampleIndex = 0; sampleIndex < sampleCount; sampleIndex++)
    {
        int y = yOffset + (yOffset * (-waveForm[sampleIndex]));

        if (y < 0 || y > getHeight())
        {
            y = yOffset;
        }

        g.fillRect((float)step * sampleIndex, (float)y, (float)2, (float)2);
    }
}

void WavetableLfoVisualiser::setWaveForm(Array<float> inputArray)
{
    waveForm.clear();
    waveForm = inputArray;
    repaint();
}
