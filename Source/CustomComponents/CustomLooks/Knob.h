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
        virtual void setLfoPointer(Knob*, int) = 0;
        virtual void removeLfoPointer(Knob*, int) = 0;
    };
    void setListener(KnobListener* knobListenerPntrIn) { knobListenerPntr = knobListenerPntrIn; }
    void removeListener() { 
        comboBox->setSelectedId(1);
        knobListenerPntr = nullptr;
    }
    KnobListener* knobListenerPntr = nullptr;
    // -----------------------------------

    // 
    // Class
    Knob(String, Colour, float, float, float, float, bool);
    ~Knob();
    // GUI
    void paint(Graphics&) override;
    void resized() override;
    // Listeners
    void addListener(Slider::Listener*);
    void removeListener(Slider::Listener*);
    void comboBoxChanged(ComboBox*) override;
    // methods
    void setLfoValue(float);
    float getValue();


    // Slider TODO: wrap it to private
    Slider slider { Slider::SliderStyle::RotaryHorizontalDrag, Slider::TextEntryBoxPosition::NoTextBox };
private:
    std::unique_ptr<ComboBox> comboBox;   
    int lastSelectedLFO = 0;
    CustomLook customLook;
    String name;
    Colour guiColor;
    float value = 0;
};