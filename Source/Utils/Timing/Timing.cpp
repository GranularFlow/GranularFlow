/*
  ==============================================================================

    Timing.cpp
    Created: 4 Mar 2023 5:42:42pm
    Author:  honza

  ==============================================================================
*/

#include "Timing.h"

Timing::Timing()
{
}

Timing::~Timing()
{
}

void Timing::timerCallback()
{
    if (timingPntr != nullptr)
    {
        timingPntr->timeCall(this);
    }
}
