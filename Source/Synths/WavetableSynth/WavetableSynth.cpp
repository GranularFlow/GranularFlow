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
    setOpaque(true);
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
    g.fillAll(Colour::fromRGB(33,33,33));
}

void WavetableSynth::resized()
{
    combineButton.setBounds(getLocalBounds().withSize(120, 40).withCentre(Point<int>(600, 30)));

    canvas1.setBounds(getLocalBounds().withTrimmedLeft(25).withTrimmedTop(100).withTrimmedBottom(getHeight() / 2).withTrimmedRight(925));
    canvas2.setBounds(getLocalBounds().withTrimmedLeft(325).withTrimmedTop(100).withTrimmedBottom(getHeight() / 2).withTrimmedRight(625));
    canvas3.setBounds(getLocalBounds().withTrimmedLeft(625).withTrimmedTop(100).withTrimmedBottom(getHeight() / 2).withTrimmedRight(325));
    canvas4.setBounds(getLocalBounds().withTrimmedLeft(925).withTrimmedTop(100).withTrimmedBottom(getHeight() / 2).withTrimmedRight(25));

    wavetableSettings.setBounds(SETTINGS_SIZE);
}

void WavetableSynth::buttonClicked(Button* button)
{
    if (button == & combineButton)
    {       

        if (canvas1.waveTableSamples.size() > 0 &&
            canvas2.waveTableSamples.size() > 0 &&
            canvas3.waveTableSamples.size() > 0)
        {
            sampleY.clear();
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
    increment = wavetableSettings.getFreq() * getTotalSampleCount() /(float)sampleRate;
}

void WavetableSynth::initSamples()
{
    currentPosition = 0;
    sampleY.clear();

    // samples from canvas1 to canvas2
    // canvas 1 samples
    for (float sample : canvas1.waveTableSamples)
    {
        sampleY.add(sample);
    }
   
    // split waves between 1-2 && 2-3
    for (int waveindex = 0; waveindex < wavetableSettings.getWaveCount() / 2; waveindex++)
    {
        for (int sampleIndex = 0; sampleIndex < 100; sampleIndex++)
        {
            sampleY.add(Utils::interpolateLinear(waveindex + 1, waveindex, (wavetableSettings.getWaveCount() / 2) + 1, canvas1.waveTableSamples[sampleIndex], canvas2.waveTableSamples[sampleIndex]));
        }
    }

    for (float sample : canvas2.waveTableSamples)
    {
        sampleY.add(sample);
    }

    for (int waveindex = 0; waveindex < wavetableSettings.getWaveCount() / 2; waveindex++)
    {
        for (int sampleIndex = 0; sampleIndex < 100; sampleIndex++)
        {
            sampleY.add(Utils::interpolateLinear(waveindex + 1, waveindex, (wavetableSettings.getWaveCount() / 2) + 1, canvas2.waveTableSamples[sampleIndex], canvas3.waveTableSamples[sampleIndex]));
        }
    }

    for (float sample : canvas3.waveTableSamples)
    {
        sampleY.add(sample);
    }
}

void WavetableSynth::prepareToPlay(float sampleRateIn, int bufferSizeIn)
{
    sampleRate = sampleRateIn;
    calculateIncrement();
}

void WavetableSynth::processBlock(AudioBuffer<float>& bufferToFill, MidiBuffer& midiMessages)
{
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
            finalSample = Utils::interpolateCubic(currentPosition - ((int)currentPosition + 1),
                sampleY[((int)currentPosition + sampleY.size()) % sampleY.size()],
                sampleY[((int)currentPosition + 1 + sampleY.size()) % sampleY.size()],
                sampleY[((int)currentPosition + 2 + sampleY.size()) % sampleY.size()],
                sampleY[((int)currentPosition + 3 + sampleY.size()) % sampleY.size()]
            );
        }
        else if (wavetableSettings.isCurrentInterpolationType(WavetableSynthSettings::HERMITE))
        {
            finalSample = Utils::interpolateHermite(currentPosition, sampleY);
        }         

        if (abs(finalSample) >= 0.9999f)
        {
            DBG("crack sample");
            finalSample = 0.5f;
        }

        bufferToFill.getWritePointer(0)[i] += (finalSample * wavetableSettings.getVolume() * wavetableSettings.getPan(0));
        bufferToFill.getWritePointer(1)[i] += (finalSample * wavetableSettings.getVolume() * wavetableSettings.getPan(1));

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