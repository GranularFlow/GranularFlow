/*
  ==============================================================================

    ResetButton.h
    Created: 3 Mar 2023 11:52:26pm
    Author:  honza

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "../../Utils/Constants.h"
#include "CustomLook.h"


class ResetButton : public Component
{
public:

    struct Listener
    {
        virtual void reseted(ResetButton*) = 0;
    };

    void setListener(ResetButton::Listener* resetPntrIn) { resetPntr = resetPntrIn; }
    void removeListener() { resetPntr = nullptr; }

	ResetButton();
	~ResetButton();

    void paint(Graphics&)override;
    void resized();

    void mouseDown(const MouseEvent&);
    void mouseUp(const MouseEvent&);

    ImageButton reloadButton{ "reloadButton" };

private:
    Listener* resetPntr = nullptr;
    Colour bgColor = L_GRAY;
    CustomLook customLook;
    Image buttonImage = ImageFileFormat::loadFrom(BinaryData::reload_png, BinaryData::reload_pngSize);
};