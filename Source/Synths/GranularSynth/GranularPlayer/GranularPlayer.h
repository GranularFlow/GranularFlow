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
class GranularPlayer : public Component, public PlayerCursor::Listener, public Timer
{
public:
    // Class
	GranularPlayer(int, int);
	~GranularPlayer() override;
    // GUI
	void paint(Graphics& g) override;
	void resized() override;
	// Listeners
	void onCursorPositionChange(int) override;
	bool isCurrentGranularMode(PlayerSettings::GranularMode) override;
	bool isCurrentRunningMode(PlayerSettings::RunningMode) override;
	bool isCurrentMidiMode(PlayerSettings::MidiMode) override;
	int getMaxSamples() override;
	void timerCallback() override;
    // Tools
	void addGrain(int, int);
	int calculateStep();
	int percentToSamplePosition(int8);
    // Getters
	void fillNextBuffer(AudioBuffer<float>&, AudioBuffer<float>&);
	void fillNextBuffer(AudioBuffer<float>&, AudioBuffer<float>&, float);
	int getGrainNumSamples();
	PlayerCursor* getCursor();
	// Setters
	void changeTimer(int);

private:
	// Settings
	int totalSamples;
	int sampleRate;

	// cursor position in samples
	int cursorPosition;
	int cursorTimer = 0;

	bool waitForNextGrain = false;
	int grainTimer = 0;
	OwnedArray<Grain> grains;
	// Cursor
	PlayerCursor cursor;
	// Settings
	PlayerSettings settings;	
};