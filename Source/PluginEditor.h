#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"


class GranularFlowAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    // -----------------------
    // Class
    GranularFlowAudioProcessorEditor (GranularFlowAudioProcessor&);
    ~GranularFlowAudioProcessorEditor() override;
    // -----------------------
    // GUI
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    GranularFlowAudioProcessor& audioProcessor;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GranularFlowAudioProcessorEditor)
};
