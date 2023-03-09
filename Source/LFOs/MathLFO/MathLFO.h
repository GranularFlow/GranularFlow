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



class MathLFO : public Component, public Timer, public Slider::Listener, public Button::Listener, public LFO
{
public:
    // Class
	MathLFO();
	~MathLFO();
    // GUI
    void paint(Graphics&)override;
    void resized()override;

    // Listener
    void timerCallback();
    void sliderValueChanged(Slider*);
    void buttonClicked(Button*)override;

    void initSamples();
    double getNext();
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