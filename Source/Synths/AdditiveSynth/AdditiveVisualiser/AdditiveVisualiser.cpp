/*
  ==============================================================================

    AdditiveVisualiser.cpp
    Created: 1 Feb 2023 11:15:23pm
    Author:  honza

  ==============================================================================
*/

#include "AdditiveVisualiser.h"

AdditiveVisualiser::AdditiveVisualiser():AudioVisualiserComponent (2)
{
    setBufferSize(256);
    setSamplesPerBlock(25);
    setSamplesPerBlock(25);
    setColours(C_DARK, L_GRAY);
}

AdditiveVisualiser::~AdditiveVisualiser()
{
}
