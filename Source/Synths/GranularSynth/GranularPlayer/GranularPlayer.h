/*
  ==============================================================================

    GranularPlayer.h
    Created: 30 Oct 2022 4:54:37pm
    Author:  honza

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "../../../Utils/Constants.h"
#include "PlayerCursor/PlayerCursor.h"
#include "PlayerSettings/PlayerSettings.h"
#include "Grain/Grain.h"


/*
  ==============================================================================
	This class acts like a container for granular cursor
  ==============================================================================

*/
class GranularPlayer : public Component, public PlayerCursor::Listener
{
public:
	// ----------------------
    // Class
	GranularPlayer(int, int);
	~GranularPlayer() override;
	// ----------------------
    // GUI
	void paint(Graphics& g) override;
	void resized() override;
	// ------- PlayerCursor
	void onCursorPositionChange(int) override;
	bool isCurrentRunningMode(PlayerSettings::RunningMode) override;
	bool isCurrentMidiMode(PlayerSettings::MidiMode);
	// ----------------------
	// Listener 
	void setKnobsListener(Knob::Listener*);
	void movePositionCallback();
	// ----------------------
    // Get
	bool isCursorMoving();
	int getActiveGrains();
	void fillNextBuffer(AudioBuffer<float>&, AudioBuffer<float>&);
	void fillNextBuffer(AudioBuffer<float>&, AudioBuffer<float>&, float);
	PlayerCursor* getCursor();
	// ----------------------
	// Set
	void changeTimer(int);
	// ----------------------
	// Tools
	void disableCursorMovements();
	void init();
	void initGrains();
	void reset();
	void addGrain(int);
private:
	// ----------------------
	int totalSamples = 1000;
	int sampleRate = 48000;
	// ----------------------
	int cursorPosition = 0;
	int cursorTimer = 0;
	// ----------------------
	int grainTimer = 0;
	bool waitForNextGrain = false;
	// ----------------------
	bool mouseMovable = true;
	// ----------------------
	OwnedArray<Grain> grains;
	PlayerCursor cursor;
	PlayerSettings settings;	
};