#pragma once
#include <JuceHeader.h>
#include "../../../../Utils/Constants.h"
#include "../PlayerSettings/PlayerSettings.h"

class PlayerCursor: public Component
{
public:

    struct Listener
    {
        virtual void onCursorPositionChange(int newCursorPositionPercent) = 0;
        virtual bool isCurrentRunningMode(PlayerSettings::RunningMode) = 0;
    };
    void setListener(Listener* listenerPntrIn) { listenerPntr = listenerPntrIn; }
    void removeListener() { listenerPntr = nullptr; }
    // ----------------------
    // Class
	PlayerCursor();
    ~PlayerCursor();
    // ----------------------
    // GUI
	void paint(Graphics& g) override;
	void paintCursor(Graphics& g);
    // ----------------------
    // Listeners
    void mouseDrag(const MouseEvent&) override;
    void mouseDown(const MouseEvent&) override;
    // ----------------------
    // Get
    float getCursorPositionInPixels(float);
    float getCursorPositionInPixels();
    float getCursorPositionInPercent();
    float getCursorPositionInPercent(float);
    // ----------------------
    // Set
    void setMouseMovable(bool);
	void setCursorPositionPercent(float);
    void setCursorPosition(float);
    void setCursorPositionPx(float);
	void setGuiColour(Colour colour);
    // ----------------------
    // Tools
    void init(float, Colour);
private:
    /* How far from start of buffer - x Position in % */
    float cursorPosition = 0;
    bool mouseMovable = true;
    // ----------------------
    Listener* listenerPntr = 0;
    // ----------------------
    Colour guiColour;
};
