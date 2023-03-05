/*
  ==============================================================================

    WavetableLFO.h
    Created: 3 Feb 2023 12:45:49pm
    Author:  honza

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "../../Utils/Constants.h"
#include "../../Utils/Utils.h"
#include "../LFO.h"
#include "WavetableLfoSettings/WavetableLfoSettings.h"
#include "WavetableLfoCanvas/WavetableLfoCanvas.h"
#include "WavetableLfoVisualiser/WavetableLfoVisualiser.h"

class WavetableLFO : public Component, public Button::Listener, public Slider::Listener, public LFO
{
public:
    // Class
	WavetableLFO();
	~WavetableLFO();
    // Listeners
    void sliderValueChanged(Slider*) override;
    void buttonClicked(Button*) override;
    // GUI
    void paint(Graphics&) override;
    void resized()override;    
    // Tools
    void initSamples();
    float getNext();
private:
    TextButton combineButton{ "COMBINE" };
    WavetableLfoCanvas canvas1 {"FIRST WAVE"};
    WavetableLfoCanvas canvas2 {"SECOND WAVE"};
    WavetableLfoCanvas canvas3 {"THIRD WAVE"};
    WavetableLfoVisualiser canvas4;
    WavetableLfoSettings wavetableSettings;
    Array<float> sampleY;

    float frequency = 440;
    float sampleRate = 48000;

    int currentPosition = 0;
    float increment = 1.0;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(WavetableLFO);
};
