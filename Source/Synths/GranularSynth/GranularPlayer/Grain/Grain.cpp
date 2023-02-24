/*
  ==============================================================================

    Grain.cpp
    Created: 21 Nov 2022 7:52:09pm
    Author:  honza

  ==============================================================================
*/

#include "Grain.h"


Grain::Grain(int startPositionIn, int sampleLengthIn, int offsetIn, float pitchIn, float volumeLeft, float volumeRight)
{
    startingPosition = startPositionIn;
    lengthInSamples = sampleLengthIn;
    offset = offsetIn;
    pitch = pitchIn;
    volume[0] = volumeLeft;
    volume[1] = volumeRight;
}

Grain::~Grain()
{
    
}

int Grain::getCurrentPosition()
{
    return currentPosition;
}

int Grain::getLengthInSamples()
{
    return lengthInSamples;
}

int Grain::getDelete()
{
    return toDelete;
}

void Grain::fillNextSamples(AudioBuffer<float>& sourceBuffer, AudioBuffer<float>& destinationBuffer, PlayerSettings* settings, int totalSamples, float increment)
{
    
    float window = 0.0f;
    float percent = (currentPosition * 100.0 / (float)lengthInSamples);

    if (settings->isWindowType(PlayerSettings::HALF_SINE))
    {
        window = sin(3.14159 * percent / (float)100);
    }
    else if (settings->isWindowType(PlayerSettings::HANN))
    {
        window = ( 0.5f * (1.0f - cos(2.0f * 3.14159f * (percent / (float)100.0)))); // Hann
    }
    else if (settings->isWindowType(PlayerSettings::TRIANGLE))
    {
        window = (0.5f - (abs(percent - 50.0f) /(float) 50.0)); // Triangle
        
    }
    if ((window > 1))
    {
        DBG("window cracks");
    }
    for (int i = 0; i < destinationBuffer.getNumSamples(); i++) {

        if (abs(currentPosition) > lengthInSamples) {
            toDelete = true;
            return;
        }

        for (int8 channel = 0; channel < 2; channel++)
        {
            // Apply envelope, apply volume, apply panning+
            auto src = sourceBuffer.getReadPointer(channel);
            float totalPosition = fmod((startingPosition + currentPosition) * pitch * increment, sourceBuffer.getNumSamples());

            if (totalPosition < 0)
            {
                totalPosition = sourceBuffer.getNumSamples() - fmod(abs(totalPosition), sourceBuffer.getNumSamples());
            }

            if (totalPosition > sourceBuffer.getNumSamples() || totalPosition + 2 > sourceBuffer.getNumSamples())
            {
                totalPosition = fmod(totalPosition, sourceBuffer.getNumSamples());
            }

            float finalSample = interpolate(totalPosition, (int)std::floor(totalPosition) % sourceBuffer.getNumSamples(), (int)std::ceil(totalPosition + 1) % sourceBuffer.getNumSamples(), src[(int)std::floor(totalPosition) % sourceBuffer.getNumSamples()], src[(int)std::ceil(totalPosition + 1) % sourceBuffer.getNumSamples()]);
            
            if (settings->isGranularMode(PlayerSettings::MIRROR) || settings->isGranularMode(PlayerSettings::REV_MIRROR))
            {
                totalPosition = fmod((startingPosition - currentPosition) * pitch, sourceBuffer.getNumSamples());

                if (totalPosition < 0)
                {
                    totalPosition = fmod(sourceBuffer.getNumSamples() + totalPosition, sourceBuffer.getNumSamples());
                    //DBG("totalPosition" << totalPosition);
                }

                //DBG("totalPosition" << totalPosition);
                float mirroredSample = interpolate(totalPosition, (int)std::floor(totalPosition) % sourceBuffer.getNumSamples(), (int)std::ceil(totalPosition + 1) % sourceBuffer.getNumSamples(), src[(int)std::floor(totalPosition) % sourceBuffer.getNumSamples()], src[(int)std::ceil(totalPosition + 1) % sourceBuffer.getNumSamples()]);
                
                if (mirroredSample != 0.0f)
                {
                    if (abs(mirroredSample) > 0.999f)
                    {
                        DBG("mirroredSample crack" << mirroredSample);
                    }
                    finalSample = (finalSample + mirroredSample) / (float)2.0f;
                }
            }

            
            if (abs(finalSample) >= 0.9999f)
            {
                DBG("sample crack" << finalSample);
                finalSample = 0;
            }
            destinationBuffer.getWritePointer(channel)[i] += (finalSample * volume[channel] * window) /(float)( settings->getNumGrains()*0.1f);
        }


        if (settings->isGranularMode(PlayerSettings::ORDER) || settings->isGranularMode(PlayerSettings::MIRROR))
        {
            currentPosition++;
        }
        else if (settings->isGranularMode(PlayerSettings::REV_ORDER) || settings->isGranularMode(PlayerSettings::REV_MIRROR))
        {
            currentPosition--;
        }

    }
    
}

float Grain::interpolate(float x, float x1, float x2, float y1, float y2)
{
    return y1 + ((x - x1) * ((y2 - y1) / (x2 - x1)));
}

float Grain::getEnvelope()
{
    return currentPosition;
}
