/*
  ==============================================================================

    WavetableSynth.cpp
    Created: 3 Feb 2023 12:45:49pm
    Author:  honza

  ==============================================================================
*/

#include "WavetableSynth.h"


WavetableSynth::WavetableSynth()
{
    addAndMakeVisible(canvas1);
    addAndMakeVisible(canvas2);
    addAndMakeVisible(canvas3);
    addAndMakeVisible(canvas4);
    addAndMakeVisible(combineButton);
    combineButton.addListener(this);
    wavetableSettings.waveCountKnob.slider.addListener(this);
    addAndMakeVisible(wavetableSettings);
}

WavetableSynth::~WavetableSynth()
{
    wavetableSettings.waveCountKnob.slider.removeListener(this);
    combineButton.removeListener(this);
    removeKnobsListener();
}
void WavetableSynth::sliderValueChanged(Slider* slider)
{
    if (slider == &wavetableSettings.waveCountKnob.slider)
    {
        combineButton.triggerClick();
    }
}

void WavetableSynth::paint(Graphics& g)
{
    g.fillAll(C_DARK);
}

void WavetableSynth::resized()
{
    combineButton.setBounds(getLocalBounds().withSize(120, 40).withCentre(Point<int>((getWidth()/2), 30)));

    int margin = 25;
    canvas1.setBounds(getLocalBounds().withTrimmedLeft(margin).withTrimmedTop(100).withTrimmedBottom(getHeight()/ 2).withTrimmedRight(margin + (W_WIDTH * 3/4)));
    canvas2.setBounds(getLocalBounds().withTrimmedLeft(margin + (W_WIDTH * 1 / 4)).withTrimmedTop(100).withTrimmedBottom(getHeight() / 2).withTrimmedRight(margin + (W_WIDTH * 2 / 4)));
    canvas3.setBounds(getLocalBounds().withTrimmedLeft(margin + (W_WIDTH * 2 / 4)).withTrimmedTop(100).withTrimmedBottom(getHeight() / 2).withTrimmedRight(margin + (W_WIDTH * 1 / 4)));
    canvas4.setBounds(getLocalBounds().withTrimmedLeft(margin + (W_WIDTH * 3 / 4)).withTrimmedTop(100).withTrimmedBottom(getHeight() / 2).withTrimmedRight(margin));

    wavetableSettings.setBounds(getLocalBounds()
        .withTrimmedTop((getHeight()* 2/3) * 1.01)
        .withTrimmedLeft(getWidth() * 0.01)
        .withTrimmedRight(getWidth() * 0.01)
        .withTrimmedBottom(getWidth() * 0.01)
    );
}

void WavetableSynth::buttonClicked(Button* button)
{
    if (button == & combineButton)
    {
        sampleY.clear();

        if (canvas1.waveTableSamples.size() > 0 &&
            canvas2.waveTableSamples.size() > 0 &&
            canvas3.waveTableSamples.size() > 0)
        {
            initSamples(); 
            canvas4.setWaveForm(sampleY);
        }
    }
}

void WavetableSynth::initSamples()
{
    // samples from canvas1 to canvas2
    // canvas 1 samples
    for (int i = 0; i < canvas1.waveTableSamples.size(); i++)
    {
        sampleY.add(canvas1.waveTableSamples[i]);
    }   

    // split waves between 1-2 && 2-3
    int semiWaves = wavetableSettings.getWaveCount() / 2;

    Array<Array<float>> samplesForEachWave;
    for (int sampleIndex = 0; sampleIndex < canvas1.waveTableSamples.size(); sampleIndex++)
    {
        Array<float> onePointEachWave;
        onePointEachWave.add(canvas1.waveTableSamples[sampleIndex]);
        for (int waveindex = 0; waveindex < semiWaves; waveindex++)
        {
            float y2 = canvas2.waveTableSamples[sampleIndex];
            float y1 = onePointEachWave.getLast();
            int x1 = waveindex;
            int x2 = semiWaves+1;
            //float y = (y1 + (x - x1) * (y2 - y1) / (x2 - x1));
            float y = (y1 + (x1+1 - x1) * (y2 - y1) / (x2 - x1));

            onePointEachWave.add(y);
        }
        samplesForEachWave.add(onePointEachWave);
    }

    for (int waveIndex = 0; waveIndex < semiWaves; waveIndex++)
    {
        for (int sampleIndex = 0; sampleIndex < samplesForEachWave.size(); sampleIndex++)
        {
            sampleY.add(samplesForEachWave[sampleIndex][waveIndex]);
        }
    }

    // add second wave
    for (int i = 0; i < canvas2.waveTableSamples.size(); i++)
    {
        sampleY.add(canvas2.waveTableSamples[i]);
    }

    samplesForEachWave.clear();
    for (int sampleIndex = 0; sampleIndex < canvas2.waveTableSamples.size(); sampleIndex++)
    {
        Array<float> onePointEachWave;
        onePointEachWave.add(canvas2.waveTableSamples[sampleIndex]);
        for (int waveindex = 0; waveindex < semiWaves; waveindex++)
        {
            float y2 = canvas3.waveTableSamples[sampleIndex];
            float y1 = onePointEachWave.getLast();
            int x1 = waveindex;
            int x2 = semiWaves + 1;
            
            //float (float x, float x1, float x2, float y1, float y2
            float y = Utils::interpolateLinear(x1 + 1, x1, x2, y1, y2);

            onePointEachWave.add(y);
        }
        samplesForEachWave.add(onePointEachWave);
    }

    for (int waveIndex = 0; waveIndex < semiWaves; waveIndex++)
    {
        for (int sampleIndex = 0; sampleIndex < samplesForEachWave.size(); sampleIndex++)
        {
            sampleY.add(samplesForEachWave[sampleIndex][waveIndex]);
        }
    }


    // add last wave
    for (int i = 0; i < canvas3.waveTableSamples.size(); i++)
    {
        sampleY.add(canvas3.waveTableSamples[i]);
    }
}

