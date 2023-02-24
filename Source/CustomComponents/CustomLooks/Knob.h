/*
  ==============================================================================

    RadioBox.h
    Created: 15 Nov 2022 1:29:12am
    Author:  honza

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "../../Utils/Constants.h"
#include "CustomLook.h"

class Knob : public Component
{
public:
    // Class
    Knob(String, Colour, float, float, float, float);
    ~Knob();
    // GUI
    void paint(Graphics&) override;
    void resized() override;
    // Listeners
    void addListener(Slider::Listener*);
    void removeListener(Slider::Listener*);

    // Getters
    float getValue();

    // Slider TODO: wrap it to private
    Slider slider { Slider::SliderStyle::RotaryHorizontalDrag, Slider::TextEntryBoxPosition::NoTextBox };
private:
    CustomLook customLook;
    String name;
    Colour guiColor;
    float value = 0;
};