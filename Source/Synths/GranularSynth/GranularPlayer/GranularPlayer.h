#pragma once
#include <JuceHeader.h>
#include "../../../Utils/Constants.h"
#include "PlayerCursor/PlayerCursor.h"
#include "PlayerSettings/PlayerSettings.h"
#include "Grain/Grain.h"


class GranularPlayer : public Component
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
	int getCursorPosition();
	PlayerSettings::MidiMode getMidiMode();
	// ----------------------
	// Set
	void prepareToPlay(int);
	// ----------------------
	// Tools
	void mouseDown(const MouseEvent&) override;
	void disableCursorMovements(bool);
	void reset();
	void addGrain(int);
private:
	bool mouseMovable = true;
	// ----------------------
	int totalSamples = 1000;
	int sampleRate = 48000;
	// ----------------------
	int cursorPosition = 0;
	int grainTimer = 0;
	bool waitForNextGrain = false;
	// ----------------------
	OwnedArray<Grain> grains;
	PlayerSettings settings;	
};