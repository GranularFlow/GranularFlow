#pragma once
#include <JuceHeader.h>

class AudioLoad
{

public:
    AudioLoad();
    ~AudioLoad();

    
    AudioBuffer<float> waveForm;
    int64 samplePosition = 0;
    int64 totalSamples = 0;

    void fillBuffer(AudioBuffer<float>&, int, File);
    void clear();
};