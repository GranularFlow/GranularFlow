#include "AdditiveHarmonic.h"

AdditiveHarmonic::AdditiveHarmonic()
{
    settings.addPhaseSliderListener(this);
    settings.addFreqSliderListener(this);
    addAndMakeVisible(settings);
}

AdditiveHarmonic::~AdditiveHarmonic()
{
    settings.removePhaseSliderListener(this);
    settings.removeFreqSliderListener(this);
    removeKnobsListener();
}

void AdditiveHarmonic::paint(Graphics& g)
{
}

void AdditiveHarmonic::resized()
{
    settings.setBounds(getLocalBounds());
}


void AdditiveHarmonic::sliderValueChanged(Slider* slider)
{
    if (settings.isPhaseKnob(slider)){
        phase = slider->getValue();
    }
    else if (settings.isFreqKnob(slider)) {
        frequency = slider->getValue();
        calculateDelta();
    }
}

void AdditiveHarmonic::processBlock(AudioBuffer<float>& bufferToFill, juce::MidiBuffer& midiMessages)
{
    if (settings.isCurrentMidiMode(AdditiveHarmonicSettings::MidiMode::ON))
    {
        handleMidi(midiMessages);
        if (!midiNoteOn) {
            return;
        }
    }

    for (int i = 0; i < bufferToFill.getNumSamples(); i++)
    {
        bufferToFill.getWritePointer(0)[i] += sin(angle + Utils::degToRad(phase)) * settings.getVolume() * settings.getPan(0);
        bufferToFill.getWritePointer(1)[i] += sin(angle + Utils::degToRad(phase)) * settings.getVolume() * settings.getPan(1);
        angle += delta;
        angle = fmod(angle, 2 * PI);
    }            
}

void AdditiveHarmonic::prepareToPlay(float sampleRateIn, int bufferSize)
{
    calculateDelta();
}

void AdditiveHarmonic::calculateDelta()
{
    delta = (double)2.0 * PI * ((frequency + midiNoteFrequency) / (double)SAMPLE_RATE);
}

void AdditiveHarmonic::handleMidi(MidiBuffer& midiMessages)
{
    MidiBuffer::Iterator iter(midiMessages);
    MidiMessage midiMsg;
    int midiPos;
    iter.getNextEvent(midiMsg, midiPos);
    if (midiMsg.isNoteOn() && midiMsg.getNoteNumber() != lastMidiNote)
    {
        midiNoteOn = true;
        lastMidiNote = midiMsg.getNoteNumber();
        midiNoteFrequency = midiMsg.getMidiNoteInHertz(lastMidiNote, frequency);
    }
    else if (midiMsg.isNoteOff() && midiMsg.getNoteNumber() == lastMidiNote)
    {
        midiNoteOn = false;
        lastMidiNote = -1;
        midiNoteFrequency = 0.f;
    }
    calculateDelta();
}

void AdditiveHarmonic::setAngle(double angleIn)
{
    angle = angleIn;
    calculateDelta();
}

double AdditiveHarmonic::getAngle()
{
    return angle;
}

void AdditiveHarmonic::reset()
{
    angle = 0;
    settings.resetDefaultValues();
}

void AdditiveHarmonic::setKnobsListener(Knob::Listener* knobListenerPntr)
{
    settings.setKnobsListener(knobListenerPntr);
}

void AdditiveHarmonic::removeKnobsListener()
{
    settings.removeKnobsListener();
}

