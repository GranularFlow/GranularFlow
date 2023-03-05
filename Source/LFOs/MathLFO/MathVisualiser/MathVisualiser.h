/*
  ==============================================================================

    MathVisualiser.h
    Created: 20 Feb 2023 9:02:16pm
    Author:  honza

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "../../../Utils/Constants.h"

class MathVisualiser : public Component
{
public:
    // Class
    MathVisualiser();
    ~MathVisualiser();
    // GUI
    void initGui();
    void paint(Graphics&)override;
    void setSamples(Array<float>);
    Array<float> getSamples();

private:
    Array<float> samples;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MathVisualiser);
};
