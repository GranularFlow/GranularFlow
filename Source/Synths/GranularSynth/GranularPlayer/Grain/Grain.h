#pragma once
#include <JuceHeader.h>
#include "../PlayerSettings/PlayerSettings.h"

class Grain
{
public:
    // Class
	Grain();
	~Grain();
    // Getters
    int getCurrentPosition();
    int getLengthInSamples();
    bool isSkipped();
    // Setters
    void setSkip();
    void setNewGrain(int, int, float, float, float, PlayerSettings::GranularMode, PlayerSettings::WindowType);
    // Audio
    void fillNextSamples(AudioBuffer<float>&, AudioBuffer<float>&, float);
    float calculateWindow(float);

private:
    float totalPosition = 0;
    float finalSample = 0;
    float mirroredSample = 0;
    int startingPosition = 0;
    int lengthInSamples = 0;
    float pitch = 1;
    float volume[2] = { 0,0 };
    PlayerSettings::GranularMode granularMode = PlayerSettings::GranularMode::ORDER;
    PlayerSettings::WindowType windowType = PlayerSettings::WindowType::HALF_SINE;
    int currentPosition = 0;
    bool toSkip = true;

};
