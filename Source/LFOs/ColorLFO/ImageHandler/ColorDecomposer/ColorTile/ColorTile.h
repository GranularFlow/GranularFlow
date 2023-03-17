#pragma once
#include <JuceHeader.h>
#include "../../../../../Utils/Constants.h"
class ColorTile : public Component
{
public:
    // -------------------
    // Class
    ColorTile();
	~ColorTile();
    // -------------------
    // GUI
    void paint(Graphics&)override;
    void setColor(int, Colour);

private:
    Colour color = C_GRAY;
    int colorInt = 255;

};
