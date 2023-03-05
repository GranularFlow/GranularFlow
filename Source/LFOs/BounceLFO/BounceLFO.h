/*
  ==============================================================================

    BounceLFO.h
    Created: 16 Feb 2023 7:29:42pm
    Author:  honza

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include <JuceHeader.h>
#include "../../Utils/Utils.h"
#include "../../Utils/Constants.h"
#include "../LFO.h"
#include "BounceSettings/BounceSettings.h"
#include "BounceCanvas/BounceCanvas.h"


class BounceLFO : public Component, public Slider::Listener, public Timer, public Button::Listener, public LFO
{
public:
    // Class
	BounceLFO();
	~BounceLFO();

    // GUI
    void paint(Graphics&) override;
    void resized() override;

    // Listeners
    void addListeners();
    void removeListeners();
    void timerCallback();
    void sliderValueChanged(Slider*);
    void buttonClicked(Button*);
    // Getters
    float getOutputValue();
    // Tools
    void checkNextCoordinate();

private:
    BounceSettings settings;
    BounceCanvas canvas;
    float outputValue = 1.0f;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(BounceLFO);
};
