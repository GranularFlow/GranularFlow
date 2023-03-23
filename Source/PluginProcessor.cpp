#include "PluginProcessor.h"
#include "PluginEditor.h"

GranularFlowAudioProcessor::GranularFlowAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
}

GranularFlowAudioProcessor::~GranularFlowAudioProcessor()
{
}

//==============================================================================
void GranularFlowAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    granularFlowWrapper.prepareToPlay(sampleRate, samplesPerBlock);
}

void GranularFlowAudioProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    granularFlowWrapper.processBlock(buffer, midiMessages);
}

//==============================================================================
const juce::String GranularFlowAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool GranularFlowAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool GranularFlowAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool GranularFlowAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double GranularFlowAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int GranularFlowAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int GranularFlowAudioProcessor::getCurrentProgram()
{
    return 0;
}

void GranularFlowAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String GranularFlowAudioProcessor::getProgramName (int index)
{
    return {};
}

void GranularFlowAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

void GranularFlowAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool GranularFlowAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

bool GranularFlowAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* GranularFlowAudioProcessor::createEditor()
{
    return new GranularFlowAudioProcessorEditor (*this);
}

//==============================================================================
void GranularFlowAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void GranularFlowAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new GranularFlowAudioProcessor();
}
