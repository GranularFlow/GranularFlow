#include "AdditiveVisualiser.h"


AdditiveVisualiser::AdditiveVisualiser()
{
    setOpaque(true);
    for (size_t i = 0; i < 10; i++)
    {
        waveForm.add(0);
    }
}

AdditiveVisualiser::~AdditiveVisualiser()
{
}

void AdditiveVisualiser::paint(Graphics& g) {

   // DBG("AdditiveVisualiser::paint");
    g.fillAll(Colour::fromRGB(45, 45, 45));
    g.setColour(Colours::white);

    Path p;
    p.startNewSubPath(0, getHeight() / 2.f);

    for (int i = 0; i < waveForm.size(); i++) {
        p.lineTo((getWidth() / (float)waveForm.size()) * i, ((getHeight() / 2.f) * (1 - waveForm[i])));
    }
    g.strokePath(p, PathStrokeType(PathStrokeType::curved), AffineTransform::identity);
}

void AdditiveVisualiser::repaintCallBack()
{
    repaint();
    setBufferedToImage(true);
}



void AdditiveVisualiser::setWaveForm(AudioBuffer<float>& audioBuffer) {

    waveForm.clear();

    const float* leftChannel = audioBuffer.getReadPointer(0);
    const float* rightChannel = audioBuffer.getReadPointer(1);

    for (int i = 0; i < audioBuffer.getNumSamples(); ++i) {
        waveForm.add(leftChannel[i] > rightChannel[i] ? leftChannel[i] : rightChannel[i]);
    }
    
}