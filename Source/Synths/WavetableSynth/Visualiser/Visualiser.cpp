#include "Visualiser.h"

Visualiser::Visualiser()
{
    setOpaque(true);
}

Visualiser::~Visualiser()
{
}

void Visualiser::paint(Graphics& g)
{
   // DBG("Visualiser::paint");
    g.fillAll(Colour::fromRGB(70, 70, 70));
    g.setColour(Colours::white);
    if (waveForm.size() > 0)
    {
        Path p;
        p.startNewSubPath(0, (getHeight() / 2.f));

        for (int i = 0; i < waveForm.size(); i++) {
            p.lineTo((getWidth() / (float)waveForm.size()) * i, (getHeight()/2.f) * (1 - waveForm[i]));
        }
        g.strokePath(p, PathStrokeType(PathStrokeType::curved), AffineTransform::identity);
    }
}

void Visualiser::setWaveForm(Array<float> inputArray)
{
    waveForm.clear();
    waveForm = inputArray;
    repaint();
    setBufferedToImage(true);
}
