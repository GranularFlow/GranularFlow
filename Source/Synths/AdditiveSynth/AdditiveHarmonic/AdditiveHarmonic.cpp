#include "AdditiveHarmonic.h"

AdditiveHarmonic::AdditiveHarmonic()
{
    settings.addPhaseSliderListener(this);
    settings.addFreqSliderListener(this);
    addAndMakeVisible(settings);

    setOpaque(true);
}

AdditiveHarmonic::~AdditiveHarmonic()
{
    settings.removePhaseSliderListener(this);
    settings.removeFreqSliderListener(this);
    removeKnobsListener();
}

void AdditiveHarmonic::paint(Graphics& g)
{
   // DBG("AdditiveHarmonic::paint");
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
    sampleRate = sampleRateIn;
    calculateDelta();
}

void AdditiveHarmonic::calculateDelta()
{
    delta = (double)2.0 * PI * ((frequency) / sampleRate);
}

void AdditiveHarmonic::handleMidi(MidiBuffer& midiMessages)
{
    MidiBuffer::Iterator iter(midiMessages);
    MidiMessage midiMsg;
    int midiPos;
    iter.getNextEvent(midiMsg, midiPos);
    if (midiMsg.isNoteOn() && midiMsg.getNoteNumber() != lastMidiNote)
    {
        angle = 0;
        midiNoteOn = true;
        lastMidiNote = midiMsg.getNoteNumber();
        frequency = midiMsg.getMidiNoteInHertz(lastMidiNote, 440);
    }
    else if (midiMsg.isNoteOff() && midiMsg.getNoteNumber() == lastMidiNote)
    {
        angle = 0;
        midiNoteOn = false;
        lastMidiNote = -1;
        frequency = settings.getFreq();
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

