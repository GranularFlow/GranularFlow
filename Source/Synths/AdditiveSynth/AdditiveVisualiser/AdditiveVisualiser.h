#pragma once
#include <JuceHeader.h>
#include "../../../Utils/Constants.h"

class AdditiveVisualiser : public Component
{
public:
    // -----------------------
    // Class
    AdditiveVisualiser();
    ~AdditiveVisualiser();
    // -----------------------
    // GUI
    void paint(Graphics& g) override;
    void repaintCallBack();
    // -----------------------
    // Set
    void setWaveForm(AudioBuffer<float>&);

private:
    bool waveformSet = false;
    Array<float> waveForm;
};
