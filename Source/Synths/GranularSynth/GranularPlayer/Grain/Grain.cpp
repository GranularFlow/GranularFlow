/*
  ==============================================================================

    Grain.cpp
    Created: 21 Nov 2022 7:52:09pm
    Author:  honza

  ==============================================================================
*/

#include "Grain.h"


Grain::Grain() {

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
bool Grain::isSkipped()
{
    return toSkip;
}

void Grain::setNewGrain(int startPositionIn, int sampleLengthIn, int offsetIn, float pitchIn, float volumeLeft, float volumeRight, PlayerSettings::GranularMode granularModeIn, PlayerSettings::WindowType windowTypeIn)
{
    startingPosition = startPositionIn;
    lengthInSamples = sampleLengthIn;
    offset = offsetIn;
    pitch = pitchIn;
    volume[0] = volumeLeft;
    volume[1] = volumeRight;
    granularMode = granularModeIn;
    windowType = windowTypeIn;
    currentPosition = 0;
    toSkip = false;
    window = 0.0f;
    currentPositionPercent = 0;
}

void Grain::fillNextSamples(AudioBuffer<float>& sourceBuffer, AudioBuffer<float>& destinationBuffer, float increment)
{    
    calculateWindow();

    currentPositionPercent = (currentPosition * 100.0 / (double)lengthInSamples);

    for (int i = 0; i < destinationBuffer.getNumSamples(); i++) {

        if (abs(currentPosition) > lengthInSamples) {
            toSkip = true;
            return;
        }

        for (int channel = 0; channel < 2; channel++)
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

            double finalSample = Utils::interpolateLinear(totalPosition, (int)std::floor(totalPosition) % sourceBuffer.getNumSamples(), (int)std::ceil(totalPosition + 1) % sourceBuffer.getNumSamples(), src[(int)std::floor(totalPosition) % sourceBuffer.getNumSamples()], src[(int)std::ceil(totalPosition + 1) % sourceBuffer.getNumSamples()]);
            
            if (granularMode == PlayerSettings::MIRROR || granularMode == PlayerSettings::REV_MIRROR)
            {
                totalPosition = fmod((startingPosition - currentPosition) * pitch, sourceBuffer.getNumSamples());

                if (totalPosition < 0)
                {
                    totalPosition = fmod(sourceBuffer.getNumSamples() + totalPosition, sourceBuffer.getNumSamples());
                }

                double mirroredSample = Utils::interpolateLinear(totalPosition, (int)std::floor(totalPosition) % sourceBuffer.getNumSamples(), (int)std::ceil(totalPosition + 1) % sourceBuffer.getNumSamples(), src[(int)std::floor(totalPosition) % sourceBuffer.getNumSamples()], src[(int)std::ceil(totalPosition + 1) % sourceBuffer.getNumSamples()]);
                
                if (mirroredSample != 0.0)
                {
                    if (abs(mirroredSample) > 0.9999)
                    {
                        DBG("mirroredSample crack" << mirroredSample);
                    }
                    finalSample = (finalSample + mirroredSample) / (double)2;
                }
            }

            
            if (abs(finalSample) >= 0.9999)
            {
                DBG("sample crack" << finalSample);
                finalSample = 0;
            }
            destinationBuffer.getWritePointer(channel)[i] += (finalSample * volume[channel] * window);
        }


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

void Grain::calculateWindow()
{
    if (windowType == PlayerSettings::HALF_SINE)
    {
        window = sin(3.14159 * currentPositionPercent / (double)100);
    }
    else if (windowType == PlayerSettings::HANN)
    {
        window = (0.5f * (1.0f - cos(2.0f * PI * (currentPositionPercent / (double)100.0)))); // Hann
    }
    else if (windowType == PlayerSettings::TRIANGLE)
    {
        window = (0.5f - (abs(currentPositionPercent - 50.0f) / (double)50.0)); // Triangle

    }
    if ((window > 1))
    {
        DBG("window cracks");
    }
}
