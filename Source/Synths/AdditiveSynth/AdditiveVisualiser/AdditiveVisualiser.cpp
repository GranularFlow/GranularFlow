#include "AdditiveVisualiser.h"


AdditiveVisualiser::AdditiveVisualiser()
{

}

AdditiveVisualiser::~AdditiveVisualiser()
{
}

void AdditiveVisualiser::paint(Graphics& g) {
    // Draw outlines

    g.fillAll(G_DARK);

    // Draw samples
    if (waveformSet) {
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
}

void AdditiveVisualiser::repaintCallBack()
{
    repaint();
}



void AdditiveVisualiser::setWaveForm(AudioBuffer<float>& audioBuffer) {

    waveForm.clear();

    const float* leftChannel = audioBuffer.getReadPointer(0);
    const float* rightChannel = audioBuffer.getReadPointer(1);

    for (int i = 0; i < audioBuffer.getNumSamples(); ++i) {
        waveForm.add(leftChannel[i] > rightChannel[i] ? leftChannel[i] : rightChannel[i]);
    }

    waveformSet = true;
}