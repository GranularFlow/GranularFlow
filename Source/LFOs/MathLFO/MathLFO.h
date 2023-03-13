/*
  ==============================================================================

    MathLFO.h
    Created: 20 Feb 2023 9:01:58pm
    Author:  honza

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "../../Utils/Constants.h"
#include "MathVisualiser/MathVisualiser.h"
#include "MathSettings/MathSettings.h"
#include "../LFO.h"
#include "exprtk.hpp"



class MathLFO : public Component, public LFO, public Button::Listener, public Slider::Listener
{
public:
    // Class
	MathLFO();
	~MathLFO();
    // GUI
    void paint(Graphics&)override;
    void resized()override;
    // Listeners
    void addTimerListener(Slider::Listener*)override;
    void removeTimerListener(Slider::Listener*)override;
    void timeCallback()override;
    // --------
    void sliderValueChanged(Slider*)override;
    void buttonClicked(Button*)override;
    // Get
    int getTimerHz();
    double getNext();
    // Tools
    void initSamples();
    void calculateDelta();
    double calculateEquation(double);
    bool isValidExpression(const std::string&);

private:
    std::string expressionString = "";


    int sampleRate = 48000;
    float frequency = 1;
    double angle = 0.0;
    double delta = 0.0;
    double outputValue = 0;

    Array<float> samples;

    MathVisualiser visualiser;
    MathSettings settings;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MathLFO);
};