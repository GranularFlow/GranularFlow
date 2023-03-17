#include "PlayerCursor.h"

PlayerCursor::PlayerCursor()
{
}

PlayerCursor::~PlayerCursor()
{
}

void PlayerCursor::init(float positionPercentIn, Colour guiColourIn) {
    setCursorPositionPercent(positionPercentIn);
    setGuiColour(guiColourIn);
}

void PlayerCursor::paint(Graphics& g) {
    paintCursor(g);
}

void PlayerCursor::paintCursor(Graphics& g) {
    g.setColour(guiColour);
    //Cursor
    g.fillRect(cursorPosition - 1.0, 0.0, 2.0, getHeight() - CURSOR_BALL_RADIUS);
    // Ball, put Y to 2,25x radius, so that there is paddingfrom top and bottom
    g.fillEllipse((float)cursorPosition - CURSOR_BALL_RADIUS,
                  (float)getHeight() - (CURSOR_BALL_RADIUS * 2.25),
                  (float)CURSOR_BALL_RADIUS * 2, 
                  (float)CURSOR_BALL_RADIUS * 2);
}

float PlayerCursor::getCursorPositionInPixels(float cursorPositionPercent) {
    return (cursorPositionPercent / (float)100) * W_WIDTH;
}

float PlayerCursor::getCursorPositionInPixels() {
    return cursorPosition;
}

float PlayerCursor::getCursorPositionInPercent(float cursorPositionPx) {
    return (cursorPositionPx * (float)100) /(float) getWidth();
}

float PlayerCursor::getCursorPositionInPercent() {
    return (cursorPosition * (float)100) / (float)getWidth();
}

void PlayerCursor::setMouseMovable(bool mouseMovableIn)
{
    mouseMovable = mouseMovableIn;
}

void PlayerCursor::setCursorPositionPercent(float cursorPositionIn)
{
    setCursorPositionPx(getCursorPositionInPixels(cursorPositionIn));
}
void PlayerCursor::setCursorPosition(float cursorPositionIn) {
    cursorPosition = getCursorPositionInPixels(cursorPositionIn);
    repaint();
}

void PlayerCursor::setCursorPositionPx(float cursorPositionIn)
{
    if (mouseMovable)
    {
        cursorPosition = cursorPositionIn;
    
        if (listenerPntr != nullptr)
        {
            if (!listenerPntr->isCurrentRunningMode(PlayerSettings::RUNNING))
            {
                listenerPntr->onCursorPositionChange(getCursorPositionInPercent(cursorPosition));
            }        
        }
        repaint();
    }
}

void PlayerCursor::setGuiColour(Colour colourIn)
{
    guiColour = colourIn;
    repaint();
}

void PlayerCursor::mouseDrag(const MouseEvent& event)
{
    if (event.x < getWidth() && event.x > 0)
    {
        setCursorPositionPx(event.x);
    }
}

void PlayerCursor::mouseDown(const MouseEvent& event)
{
    if (event.x <= getWidth() && event.x >= 0)
    {
        setCursorPositionPx(event.x);
    }
}