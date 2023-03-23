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
	ResetButton(int, int, int, int);
	~ResetButton();
    // ----------------------
    // GUI
    void paint(Graphics&)override;
    void resized();
    // ----------------------
    // Listeners
    void mouseDown(const MouseEvent&)override;
    // ----------------------    
private:
    // ----------------------
    Listener* resetPntr = nullptr;
    CustomLook customLook;
    // ----------------------
    ImageButton reloadButton{ "reloadButton" };
    Image buttonImage = ImageFileFormat::loadFrom(BinaryData::reload_png, BinaryData::reload_pngSize);
};