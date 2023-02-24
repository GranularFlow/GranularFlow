/*
  ==============================================================================

    GranularSettings.h
    Created: 18 Nov 2022 12:48:24pm
    Author:  honza

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "../../../Utils/Constants.h"
#include "../../../Utils/Utils.h"
#include "../../../CustomComponents/CustomLooks/Knob.h"
#include "../../../CustomComponents/CustomLooks/RadioBox.h"
#include "../../../CustomComponents/CustomLooks/NumberSelect.h"

class GranularSettings : public Component
{
public:
    enum INPUT
    {
        BUFFER,
        FILE
    };

    // Class
    GranularSettings();
    ~GranularSettings() override;
    // Utils
    void addComponents();
    // GUI
    void enablePlayers();
    void paint (Graphics&) override;
    void resized() override;

    // Buffer length - number of buffers to play from
    NumberSelect timeLengthNum{ "Length", C_ANDROID ,1.0, 3.0, 0.1, 3.0 };
    TextButton openBufferButton{ "BUFFER" };
    // Open file button
    TextButton openAudioButton{ "FILE" };
    // Player settings
    NumberSelect playerCountNum{ "Count", C_BARARED, 0, 3, 1, 0 };
    NumberSelect playerSelectNum{ "Select", C_MARINE, 0, 3, 1, 0 };

   

private:

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GranularSettings)
};
