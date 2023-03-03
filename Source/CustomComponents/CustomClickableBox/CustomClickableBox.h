/*
  ==============================================================================

    CustomClickableBox.h
    Created: 22 Feb 2023 8:25:22pm
    Author:  honza

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "../../Utils/Constants.h"

class CustomClickableBox : public Component
{
public:
    // Class
    CustomClickableBox(Colour, String, bool);
	~CustomClickableBox();
    // GUI
    void paint(Graphics&)override;
    

private:
    bool fullSize = false;
    Colour color;
    String text;
};
