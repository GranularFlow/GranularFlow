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
    // Class
	GranularPlayer(int, int);
	~GranularPlayer() override;
    // GUI
	void paint(Graphics& g) override;
	void resized() override;
	// ------- PlayerCursor
	void onCursorPositionChange(int) override;
	bool isCurrentRunningMode(PlayerSettings::RunningMode) override;
	bool isCurrentMidiMode(PlayerSettings::MidiMode);
	// -------

	void movePositionCallback();
    // Tools
	void init();
	void initGrains();
	void reset();
	void addGrain(int);
	void removeGrain();
    // Getters
	bool isCursorMoving();
	int getActiveGrains();
	void fillNextBuffer(AudioBuffer<float>&, AudioBuffer<float>&);
	void fillNextBuffer(AudioBuffer<float>&, AudioBuffer<float>&, float);
	PlayerCursor* getCursor();
	// Setters
	void changeTimer(int);

	void setKnobsListener(Knob::Listener*);

private:
	// Settings
	int totalSamples;
	int sampleRate;

	// cursor position in samples
	int cursorPosition = 0;
	int cursorTimer = 0;
	bool waitForNextGrain = false;
	int grainTimer = 0;
	OwnedArray<Grain> grains;
	// Cursor
	PlayerCursor cursor;
	// Settings
	PlayerSettings settings;	
};