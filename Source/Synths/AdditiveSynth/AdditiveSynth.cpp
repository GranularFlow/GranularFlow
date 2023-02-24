/*
  ==============================================================================

    AdditiveSynth.cpp
    Created: 1 Feb 2023 9:36:43pm
    Author:  honza

  ==============================================================================
*/

#include "AdditiveSynth.h"

AdditiveSynth::AdditiveSynth()
{
    initGui();
    addListeners();
    addNewHarmonic();
}

AdditiveSynth::~AdditiveSynth()
{
    removeListeners();
}

void AdditiveSynth::initGui()
{
    addAndMakeVisible(additiveSynthSettings, 0);
    addAndMakeVisible(additiveVisualiser, 1);
}

void AdditiveSynth::paint(Graphics& g)
{
    g.fillAll(C_DARK);
}

void AdditiveSynth::resized()
{

    // Top GranularSynthSettings
    int8 topSettingsHeight = 50;

    additiveSynthSettings.setBounds(getLocalBounds().withTrimmedBottom(getHeight() - topSettingsHeight));

    // Harmonics
    for (int i = 0; i < additiveHarmonics.size(); i++)
    {
        additiveHarmonics[i]->setBounds(getLocalBounds().withTrimmedTop(topSettingsHeight + ((getHeight()- topSettingsHeight) * 2/3)));
    }
    // AudioVisualiser
    additiveVisualiser.setBounds(getLocalBounds().withTrimmedTop(topSettingsHeight).withTrimmedBottom((getHeight() - topSettingsHeight) * 1/3));
}

void AdditiveSynth::sliderValueChanged(Slider* slider)
{

    if (slider == &additiveSynthSettings.harmonicCount.slider)
    {
        int8 val = static_cast<int8>(slider->getValue());

        if (val > additiveHarmonics.size())
        {
            addNewHarmonic();
        }
        else if (val < additiveHarmonics.size())
        {
            removeHarmonic();
        }

        // After adding, select this new player
        additiveSynthSettings.harmonicSelect.slider.setValue(val);
    }
    else if (slider == &additiveSynthSettings.harmonicSelect.slider)
    {

        int8 val = static_cast<int8>(slider->getValue());

        if (additiveHarmonics.size() > val - 1)
        {
            selectHarmonic(val);
        }
        else
        {
            slider->setValue(val - 1);
        }
    }
}

void AdditiveSynth::buttonClicked(Button*)
{
}

void AdditiveSynth::addListeners()
{
    additiveSynthSettings.harmonicCount.slider.addListener(this);
    additiveSynthSettings.harmonicSelect.slider.addListener(this);
}

void AdditiveSynth::removeListeners()
{
    additiveSynthSettings.harmonicCount.slider.removeListener(this);
    additiveSynthSettings.harmonicSelect.slider.removeListener(this);
}

void AdditiveSynth::addNewHarmonic()
{
    const MessageManagerLock mmLock;
    additiveHarmonics.add(new AdditiveHarmonic(sampleRate));
    addAndMakeVisible(additiveHarmonics.getLast(), 5);
    resized();
}

void AdditiveSynth::removeHarmonic()
{
    additiveHarmonics.removeLast();
    resized();
}

void AdditiveSynth::selectHarmonic(int harmonicNumber)
{
    additiveHarmonics[harmonicNumber - 1]->toFront(true);
}

void AdditiveSynth::getNextBlock(AudioBuffer<float>& bufferToFill, juce::MidiBuffer& midiMessages)
{
   
    bufferToFill.clear();
    for (AdditiveHarmonic* harmonic : additiveHarmonics)
    {
        harmonic->fillNextBuffer(bufferToFill, midiMessages);
    }
    additiveVisualiser.pushBuffer(bufferToFill);
}

void AdditiveSynth::prepareToPlay(double sampleRateIn, int bufferSize)
{
    additiveVisualiser.clear();
    sampleRate = (int)sampleRateIn;
    bufferSize = bufferSize;
    for (AdditiveHarmonic* harmonic: additiveHarmonics)
    {
        harmonic->setSampleRate(sampleRate);
    }
}
