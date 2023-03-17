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
    // ----------------------------------------
    // Class
	ColorLFO();
	~ColorLFO();
    // ----------------------------------------
    // GUI
    void paint(Graphics&)override;
    void resized()override;
    // ----------------------------------------
    // Listeners
    // --- Button
    void buttonClicked(Button*)override;
    // LFO
    void addTimerListener(Slider::Listener*)override;
    void removeTimerListener(Slider::Listener*)override;
    // ------ Callback LFO
    void timeCallback()override;
    // ------ Callback GUI
    void repaintCanvas();        
    // ------ Callback Radiobox change
    void onValueChange(RadioBox*, int)override;
    // ----------------------------------------
    // Get
    int getTimerHz();
    bool isImageSet();
    bool isTimerSlider(Slider*);
    // ----------------------------------------
private:    
    // ----------------------------------------
    LfoSettings settings;
    ImageHandler imageHandler;
    // ----------------------------------------
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ColorLFO);
};