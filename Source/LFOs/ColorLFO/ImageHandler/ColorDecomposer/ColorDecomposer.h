#pragma once
#include <JuceHeader.h>
#include "../../../../Utils/Constants.h"
#include "../../../../Utils/Utils.h"
#include "ColorTile/ColorTile.h"

class ColorDecomposer : public Component
{
public:
    // ----------------------------------------
    // Class
    ColorDecomposer();
    ~ColorDecomposer();
    // ----------------------------------------
    // GUI
    void paint(Graphics&)override;
    void resized()override;
    void setRGB(int, int, int);
    // ----------------------------------------
private:
    // ----------------------------------------
    ColorTile centerTile;
    ColorTile redTile;
    ColorTile greenTile;
    ColorTile blueTile;
    // ----------------------------------------
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ColorDecomposer);
};
