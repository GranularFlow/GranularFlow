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
