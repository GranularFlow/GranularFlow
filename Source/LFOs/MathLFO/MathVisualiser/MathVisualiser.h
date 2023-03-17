#pragma once
#include <JuceHeader.h>
#include "../../../Utils/Constants.h"

class MathVisualiser : public Component
{
public:
    // -----------------------
    // Class
    MathVisualiser();
    ~MathVisualiser();
    // -----------------------
    // GUI    
    void paint(Graphics&)override;
    // -----------------------
    // Get
    Array<float> getSamples();
    // -----------------------
    // Set
    void setSamples(Array<float>);   
    // -----------------------
    // Tools
    void initGui();
    // -----------------------
private:
    // -----------------------
    Array<float> samples;
    // -----------------------
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MathVisualiser);
};
