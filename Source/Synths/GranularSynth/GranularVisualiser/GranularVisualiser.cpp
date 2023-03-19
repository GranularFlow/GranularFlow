#include "GranularVisualiser.h"

GranularVisualiser::GranularVisualiser()
{
    
}

GranularVisualiser::~GranularVisualiser()
{
    ringBufferPointer = nullptr;
}

void GranularVisualiser::paint(Graphics& g) {
    // Draw outlines

    g.fillAll(G_DARK);

    // Draw samples
    if (waveformSet){
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

void GranularVisualiser::setPntr(std::shared_ptr<RingBuffer> ringPointer)
{
    ringBufferPointer = ringPointer;
}

void GranularVisualiser::setWaveCallback()
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