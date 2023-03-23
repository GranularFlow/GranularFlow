#include "PluginProcessor.h"
#include "PluginEditor.h"

GranularFlowAudioProcessorEditor::GranularFlowAudioProcessorEditor (GranularFlowAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
   //// DBG("GranularFlowAudioProcessorEditor()");

    addAndMakeVisible(audioProcessor.granularFlowWrapper);
    setSize(1200, 700);
}

GranularFlowAudioProcessorEditor::~GranularFlowAudioProcessorEditor()
{
}

void GranularFlowAudioProcessorEditor::paint (juce::Graphics& g)
{
   // DBG("GranularFlowAudioProcessorEditor::paint");
    g.fillAll(Colour::fromRGB(33, 33, 33));
}

void GranularFlowAudioProcessorEditor::resized()
{

   //// DBG("GranularFlowAudioProcessorEditor::resized()");
}
