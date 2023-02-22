/*
  ==============================================================================

    LfoPanel.h
    Created: 21 Feb 2023 5:44:35pm
    Author:  honza

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "../../Utils/Constants.h"

class CustomLfoPanel : public Component
{
public:
    // Class
    CustomLfoPanel();
	~CustomLfoPanel();
    // GUI
    void paint(Graphics&)override;

private:

};
