#include "PluginProcessor.h"
#include "PluginEditor.h"

GranularFlowAudioProcessorEditor::GranularFlowAudioProcessorEditor (GranularFlowAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    addAndMakeVisible(audioProcessor.granularFlowWrapper);
    setSize(W_WIDTH, W_HEIGHT);
}

GranularFlowAudioProcessorEditor::~GranularFlowAudioProcessorEditor()
{
}

void GranularFlowAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll(C_DARK_GRAY);
}

void GranularFlowAudioProcessorEditor::resized()
{
}
