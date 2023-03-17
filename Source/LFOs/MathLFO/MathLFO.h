#pragma once
#include <JuceHeader.h>
#include "../../Utils/Constants.h"
#include "MathVisualiser/MathVisualiser.h"
#include "MathSettings/MathSettings.h"
#include "../LFO.h"
#include "exprtk.hpp"

class MathLFO : public Component, public LFO, public Button::Listener
{
public:
    // ----------------------
    // Class
	MathLFO();
	~MathLFO();
    // ----------------------
    // GUI
    void paint(Graphics&)override;
    void resized()override;
    // ----------------------
    // Listeners
    void addTimerListener(Slider::Listener*)override;
    void removeTimerListener(Slider::Listener*)override;
    void timeCallback();
    // ----------------------
    bool isTimerSlider(Slider*);
    void buttonClicked(Button*)override;
    // ----------------------
    // Get
    float getTimerHz();
    double getNext();    
    bool isValidExpression();
    bool isValidExpression(const std::string&);
    // ----------------------
    // Tools
    void initSamples(std::string, int);
private:
    // ----------------------
    bool validExp = false;
    float increment = 1;
    float index = 0;
    double value;
    Array<float> samples;
    // ----------------------
    MathVisualiser visualiser;
    MathSettings settings;
    // ----------------------
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MathLFO);
};