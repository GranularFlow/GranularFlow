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
#include "../../Utils/Utils.h"
#include "CustomLook.h"

class Knob : public Component, private ComboBox::Listener
{
public:

    // -----------------------------------
    struct KnobListener
    {
        virtual void setKnobToLfo(Knob*, int) = 0;
        virtual void removeKnobFromLfo(Knob*, int) = 0;
    };

    void setKnobListener(KnobListener* knobListenerPntrIn) 
    { 
        knobListenerPntr = knobListenerPntrIn; 
    }

    void removeKnobListener() 
    { 
        comboBox->setSelectedId(1);
        knobListenerPntr = nullptr;
    }

    KnobListener* knobListenerPntr = nullptr;
    // -----------------------------------

    // Class
    Knob(String, Colour, float, float, float, float, bool);
    ~Knob();
    // GUI
    void paint(Graphics&) override;
    void resized() override;    
    // Listeners
    void addSliderListener(Slider::Listener*);
    void removeSliderListener(Slider::Listener*);
    void comboBoxChanged(ComboBox*) override;
    // Setters
    void setDefaultValue();
    void setLfoValue(float);
    // Getters
    float getValue();
    // Tools
    bool isCurrentSlider(Slider*);
    Slider& getSlider();

private:
    CustomLook customLook;
    std::unique_ptr<ComboBox> comboBox;   

    String name;
    Colour guiColor;
    int lastSelectedLFO = 0;
    float defaultValue;

    Slider slider{ Slider::SliderStyle::RotaryHorizontalDrag, Slider::TextEntryBoxPosition::TextBoxBelow };
};