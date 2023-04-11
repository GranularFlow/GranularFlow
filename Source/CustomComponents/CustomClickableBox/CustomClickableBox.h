#pragma once
#include <JuceHeader.h>
#include "../../Utils/Constants.h"

class CustomClickableBox : public Component
{
public:
    // ----------------------
    // Class
    CustomClickableBox(juce::Colour, juce::String, bool, int, int, int, int);
	~CustomClickableBox();
    // ----------------------
    // GUI
    void paint(Graphics&)override;
private:
    bool fullSize = false;
    juce::Colour color;
    juce::String text;
    juce::Rectangle<int> boxSize;
    juce::Path path;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CustomClickableBox);
};
