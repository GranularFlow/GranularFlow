/*
  ==============================================================================

    PlayerCursor.cpp
    Created: 30 Oct 2022 10:52:52pm
    Author:  honza

  ==============================================================================
*/

#include "PlayerCursor.h"

PlayerCursor::PlayerCursor()
{
    //startTimer(30);
}

PlayerCursor::~PlayerCursor()
{
    //stopTimer();
}

void PlayerCursor::init(float positionPercentIn, Colour guiColourIn) {
    setCursorPositionPercent(positionPercentIn);
    setGuiColour(guiColourIn);
}

void PlayerCursor::paint(Graphics& g) {
    paintCursor(g);
    //paintGrainLength(g);
    //paintGrainPosition(g);
}

void PlayerCursor::paintCursor(Graphics& g) {
    g.setColour(guiColour.darker( 1 - (opacity / (float) 100) ));
    //Cursor
    g.fillRect(cursorPosition - 1.0, 0.0, 2.0, getHeight() - CURSOR_BALL_RADIUS);
    // Ball, put Y to 2,25x radius, so that there is paddingfrom top and bottom
    g.fillEllipse((float)cursorPosition - CURSOR_BALL_RADIUS,
                  (float)getHeight() - (CURSOR_BALL_RADIUS * 2.25),
                  (float)CURSOR_BALL_RADIUS * 2, 
                  (float)CURSOR_BALL_RADIUS * 2);
}

void PlayerCursor::paintGrainLength(Graphics& g) {
    g.setColour(Colour::fromRGBA(255,255,255,100));

    if (false) {
        // Ordered forward
    }
    else
    {
        // Ordered reversed

    }
    
}

void PlayerCursor::paintGrainPosition(Graphics& g) {
    g.fillAll(Colours::white);
}

void PlayerCursor::setOpacity(int8 opacityIn)
{
    opacity = opacityIn;
    repaint();
}

void PlayerCursor::timerCallback()
{
}

float PlayerCursor::getCursorPositionInPixels(float cursorPositionPercent) {
    return (cursorPositionPercent / (float)100) * getWidth();
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
    cursorPosition = cursorPositionIn;
    
    if (listenerPntr != nullptr)
    {
        if (!listenerPntr->isCurrentRunningMode(PlayerSettings::RUNNING))
        {
            //DBG("cursorPosition" << cursorPosition);
            listenerPntr->onCursorPositionChange(getCursorPositionInPercent(cursorPosition));
        }
        
    }
    repaint();   
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

void PlayerCursor::mouseUp(const MouseEvent&)
{
   
}


