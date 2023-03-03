/*
  ==============================================================================

    Separator.h
    Created: 22 Nov 2022 11:46:37pm
    Author:  honza

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "../../Utils/Constants.h"

class Separator : public Component
{
public:
    Separator() {}
    ~Separator() {}
    void paint(Graphics& g) override {
        g.fillAll(M_T_LIGHT);
    };
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Separator);
};