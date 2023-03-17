#pragma once
#include <JuceHeader.h>
#include "../../Utils/Constants.h"
#include "../../Utils/Utils.h"
#include "../LFO.h"
#include "WavetableLfoSettings/WavetableLfoSettings.h"
#include "WavetableLfoCanvas/WavetableLfoCanvas.h"
#include "WavetableLfoVisualiser/WavetableLfoVisualiser.h"

class WavetableLFO : public Component, public LFO, public Button::Listener, public Slider::Listener
{
public:
    // -----------------------
    // Class
	WavetableLFO();
	~WavetableLFO();
    // -----------------------
    // GUI
    void paint(Graphics&) override;
    void resized()override;
    // -----------------------
    // Listeners
    void sliderValueChanged(Slider*) override;
    void buttonClicked(Button*) override;
    // -----------------------
    // ---LFO
    void addTimerListener(Slider::Listener*)override;
    void removeTimerListener(Slider::Listener*)override;
    void timeCallback()override;
    // -----------------------
    // Get
    int getTimerHz();
    double getNext();
    bool isTimerSlider(Slider*);
    bool isEmpty();
    // -----------------------
    // Tools
    void initSamples();
    void calculateIncrement();
    // -----------------------
private:
    float currentPosition = 0;
    float finalSample = 0;
    float increment = 0;
    bool isSetWave = false;
    // -----------------------
    TextButton combineButton{ "COMBINE" };
    // -----------------------
    WavetableLfoCanvas canvas1 {"FIRST WAVE"};
    WavetableLfoCanvas canvas2 {"SECOND WAVE"};
    WavetableLfoCanvas canvas3 {"THIRD WAVE"};
    WavetableLfoVisualiser canvas4;
    // -----------------------
    Array<float> sampleY;
    // -----------------------
    WavetableLfoSettings settings;
    // -----------------------
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(WavetableLFO);
};
