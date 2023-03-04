/*
  ==============================================================================

    Timing.h
    Created: 4 Mar 2023 5:42:42pm
    Author:  honza

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "../Constants.h"

class Timing : public Timer
{
public:
    struct TimingListener
    {
        virtual void timeCall(Timing*) = 0;
    };
    void setListener(TimingListener* timingPntrIn) { timingPntr = timingPntrIn; }
    void removeListener() { timingPntr = nullptr; }

	Timing();
	~Timing();
    void timerCallback()override;

private:
    TimingListener* timingPntr = nullptr;
};
