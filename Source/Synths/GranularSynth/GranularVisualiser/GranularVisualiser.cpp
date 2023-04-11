#include "GranularVisualiser.h"

GranularVisualiser::GranularVisualiser()
{
    setBounds(0, 60, W_WIDTH, 340);
}

GranularVisualiser::~GranularVisualiser()
{
    ringBufferPointer = nullptr;
}

void GranularVisualiser::paint(Graphics& g) {
    // Draw outlines
   // DBG("GranularVisualiser::paint");
    g.fillAll(Colour::fromRGB(45, 45, 45));

    // Draw samples
    if (waveformSet) {
        p.startNewSubPath(0, getHeight() / 2);
        for (int i = 0; i < waveForm.size(); i++) {
            float y = (getHeight() / 2) - ((getHeight() / 2) * waveForm[i]);
            p.lineTo((getWidth() / (float)waveForm.size()) * i, y);
        }
        g.setColour(Colours::white);
        g.strokePath(p, PathStrokeType(PathStrokeType::curved), AffineTransform::identity);
        p.clear();
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

    for (int i = 0; i < (int)audioBuffer.getNumSamples(); i++) {
        waveForm.add(audioBuffer.getReadPointer(0)[i] > audioBuffer.getReadPointer(1)[i] ? audioBuffer.getReadPointer(0)[i] : audioBuffer.getReadPointer(1)[i]);
    }

    waveformSet = true;
    
    repaint();
    setBufferedToImage(true);
}