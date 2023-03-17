#pragma once
#include <JuceHeader.h>
#include "../../Utils/Constants.h"
#include "CustomLook.h"

class ResetButton : public Component
{
public:
    // ----------------------
    struct Listener
    {
        virtual void reseted(ResetButton*) = 0;
    };

    void setListener(ResetButton::Listener* resetPntrIn) { resetPntr = resetPntrIn; }
    void removeListener() { resetPntr = nullptr; }
    // ----------------------
    // Class
	ResetButton();
	~ResetButton();
    // ----------------------
    // GUI
    void paint(Graphics&)override;
    void resized();
    // ----------------------
    // Listeners
    void mouseDown(const MouseEvent&);
    void mouseUp(const MouseEvent&);
    // ----------------------    
private:
    // ----------------------
    Listener* resetPntr = nullptr;
    // ----------------------
    Colour bgColor = L_GRAY;
    CustomLook customLook;
    // ----------------------
    ImageButton reloadButton{ "reloadButton" };
    Image buttonImage = ImageFileFormat::loadFrom(BinaryData::reload_png, BinaryData::reload_pngSize);
};