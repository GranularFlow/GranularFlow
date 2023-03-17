#pragma once
#include <JuceHeader.h>
#include "../../Utils/Constants.h"
#include "../../Utils/Utils.h"
#include "CustomLook.h"

class Knob : public Component, private ComboBox::Listener
{
public:

    // -----------------------------------
    struct Listener
    {
        virtual void setKnobToLfo(Knob*, int) = 0;
        virtual void removeKnobFromLfo(Knob*, int) = 0;
    };

    void setKnobListener(Knob::Listener* knobListenerPntrIn)
    { 
        if (knobListenerPntrIn!= nullptr)
        {
            knobListenerPntr = knobListenerPntrIn;
        }
    }

    void removeKnobListener() 
    { 
        if (knobListenerPntr != nullptr)
        {
            knobListenerPntr->removeKnobFromLfo(this, lastSelectedLFO);
            lastSelectedLFO = 0;
            knobListenerPntr = nullptr;
        }     
    }
    // ----------------------
    Listener* knobListenerPntr = nullptr;
    // -----------------------------------
    // Class
    Knob(String, Colour, float, float, float, float, bool);
    ~Knob();
    // ----------------------
    // GUI
    void paint(Graphics&) override;
    void resized() override;    
    // ----------------------
    // Listeners
    void addSliderListener(Slider::Listener*);
    void removeSliderListener(Slider::Listener*);
    // --- ComboBox
    void comboBoxChanged(ComboBox*) override;
    // ----------------------
    // Setters
    void setValue(float);
    void setDefaultValue();
    void setLfoValue(float);
    // ----------------------
    // Getters
    float getValue();
    // ----------------------
    // Tools
    bool isCurrentSlider(Slider*);
    Slider& getSlider();

private:
    // ----------------------
    CustomLook customLook;
    // ----------------------
    String name;
    Colour guiColor;
    int lastSelectedLFO = 0;
    float defaultValue = 0;
    std::unique_ptr<ComboBox> comboBox;
    // ---------------------- 
    Slider slider{ Slider::SliderStyle::RotaryHorizontalDrag, Slider::TextEntryBoxPosition::TextBoxBelow };

};