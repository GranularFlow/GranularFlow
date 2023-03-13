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

class ColorLFO : public Component, public LFO, public Button::Listener, public RadioBox::Listener
{
public:
    // Class
	ColorLFO();
	~ColorLFO();
    // GUI
    void paint(Graphics&)override;
    void resized()override;
    // Listener
    void buttonClicked(Button*)override;
    // LFO
    // Listeners
    void addTimerListener(Slider::Listener*)override;
    void removeTimerListener(Slider::Listener*)override;
    void timeCallback()override;
    // --------
    // Radiobox
    void onValueChange(RadioBox*, int)override;
    // Get
    int getTimerHz();
    

private:
    //  -- Settings
    LfoSettings settings;
    //  -- handler
    ImageHandler imageHandler;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ColorLFO);
};