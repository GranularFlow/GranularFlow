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

class ColorLFO : public Component, public Button::Listener
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

    // Tools
    void prepareToPlay(float);
    void getNext();
private:
    //  -- Settings
    Component::SafePointer<LfoSettings> settings = new LfoSettings();
    //  -- handler
    std::unique_ptr<ImageHandler> imageHandler = std::make_unique<ImageHandler>(settings);
};