#include "PluginProcessor.h"
#include "PluginEditor.h"

GranularFLowAudioProcessorEditor::GranularFLowAudioProcessorEditor (GranularFLowAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    addAndMakeVisible(audioProcessor.granularFlowWrapper);
    setSize (W_WIDTH, W_HEIGHT);
}

GranularFLowAudioProcessorEditor::~GranularFLowAudioProcessorEditor()
{
}

void GranularFLowAudioProcessorEditor::paint (juce::Graphics& g)
{
    Utils::paintLogo(g);
}

void GranularFLowAudioProcessorEditor::resized()
{
    audioProcessor.granularFlowWrapper.setBounds(getLocalBounds());
}
