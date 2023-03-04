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
#include "WavetableLfoSettings/WavetableLfoSettings.h"
#include "WavetableLfoCanvas/WavetableLfoCanvas.h"
#include "WavetableLfoVisualiser/WavetableLfoVisualiser.h"

class WavetableLFO : public Component, public Button::Listener, public Slider::Listener
{
public:
    // Class
	WavetableLFO();
	~WavetableLFO();


    // Listeners
    void addListeners();
    void removeListeners();
    void sliderValueChanged(Slider*) override;
    void buttonClicked(Button*) override;

    // GUI
    void paint(Graphics&) override;
    void paintLogoOnce(Graphics&);
    void resized()override;
    
    // Tools
    void initSamples();
    float interpolate(float x, float x1, float x2, float y1, float y2);

    float getNext();
private:
    TextButton combineButton{ "COMBINE" };
    WavetableLfoCanvas canvas1 {"FIRST WAVE"};
    WavetableLfoCanvas canvas2 {"SECOND WAVE"};
    WavetableLfoCanvas canvas3 {"THIRD WAVE"};
    WavetableLfoVisualiser canvas4;
    WavetableLfoSettings wavetableSettings;
    Array<float> sampleY;
    Array<float> sampleX;

    float frequency = 440;
    float sampleRate = 48000;

    int currentPosition = 0;
    float increment = 1.0;
};
