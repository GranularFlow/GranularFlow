/*
  ==============================================================================

    Wrapper.h
    Created: 21 Feb 2023 3:43:03pm
    Author:  honza

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "../Utils/Constants.h"
#include "../CustomComponents/CustomWindow/CustomWindow.h"
#include "../CustomComponents/CustomLfoPanel/CustomLfoPanel.h"
#include "../CustomComponents/CustomClickableBox/CustomClickableBox.h"

class GranularFlowWrapper : public Component
{
public:
    // Class
    GranularFlowWrapper();
	~GranularFlowWrapper();
    // GUI
    void paint(Graphics&)override;
    void resized();
    // Tools
    void closeWindows();

private:
    Component::SafePointer<Component> waveSynthBox = new CustomClickableBox(C_MARINE, "WAVETABLE SYNTH");
    Component::SafePointer<Component> granularSynthBox = new CustomClickableBox(C_BILLS, "GRANULAR SYNTH");
    Component::SafePointer<Component> additiveSynthBox = new CustomClickableBox(C_ANDROID, "ADDITIVE SYNTH");


    Array<Component::SafePointer<Component>> windows;
    //Component::SafePointer<Component> panel = new CustomLfoPanel;
};
