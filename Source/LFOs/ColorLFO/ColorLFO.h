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

class ColorLFO : public Component, public Button::Listener, public Slider::Listener, public LFO, public Timer, public ImageHandler::ImageHandlerListener
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
    void timerCallback() override;
    void sliderValueChanged(Slider*) override;
    // Process
    void prepareToPlay(double, int);
    // Tools
    void imageLoaded() override;
private:
    //  -- Settings
    Component::SafePointer<LfoSettings> settings = new LfoSettings();
    //  -- handler
    Component::SafePointer<ImageHandler> imageHandler = new ImageHandler(settings);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ColorLFO);
};