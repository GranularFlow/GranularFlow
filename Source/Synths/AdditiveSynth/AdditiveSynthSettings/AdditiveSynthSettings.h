/*
  ==============================================================================

    AdditiveSettings.h
    Created: 1 Feb 2023 10:10:45pm
    Author:  honza

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "../../../Utils/Utils.h"
#include "../../../Utils/Constants.h"
#include "../../../CustomComponents/CustomLooks/Knob.h"
#include "../../../CustomComponents/CustomLooks/NumberSelect.h"

class AdditiveSynthSettings : public Component
{
public:
    // Class
	AdditiveSynthSettings();
	~AdditiveSynthSettings();
    // GUI
    void paint(Graphics&) override;
    void resized() override;
    // Harmonic settings    
    //(String nameIn, Colour guiColorIn, int startRangeIn, int endRangeIn, int stepIn, int initialValue
    NumberSelect harmonicCount {"Count", L_GREEN, 0, 5, 1, 0};
    NumberSelect harmonicSelect { "Selected", L_ORANGE, 0, 5, 1, 0 };

private:

};
