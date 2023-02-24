/*
  ==============================================================================

    ColorTile.h
    Created: 15 Feb 2023 7:11:16pm
    Author:  honza

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "../../../../../Utils/Constants.h"
class ColorTile : public Component
{
public:
    // Class
    ColorTile();
	~ColorTile();
    // GUI
    void paint(Graphics&)override;
    void setColor(int, Colour);

private:
    Colour color = Colours::black;
    int colorInt = 255;

};
