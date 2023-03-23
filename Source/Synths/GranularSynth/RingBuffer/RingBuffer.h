#pragma once
#include <JuceHeader.h>
#include "../../../Utils/Constants.h"
class RingBuffer
{
public:
    // ----------------------
    // Class
	RingBuffer();
	~RingBuffer();
    // ----------------------
    // Process
    void addBuffer(AudioBuffer<float>&);
    AudioBuffer<float>& getBuffer();   
    // ----------------------
    // Get
    int getSize();
    bool readyToBeConsumed();

private:
    AudioBuffer<float> ringBuffer { 2, 144000 };
    int writePosition = 144000/2;
    int readPosition = 0;
};

