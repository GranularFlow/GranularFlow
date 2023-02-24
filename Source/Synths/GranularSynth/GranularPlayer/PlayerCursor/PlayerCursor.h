/*
  ==============================================================================

    PlayerCursor.h
    Created: 30 Oct 2022 10:49:29pm
    Author:  honza

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "../../../../Utils/Constants.h"
#include "../PlayerSettings/PlayerSettings.h"

class PlayerCursor: public Component, public Timer
{
public:

    struct Listener
    {
        virtual void onCursorPositionChange(int newCursorPositionPercent) = 0;
        virtual bool isCurrentMidiMode(PlayerSettings::MidiMode) = 0;
        virtual bool isCurrentRunningMode(PlayerSettings::RunningMode) = 0;
        virtual bool isCurrentGranularMode(PlayerSettings::GranularMode) = 0;
        virtual int getMaxSamples() = 0;
    };
    void setListener(Listener* listenerPntrIn) { listenerPntr = listenerPntrIn; }
    void removeListener() { listenerPntr = nullptr; }

    // Class
	PlayerCursor();
    ~PlayerCursor();
    void init(float, Colour);
    // GUI
	void paint(Graphics& g) override;
	void paintCursor(Graphics& g);
	void paintGrainLength(Graphics& g);
	void paintGrainPosition(Graphics& g);
    void setOpacity(int8 opacityIn);
    // Listeners
    void timerCallback() override;
    //void onValueChange(float) override;
    void mouseDrag(const MouseEvent&) override;
    void mouseDown(const MouseEvent&) override;
    void mouseUp(const MouseEvent&) override;
    // Getters
    float getCursorPositionInPixels(float);
    float getCursorPositionInPixels();
    float getCursorPositionInPercent();
    float getCursorPositionInPercent(float);
    // Setters
	void setCursorPositionPercent(float);
    void setCursorPosition(float);
    void setCursorPositionPx(float);
	void setGuiColour(Colour colour);

private:
    Listener* listenerPntr = 0;
    int opacity=100;
    Colour guiColour;
	/* How far from start of buffer - x Position in % */
    float cursorPosition = 0;
};
