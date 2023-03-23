#pragma once
#include <JuceHeader.h>
#include "../../Utils/Constants.h"

class CustomClickableBox : public Component
{
public:
    // ----------------------
    // Class
    CustomClickableBox(Colour, String, bool, int, int, int, int);
	~CustomClickableBox();
    // ----------------------
    // GUI
    void paint(Graphics&)override;
private:
    bool fullSize = false;
    Colour color;
    String text;
    Rectangle<int> boxSize;
    Path path;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CustomClickableBox);
};
