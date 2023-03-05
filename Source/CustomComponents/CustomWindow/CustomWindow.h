/*
  ==============================================================================

    Window.h
    Created: 21 Feb 2023 3:50:16pm
    Author:  honza

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "../../Utils/Constants.h"
#include "../../Synths/Synth.h"

class CustomWindow : public DocumentWindow
{
public:
    // Class
    CustomWindow(String, Component*);

	~CustomWindow();
    void showWindow();
    void hideWindow();
    void closeButtonPressed()override;
private:
};