void WavetableSynth::prepareToPlay(float sampleRateIn, int bufferSizeIn)
{
    sampleRate = sampleRateIn;

}

void WavetableSynth::processBlock(AudioBuffer<float>& bufferToFill, MidiBuffer& midiMessages)
{
    float* leftChannel = bufferToFill.getWritePointer(0);
    float* rightChannel = bufferToFill.getWritePointer(1);
    frequency = wavetableSettings.freqKnob.getValue();
    increment = frequency / (float)440.f;

    if (sampleY.size() != (wavetableSettings.getWaveCount() + 3) * 100)
    {
        return;
    }

    if (wavetableSettings.isCurrentMidiMode(WavetableSynthSettings::MidiMode::ON))
    {
        handleMidi(midiMessages);
        if (!midiNoteOn) {
            return;
        }
    }
    for (int i = 0; i < bufferToFill.getNumSamples(); i++)
    {
        float totalPosition = fmod((currentPosition * increment), sampleY.size());

        if (totalPosition < 0)
        {
            totalPosition = sampleY.size() - fmod(abs(totalPosition), sampleY.size());
        }

        if (totalPosition > sampleY.size() || totalPosition + 2 > sampleY.size())
        {
            totalPosition = fmod(totalPosition, sampleY.size());
        }

        float finalSample = 0;
        if (wavetableSettings.isCurrentInterpolationType(WavetableSynthSettings::LINEAR))
        {
           finalSample = Utils::interpolateLinear(totalPosition, (int)std::floor(totalPosition) % sampleY.size(), (int)std::ceil(totalPosition + 1) % sampleY.size(), sampleY[(int)std::floor(totalPosition) % sampleY.size()], sampleY[(int)std::ceil(totalPosition + 1) % sampleY.size()]);

        }
        else if (wavetableSettings.isCurrentInterpolationType(WavetableSynthSettings::CUBIC))
        {
            finalSample = Utils::interpolateCubic(totalPosition, sampleY);
        }
        else if (wavetableSettings.isCurrentInterpolationType(WavetableSynthSettings::HERMITE))
        {
            finalSample = Utils::interpolateHermite(totalPosition, sampleY);
        }
         

        if (abs(finalSample) >= 0.9999f)
        {
            DBG("crack sample");
            finalSample = 0;
        }

        leftChannel[i] += (finalSample * wavetableSettings.getVolume() * wavetableSettings.getPan(0));
        rightChannel[i] += (finalSample * wavetableSettings.getVolume() * wavetableSettings.getPan(1));
        currentPosition++;
    }   
}

void WavetableSynth::handleMidi(MidiBuffer& midiMessages)
{
    MidiBuffer::Iterator iter(midiMessages);
    MidiMessage midiMsg;
    int midiPos;
    iter.getNextEvent(midiMsg, midiPos);
    if (midiMsg.isNoteOn() && midiMsg.getNoteNumber() != lastMidiNote)
    {
        midiNoteOn = true;
        lastMidiNote = midiMsg.getNoteNumber();
        increment = std::powf(2.f, (midiMsg.getNoteNumber() - 69.f) / 12.f);
    }
    else if (midiMsg.isNoteOff() && midiMsg.getNoteNumber() == lastMidiNote)
    {
        midiNoteOn = false;
        lastMidiNote = -1;
        increment = 1.0f;
    }
}

void WavetableSynth::setKnobsListener(Knob::KnobListener* knobListenerPntr)
{
    wavetableSettings.freqKnob.setListener(knobListenerPntr);
    wavetableSettings.waveCountKnob.setListener(knobListenerPntr);
    wavetableSettings.volumeKnob.setListener(knobListenerPntr);
    wavetableSettings.panKnob.setListener(knobListenerPntr);
};

void WavetableSynth::removeKnobsListener()
{
    wavetableSettings.freqKnob.removeListener();
    wavetableSettings.waveCountKnob.removeListener();
    wavetableSettings.volumeKnob.removeListener();
    wavetableSettings.panKnob.removeListener();
};