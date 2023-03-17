#pragma once
#include <JuceHeader.h>
#include "../../Utils/Constants.h"

class CustomClickableBox : public Component
{
public:
    // ----------------------
    // Class
    CustomClickableBox(Colour, String, bool);
	~CustomClickableBox();
    // ----------------------
    // GUI
    void paint(Graphics&)override;
private:
    bool fullSize = false;
    Colour color;
    String text;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CustomClickableBox);
};
