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
    addListeners();
    addAndMakeVisible(wavetableSettings);
}

WavetableSynth::~WavetableSynth()
{
    removeListeners();
}

void WavetableSynth::addListeners()
{
    wavetableSettings.freqKnob.slider.addListener(this);
}

void WavetableSynth::removeListeners()
{
    wavetableSettings.freqKnob.slider.removeListener(this);

}

void WavetableSynth::sliderValueChanged(Slider* slider)
{

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
            float y = interpolate(x1 + 1, x1, x2, y1, y2);

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

void WavetableSynth::prepareToPlay(double sampleRateIn)
{
    sampleRate = (float)sampleRateIn;

}

void WavetableSynth::getNextBlock(AudioBuffer<float>& bufferToFill, MidiBuffer& midiMessages)
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
           finalSample = interpolate(totalPosition, (int)std::floor(totalPosition) % sampleY.size(), (int)std::ceil(totalPosition + 1) % sampleY.size(), sampleY[(int)std::floor(totalPosition) % sampleY.size()], sampleY[(int)std::ceil(totalPosition + 1) % sampleY.size()]);

        }
        else if (wavetableSettings.isCurrentInterpolationType(WavetableSynthSettings::CUBIC))
        {
            finalSample = cubicInterpolate(totalPosition);
        }
        else if (wavetableSettings.isCurrentInterpolationType(WavetableSynthSettings::HERMITE))
        {
            finalSample = interpolateHermite(totalPosition);
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

float WavetableSynth::interpolate(float x, float x1, float x2, float y1, float y2)
{
    return y1 + ((x - x1) * ((y2 - y1) / (x2 - x1)));
}

float WavetableSynth::cubicInterpolate(float x)
{
    int n = sampleY.size() - 1;
    int i = 0;

    // find the segment containing x
    while (i < n && x > i + 1)
        i++;
    
    // calculate the coefficients of the cubic polynomial for the segment
    double h = i + 1 - i;
    double t = (x - i) / h;
    double t2 = t * t;
    double t3 = t2 * t;
    double c0 = sampleY[i];
    double c1 = h * sampleY[i + 1] - h * sampleY[i];
    double c2 = -2 * h * sampleY[i + 1] + 2 * h * sampleY[i] + 3 * (sampleY[i + 1] - sampleY[i]);
    double c3 = 1 * h * sampleY[i + 1] - 1 * h * sampleY[i] - 2 * (sampleY[i + 1] - sampleY[i]);

    // evaluate the cubic polynomial at x
    double y = c0 + c1 * t + c2 * t2 + c3 * t3;
    /*
    DBG("x " << x);
    DBG("n " << n);
    DBG("h " << h);
    DBG("t " << t);
    DBG("t2 " << t2);
    DBG("t3 " << t3);
    DBG("c0 " << c0);
    DBG("c1 " << c1);
    DBG("c2 " << c2);
    DBG("c3 " << c3);

    DBG("i " << i);
    DBG("y " << y);*/
    return y;
}

double WavetableSynth::interpolateHermite(double wantedX)
{
    int n = sampleY.size();

    // Find the interval containing the wanted x
    int i = 0;
    while (i < n - 1 && wantedX > i + 1)
        i++;

    // Compute the tangents at the interval endpoints
    double m0, m1;
    if (i == 0) {
        m0 = (sampleY[1] - sampleY[0]) / (1);
        m1 = (sampleY[2] - sampleY[1]) / (1);
    }
    else if (i == n - 2) {
        m0 = (sampleY[n - 2] - sampleY[n - 3]) / ((n - 2) - (n - 3));
        m1 = (sampleY[n - 1] - sampleY[n - 2]) / ((n - 1) - (n - 2));
    }
    else {
        double t = (wantedX - i) / (i + 1 - i);
        double t2 = t * t;

        double h00 = 2 * t2 * t - 3 * t2 + 1;
        double h10 = t2 * t - 2 * t2 + t;
        double h01 = -2 * t2 * t + 3 * t2;
        double h11 = t2 * t - t2;

        m0 = (h00 * sampleY[i] + h10 * (i + 1 - i) * m0 + h01 * sampleY[i + 1] + h11 * (i + 1 - i) * m1) / (i + 1 - i);
        m1 = (h00 * sampleY[i + 1] + h10 * (i + 1 - i) * m0 + h01 * sampleY[i + 2] + h11 * (i + 2 - i + 1) * m1) / (i + 1 - i);
    }

    // Interpolate using the Hermite formula
    double t = (wantedX - i) / (i + 1 - i);
    double t2 = t * t;
    double t3 = t2 * t;

    double h00 = 2 * t3 - 3 * t2 + 1;
    double h10 = t3 - 2 * t2 + t;
    double h01 = -2 * t3 + 3 * t2;
    double h11 = t3 - t2;

    return h00 * sampleY[i] + h10 * (i + 1 - i) * m0 + h01 * sampleY[i + 1] + h11 * (i + 1 - i) * m1;
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