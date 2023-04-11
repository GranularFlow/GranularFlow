#pragma once
#include <JuceHeader.h>
#include "../../Utils/Constants.h"

class Separator : public Component
{
public:
    Separator() { setOpaque(true); }
    ~Separator() {}
    void paint(Graphics& g) override {
        g.fillAll(C_DARKER_GRAY);
    };
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Separator);
};