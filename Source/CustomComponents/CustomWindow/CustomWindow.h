#pragma once
#include <JuceHeader.h>
#include "../../Utils/Constants.h"
#include "../../Synths/Synth.h"

class CustomWindow : public DocumentWindow
{
public:
    // ----------------
    // Class
    CustomWindow(String, Component*);
	~CustomWindow();
    // ----------------
    // Tools
    void showWindow();
    void hideWindow();
    void closeButtonPressed()override;
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CustomWindow);
};