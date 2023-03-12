/*
  ==============================================================================

    ColorLFO.h
    Created: 8 Feb 2023 4:43:34pm
    Author:  honza

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "../../Utils/Utils.h"
#include "../../Utils/Constants.h"
#include "LfoSettings/LfoSettings.h"
#include "ImageHandler/ImageHandler.h"
#include "../LFO.h"

class ColorLFO : public Component, public Button::Listener, public Slider::Listener, public LFO
{
public:
    // Class
	ColorLFO();
	~ColorLFO();
    // GUI
    void paint(Graphics&)override;
    void resized()override;
    // Listener
    void buttonClicked(Button*);
    void timeCallback();
    void sliderValueChanged(Slider*) override;
    // Get
    int getTimerHz();
    // Tools
    void addTimerListener(Slider::Listener*);
    void removeTimerListener(Slider::Listener*);

private:
    //  -- Settings
    LfoSettings settings = new LfoSettings();
    //  -- handler
    ImageHandler imageHandler = new ImageHandler();

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ColorLFO);
};