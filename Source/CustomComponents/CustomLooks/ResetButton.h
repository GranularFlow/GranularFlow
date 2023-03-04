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

    struct ResetListener
    {
        virtual void reseted(ResetButton*) = 0;
    };

    void setListener(ResetListener* resetPntrIn) { resetPntr = resetPntrIn; }
    void removeListener() { resetPntr = nullptr; }

	ResetButton();
	~ResetButton();

    void paint(Graphics&)override;
    void resized();

    void mouseDown(const MouseEvent&);
    void mouseUp(const MouseEvent&);

    ImageButton reloadButton{ "reloadButton" };

private:
    ResetListener* resetPntr = nullptr;
    Colour bgColor = C_GRAY;
    CustomLook customLook;
    Image buttonImage = ImageFileFormat::loadFrom(BinaryData::reload_png, BinaryData::reload_pngSize);
};