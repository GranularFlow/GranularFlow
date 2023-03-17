#pragma once
#include <JuceHeader.h>
#include "../../../Utils/Constants.h"

class Visualiser : public Component
{
public:
    // -----------------------
    // Class
	Visualiser();
	~Visualiser();
    // -----------------------
    // GUI
    void paint(Graphics&) override;
    void setWaveForm(Array<float>);
    // -----------------------
private:
    Array<float> waveForm;
};
