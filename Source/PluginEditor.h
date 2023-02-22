/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"


class GranularFLowAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    // Class
    GranularFLowAudioProcessorEditor (GranularFLowAudioProcessor&);
    ~GranularFLowAudioProcessorEditor() override;
    // GUI
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    GranularFLowAudioProcessor& audioProcessor;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GranularFLowAudioProcessorEditor)
};
