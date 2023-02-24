/*
  ==============================================================================

    AudioLoad.cpp
    Created: 17 Nov 2022 4:31:35pm
    Author:  honza

  ==============================================================================
*/

#include "AudioLoad.h"

AudioLoad::AudioLoad() {
}
AudioLoad::~AudioLoad()
{
}

void AudioLoad::clear()
{
    waveForm.clear();
    samplePosition = 0;
    totalSamples = 0;
}

void AudioLoad::fillBuffer(AudioBuffer<float>& bufferToFill, int numSamplesToFill, File audioFile) {
    AudioFormatManager formatManager;
    formatManager.registerBasicFormats();

    if (audioFile != juce::File{}) {
        DBG("isnt file empty");
        std::unique_ptr<AudioFormatReader> reader(formatManager.createReaderFor(audioFile));

        int minFill = 0;

        if (reader != nullptr)
        {
            DBG("reader can read");
            minFill = (numSamplesToFill == -1) ? reader->lengthInSamples : numSamplesToFill;
            reader->read(&bufferToFill, 0, minFill, 0, true, true);
            samplePosition += minFill;
        }
    }
    else
    {
        DBG("failed");
    }

}
