#pragma once
#include <JuceHeader.h>
#include "../../Utils/Constants.h"
#include "CustomLook.h"

class RadioBox : public Component, public ToggleButton::Listener
{
public:
    // ----------------------------------
    struct Listener {
        virtual void onValueChange(RadioBox*, int) = 0;
    };
    // ----------------------
    void setListener(RadioBox::Listener* listenerPntr) { radioBoxListenerPntr = listenerPntr; }
    void removeListener() { radioBoxListenerPntr = nullptr; }
    Listener* radioBoxListenerPntr = nullptr;
    // ----------------------------------
    // Class
	RadioBox(String, Colour, Array<String>);
    ~RadioBox();
    // ----------------------
    // GUI
    void paint(Graphics&) override;
    void resized();
    // ----------------------
    // Listeners
    void buttonStateChanged(Button*) override;
    void buttonClicked(Button*) override;
    // ----------------------
    // Getters
    int getValue();
    void resetDefaultValue();

private:
    CustomLook customLook;
    String name;
    Colour guiColor;
    OwnedArray<ToggleButton> toggleButtons;
};
