#include "WavetableSynth.h"


WavetableSynth::WavetableSynth()
{
    addAndMakeVisible(canvas1);
    addAndMakeVisible(canvas2);
    addAndMakeVisible(canvas3);
    addAndMakeVisible(canvas4);
    addAndMakeVisible(combineButton);
    addAndMakeVisible(wavetableSettings);

    combineButton.addListener(this);
    wavetableSettings.addSlidersListener(this);
}

WavetableSynth::~WavetableSynth()
{
    wavetableSettings.removeSlidersListener(this);
    combineButton.removeListener(this);
    removeKnobsListener();
}
void WavetableSynth::sliderValueChanged(Slider* slider)
{
    if (wavetableSettings.isWaveCountKnobSlider(slider))
    {
        combineButton.triggerClick();
    }
    else if (wavetableSettings.isFreqKnobSlider(slider))
    {
        calculateIncrement();
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

    wavetableSettings.setBounds(SETTINGS_SIZE);

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
            calculateIncrement();
            canvas4.setWaveForm(sampleY);
        }
    }
}

int WavetableSynth::getTotalSampleCount()
{
    return sampleY.size();
}

void WavetableSynth::calculateIncrement()
{
    increment = wavetableSettings.getFreq() * getTotalSampleCount() /(float) SAMPLE_RATE;
}

void WavetableSynth::initSamples()
{
    currentPosition = 0;
    sampleY.clear();
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
     
        

        if (wavetableSettings.isCurrentInterpolationType(WavetableSynthSettings::LINEAR))
        {
           finalSample = Utils::interpolateLinear(currentPosition, (int)currentPosition % sampleY.size(), ((int)currentPosition + 1) % sampleY.size(), sampleY[(int)currentPosition % sampleY.size()], sampleY[((int)currentPosition + 1) % sampleY.size()]);

        }
        else if (wavetableSettings.isCurrentInterpolationType(WavetableSynthSettings::CUBIC))
        {
            finalSample = Utils::interpolateCubic(currentPosition, sampleY);
        }
        else if (wavetableSettings.isCurrentInterpolationType(WavetableSynthSettings::HERMITE))
        {
            finalSample = Utils::interpolateHermite(currentPosition, sampleY);
        }         

        if (abs(finalSample) >= 0.9999f)
        {
            DBG("crack sample");
            finalSample = 0;
        }

        leftChannel[i] += (finalSample * wavetableSettings.getVolume() * wavetableSettings.getPan(0));
        rightChannel[i] += (finalSample * wavetableSettings.getVolume() * wavetableSettings.getPan(1));

        currentPosition = fmod((currentPosition + increment), sampleY.size());
        //currentPosition++;
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
        increment = midiMsg.getMidiNoteInHertz(lastMidiNote,440)/(float)440;
    }
    else if (midiMsg.isNoteOff() && midiMsg.getNoteNumber() == lastMidiNote)
    {
        midiNoteOn = false;
        lastMidiNote = -1;
        increment = 1.0f;
    }
}

void WavetableSynth::setKnobsListener(Knob::Listener* knobListenerPntr)
{
    wavetableSettings.setKnobsListener(knobListenerPntr);
};

void WavetableSynth::removeKnobsListener()
{
    wavetableSettings.removeKnobsListener();
};