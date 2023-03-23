#pragma once

#include <JuceHeader.h>
#include "../../../Utils/Constants.h"
#include "../RingBuffer/RingBuffer.h"

class GranularVisualiser : public Component
{
public:
    // -----------------------
    // Class
    GranularVisualiser();
	~GranularVisualiser();
    // -----------------------
    // GUI
    void paint(Graphics& g) override;
    // -----------------------
    // Callbacks
    void setPntr(std::shared_ptr<RingBuffer>);
    void setWaveCallback();
    void repaintCallback();
    // -----------------------
    // Setters
    void setWaveForm(AudioBuffer<float>&);

private:
    Path p;
    std::shared_ptr<RingBuffer> ringBufferPointer = nullptr;
    Array<float> waveForm;
    bool waveformSet = false;
};

