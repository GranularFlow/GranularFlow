#pragma once
#include <JuceHeader.h>

class AudioLoad
{

public:
    AudioLoad();
    ~AudioLoad();
    void fillBuffer(AudioBuffer<float>&, int, File);
    void clear();

    AudioBuffer<float> waveForm;
    int samplePosition = 0;
    int totalSamples = 0;
};