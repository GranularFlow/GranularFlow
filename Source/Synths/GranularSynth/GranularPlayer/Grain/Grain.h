/*
  ==============================================================================

    Grain.h
    Created: 21 Nov 2022 7:52:09pm
    Author:  honza

  ==============================================================================
*/

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
    int getDelete();
    // Setters
    void setNewGrain(int, int, int, float, float, float);
    // Audio
    void fillNextSamples(AudioBuffer<float>&, AudioBuffer<float>&, PlayerSettings*, int, double);
private:
    bool toDelete = false;

    int startingPosition = 0;
    int currentPosition = 0;
    int lengthInSamples = 0;
    float pitch = 1;
    float volume[2] = {0,0};
};
