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
    addAndMakeVisible(settings);
    addAndMakeVisible(visualiser);
    settings.addListener(this);

    for (int i = 0; i < 5; i++)
    {
        harmonics.add(new AdditiveHarmonic());
        harmonics[i]->setKnobsListener(knobListener);
        addAndMakeVisible(harmonics.getLast());
    }
    harmonics[0]->toFront(true);
}

AdditiveSynth::~AdditiveSynth()
{
    settings.removeListener(this);
    harmonics.clear();
    knobListener = nullptr;
}

void AdditiveSynth::paint(Graphics& g)
{
    g.fillAll(C_DARK);
}

void AdditiveSynth::resized()
{

    settings.setBounds(getLocalBounds().withTrimmedBottom(getHeight() - TOP_BAR_HEIGHT));

    // Harmonics
    for (int i = 0; i < harmonics.size(); i++)
    {
        harmonics[i]->setBounds(SETTINGS_SIZE);
    }
    // AudioVisualiser
    visualiser.setBounds(getLocalBounds().withTrimmedTop(TOP_BAR_HEIGHT).withTrimmedBottom(((getHeight() - TOP_BAR_HEIGHT) / 2) + TOP_BAR_HEIGHT));
}

void AdditiveSynth::sliderValueChanged(Slider* slider)
{

    if (settings.isHarmonicCountSlider(slider))
    {
        int8 val = static_cast<int8>(slider->getValue());

        if (val > activeHarmonics)
        {
            addNewHarmonic();
        }
        else if (val < activeHarmonics)
        {
            removeHarmonic();
        }

        // After adding, select this new player
        settings.getHarmonicSelect().setValue(val, sendNotification);
    }
    else if (settings.isHarmonicSelectSlider(slider))
    {

        int8 val = static_cast<int8>(slider->getValue());

        if (activeHarmonics > val - 1)
        {
            selectHarmonic(val);
        }
        else
        {
            slider->setValue(val - 1);
        }
    }
}

void AdditiveSynth::addNewHarmonic()
{
    harmonicsToAdd++;
    activeHarmonics++;
}

void AdditiveSynth::removeHarmonic()
{
    activeHarmonics--;
    harmonics[activeHarmonics]->reset();
    resized();
}

void AdditiveSynth::selectHarmonic(int harmonicNumber)
{
    harmonics[harmonicNumber - 1]->toFront(true);
}

void AdditiveSynth::processBlock(AudioBuffer<float>& bufferToFill, juce::MidiBuffer& midiMessages)
{
    if (harmonicsToAdd > 0)
    {
        for (int i = 0; i < harmonicsToAdd; i++)
        {
            harmonics[activeHarmonics - harmonicsToAdd + i]->setAngle(harmonics[0]->getAngle());
        }
        harmonicsToAdd = 0;
    }


    for (int i = 0; i < activeHarmonics; i++)
    {
        harmonics[i]->processBlock(bufferToFill, midiMessages);
    }

    visualiser.pushBuffer(bufferToFill);
}

void AdditiveSynth::prepareToPlay(float sampleRate, int bufferSize)
{
    visualiser.clear();
    for (AdditiveHarmonic* harmonic : harmonics)
    {
        harmonic->prepareToPlay(sampleRate, bufferSize);
    }
}

void AdditiveSynth::setKnobsListener(Knob::KnobListener* knobListenerPntr)
{
    knobListener = knobListenerPntr;
}