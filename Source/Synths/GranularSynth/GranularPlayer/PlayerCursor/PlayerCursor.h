#pragma once
#include <JuceHeader.h>
#include "../../../../Utils/Constants.h"
#include "../PlayerSettings/PlayerSettings.h"

class PlayerCursor: public Component
{
public:
    // ----------------------
    // Class
	PlayerCursor();
    ~PlayerCursor();
    // ----------------------
    // GUI
	void paint(Graphics& g) override;
    // ----------------------
    // Listeners
    void mouseDrag(const MouseEvent&) override;
    void mouseDown(const MouseEvent&) override;
    void movePositionCallback(int, PlayerSettings::GranularMode);
    // ----------------------
    // Get
    int getCursorPosition();
    // ----------------------
    // Set
    void setMouseMovable(bool);
    void setCursorPosition(int);
    // ----------------------
    // Tools
private:
    /* How far from start of buffer - x Position in % */
    float cursorPosition = 0;
    
    // ----------------------
    // ----------------------
    Colour guiColour;
};
