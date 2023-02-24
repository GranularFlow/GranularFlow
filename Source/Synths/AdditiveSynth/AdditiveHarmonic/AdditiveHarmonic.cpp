/*
  ==============================================================================

    AdditiveHarmonic.cpp
    Created: 1 Feb 2023 11:01:49pm
    Author:  honza

  ==============================================================================
*/

#include "AdditiveHarmonic.h"

AdditiveHarmonic::AdditiveHarmonic(int sampleRateIn)
{
    sampleRate = sampleRateIn;
    addListeners();
    addAndMakeVisible(harmonicSettings);
    startTimer(1);
}

AdditiveHarmonic::~AdditiveHarmonic()
{
    stopTimer();

}

void AdditiveHarmonic::paint(Graphics& g)
{
    //g.fillAll(C_GRASS);
}

void AdditiveHarmonic::resized()
{
    harmonicSettings.setBounds(getLocalBounds()
        .withTrimmedTop(getWidth() * 0.01)
        .withTrimmedLeft(getWidth() * 0.01)
        .withTrimmedRight(getWidth() * 0.01)
        .withTrimmedBottom(getWidth() * 0.01)
    );

}

void AdditiveHarmonic::addListeners()
{
    harmonicSettings.phaseKnob.slider.addListener(this);
    harmonicSettings.freqKnob.slider.addListener(this);
}

void AdditiveHarmonic::removeListeners()
{
    harmonicSettings.phaseKnob.slider.removeListener(this);
    harmonicSettings.freqKnob.slider.removeListener(this);
}

void AdditiveHarmonic::timerCallback()
{
}

void AdditiveHarmonic::sliderValueChanged(Slider* slider)
{
    if (slider == &harmonicSettings.phaseKnob.slider){
        phase = slider->getValue();
    }
    else if (slider == &harmonicSettings.freqKnob.slider) {
        frequency = slider->getValue();
        calculateDelta();
    }
}

void AdditiveHarmonic::fillNextBuffer(AudioBuffer<float>& bufferToFill, juce::MidiBuffer& midiMessages)
{
    float* leftChannel = bufferToFill.getWritePointer(0);
    float* rightChannel = bufferToFill.getWritePointer(1);

    if (harmonicSettings.isCurrentMidiMode(AdditiveHarmonicSettings::MidiMode::ON))
    {
        handleMidi(midiMessages);
        if (midiNoteOn) {
            calculateDelta();
            if (!lastMidiMode)
            {
                lastMidiMode = true;
                angle = 0.0;
            }
            for (int i = 0; i < bufferToFill.getNumSamples(); i++)
            {
                leftChannel[i] += sin(angle + getPhaseRads()) * harmonicSettings.getVolume() * harmonicSettings.getPan(0);
                rightChannel[i] += sin(angle + getPhaseRads()) * harmonicSettings.getVolume() * harmonicSettings.getPan(1);
                angle += delta;
                angle = fmod(angle, 2 * getPi());
            }
        }
    }
    else
    {
        for (int i = 0; i < bufferToFill.getNumSamples(); i++)
        {
            leftChannel[i] += sin(angle + getPhaseRads()) * harmonicSettings.getVolume() * harmonicSettings.getPan(0);
            rightChannel[i] += sin(angle + getPhaseRads()) * harmonicSettings.getVolume() * harmonicSettings.getPan(1);
            angle += delta;
            angle = fmod(angle, 2 * getPi());
        }
    }

    
}

void AdditiveHarmonic::changeTimer(float)
{
}

void AdditiveHarmonic::setSampleRate(int sampleRateIn)
{
    sampleRate = sampleRateIn;
    calculateDelta();
}

void AdditiveHarmonic::calculateDelta()
{
    delta = (double)2.0 * getPi() * ((frequency + midiNoteFrequency) / (double)sampleRate);
}

void AdditiveHarmonic::handleMidi(MidiBuffer& midiMessages)
{
    MidiBuffer::Iterator iter(midiMessages);
    MidiMessage midiMsg;
    int midiPos;
    iter.getNextEvent(midiMsg, midiPos);
    if (midiMsg.isNoteOn() && midiMsg.getNoteNumber() != lastMidiNote)
    {
        DBG("on");
        midiNoteOn = true;
        lastMidiNote = midiMsg.getNoteNumber();
        midiNoteFrequency = midiMsg.getMidiNoteInHertz(lastMidiNote, frequency); // freq maybe?
    }
    else if (midiMsg.isNoteOff() && midiMsg.getNoteNumber() == lastMidiNote)
    {
        DBG("off");
        midiNoteOn = false;
        lastMidiNote = -1;
        midiNoteFrequency = 0.f;
    }
}

double AdditiveHarmonic::getPhaseRads()
{
    return (phase * getPi() / (double)180.f);
}

double AdditiveHarmonic::getPi()
{
    return juce::MathConstants<double>::pi;
}

