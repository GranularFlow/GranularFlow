#include "Grain.h"


Grain::Grain() {}

Grain::~Grain() {}

int Grain::getCurrentPosition()
{
    return currentPosition;
}

int Grain::getLengthInSamples()
{
    return lengthInSamples;
}

bool Grain::isSkipped()
{
    return toSkip;
}

void Grain::setSkip()
{
    toSkip = true;
}

void Grain::setNewGrain(int startPositionIn, int sampleLengthIn, float pitchIn, float volumeLeft, float volumeRight, PlayerSettings::GranularMode granularModeIn, PlayerSettings::WindowType windowTypeIn)
{
    startingPosition = startPositionIn;
    lengthInSamples = sampleLengthIn;
    pitch = pitchIn;
    volume[0] = volumeLeft;
    volume[1] = volumeRight;
    granularMode = granularModeIn;
    windowType = windowTypeIn;

    totalPosition = 0;
    finalSample = 0;
    mirroredSample = 0;
    currentPosition = 0;
    toSkip = false;
}

void Grain::fillNextSamples(AudioBuffer<float>& sourceBuffer, AudioBuffer<float>& destinationBuffer, float increment)
{    

    for (int i = 0; i < destinationBuffer.getNumSamples(); i++) {

        if (abs(currentPosition) > lengthInSamples) {
            toSkip = true;
            return;
        }

        for (int channel = 0; channel < 2; channel++)
        {
            totalPosition = fmod((startingPosition + currentPosition) * pitch * increment, sourceBuffer.getNumSamples());

            if (totalPosition < 0)
            {
                totalPosition = fmod(sourceBuffer.getNumSamples() + totalPosition, sourceBuffer.getNumSamples());
            }

            finalSample = Utils::interpolateLinear(totalPosition,
                (int)totalPosition % sourceBuffer.getNumSamples(),
                (int)(totalPosition + 1) % sourceBuffer.getNumSamples(),
                sourceBuffer.getReadPointer(channel)[(int)totalPosition % sourceBuffer.getNumSamples()],
                sourceBuffer.getReadPointer(channel)[(int)(totalPosition + 1) % sourceBuffer.getNumSamples()]);
            
            if (granularMode == PlayerSettings::MIRROR || granularMode == PlayerSettings::REV_MIRROR)
            {
                totalPosition = fmod((startingPosition - currentPosition) * pitch, sourceBuffer.getNumSamples());

                if (totalPosition < 0)
                {
                    totalPosition = fmod(sourceBuffer.getNumSamples() + totalPosition, sourceBuffer.getNumSamples());
                }

                mirroredSample = Utils::interpolateLinear(totalPosition,
                    (int)totalPosition % sourceBuffer.getNumSamples(),
                    (int)(totalPosition + 1) % sourceBuffer.getNumSamples(),
                    sourceBuffer.getReadPointer(channel)[(int)totalPosition % sourceBuffer.getNumSamples()],
                    sourceBuffer.getReadPointer(channel)[(int)(totalPosition + 1) % sourceBuffer.getNumSamples()]);

                if (mirroredSample != 0.0)
                {
                    if (abs(mirroredSample) > 0.99999f)
                    {
                      // DBG("mirroredSample crack" << mirroredSample);
                    }
                    else
                    {
                        finalSample = (finalSample + mirroredSample) / (double)2;
                    }                    
                }
            }

            
            if (abs(finalSample) >= 0.99999f)
            {
               // DBG("grain sample crack: " << finalSample);
                return;
            }
            destinationBuffer.getWritePointer(channel)[i] += (finalSample * volume[channel] * calculateWindow(currentPosition/(float)lengthInSamples));
        }

        // Move cursor
        if (granularMode == PlayerSettings::ORDER || granularMode == PlayerSettings::MIRROR)
        {
            currentPosition++;
        }
        else if (granularMode == PlayerSettings::REV_ORDER || granularMode ==  PlayerSettings::REV_MIRROR)
        {
            currentPosition--;
        }
    }    
}

float Grain::calculateWindow(float currentPositionPercent)
{
    if (windowType == PlayerSettings::HALF_SINE)
    {
        return sin(PI * currentPositionPercent);
    }
    else if (windowType == PlayerSettings::HANN)
    {
        return (0.5f * (1.0f - cos(2.0f * PI * currentPositionPercent))); // Hann
    }
    else if (windowType == PlayerSettings::TRIANGLE)
    {
        return (1 - ((2 / (double)100) * abs((currentPositionPercent * 100) - 50))); // Triangle
    }
}
