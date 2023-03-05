/*
  ==============================================================================

    WavetableLfoVisualiser.h
    Created: 5 Feb 2023 2:53:14pm
    Author:  honza

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "../../../Utils/Constants.h"

class WavetableLfoVisualiser : public Component
{
public:
    // Class
	WavetableLfoVisualiser();
	~WavetableLfoVisualiser();

    // GUI
    void paint(Graphics&) override;
    void setWaveForm(Array<float>);

private:
    Array<float> waveForm;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(WavetableLfoVisualiser);
};
