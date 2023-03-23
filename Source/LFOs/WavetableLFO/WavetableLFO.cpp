#include "WavetableLFO.h"


WavetableLFO::WavetableLFO()
{
    addAndMakeVisible(canvas1);
    addAndMakeVisible(canvas2);
    addAndMakeVisible(canvas3);
    addAndMakeVisible(canvas4);
    addAndMakeVisible(combineButton);
    addAndMakeVisible(settings);

    combineButton.addListener(this);
    settings.addWaveCountListener(this);
    setOpaque(true);
}

WavetableLFO::~WavetableLFO()
{
    settings.removeWaveCountListener(this);
}

void WavetableLFO::sliderValueChanged(Slider* slider)
{
    if (settings.isWaveCountSlider(slider))
    {
        combineButton.triggerClick();
    }
}

void WavetableLFO::paint(Graphics& g)
{
    g.fillAll(Colour::fromRGB(33,33,33));
    Utils::paintLogo(g);
}

void WavetableLFO::resized()
{
    combineButton.setBounds(getLocalBounds().withSize(120, 40).withCentre(Point<int>((getWidth() / 2), 30)));

    canvas1.setBounds(getLocalBounds().withTrimmedLeft(25).withTrimmedTop(100).withTrimmedBottom(getHeight() / 2).withTrimmedRight(925));
    canvas2.setBounds(getLocalBounds().withTrimmedLeft(325).withTrimmedTop(100).withTrimmedBottom(getHeight() / 2).withTrimmedRight(625));
    canvas3.setBounds(getLocalBounds().withTrimmedLeft(625).withTrimmedTop(100).withTrimmedBottom(getHeight() / 2).withTrimmedRight(325));
    canvas4.setBounds(getLocalBounds().withTrimmedLeft(925).withTrimmedTop(100).withTrimmedBottom(getHeight() / 2).withTrimmedRight(25));

    settings.setBounds(SETTINGS_SIZE.withSizeKeepingCentre(600, 220));
}

void WavetableLFO::buttonClicked(Button* button)
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
            isSetWave = true;
        }
    }
}

void WavetableLFO::addTimerListener(Slider::Listener* listener)
{
    settings.addRateListener(listener);
}

void WavetableLFO::removeTimerListener(Slider::Listener* listener)
{
    settings.removeRateListener(listener);
}

void WavetableLFO::timeCallback()
{
    updateKnobs(getNext());
  
}

void WavetableLFO::initSamples()
{
    // samples from canvas1 to canvas2
    // canvas 1 samples
    for (int i = 0; i < canvas1.waveTableSamples.size(); i++)
    {
        sampleY.add(canvas1.waveTableSamples[i]);
    }   

    // split waves between 1-2 && 2-3
    int semiWaves = settings.getWaveCount() / 2;

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
            //float y = (y1 + (x - x1) * (y2 - y1) / (x2 - x1));
            float y = (y1 + (x1 + 1 - x1) * (y2 - y1) / (x2 - x1));

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

bool WavetableLFO::isTimerSlider(Slider* slider)
{
    return settings.isRateSlider(slider);
}

bool WavetableLFO::isEmpty()
{
    return !isSetWave;
}

void WavetableLFO::calculateIncrement()
{
    increment = settings.getRate() * sampleY.size() / Utils::msToHz(TIMER_MS);
}

int WavetableLFO::getTimerHz() {
    return settings.getRate();
}

double WavetableLFO::getNext()
{

    finalSample = Utils::interpolateLinear(currentPosition, (int)currentPosition % sampleY.size(), ((int)currentPosition + 1) % sampleY.size(),
        sampleY[(int)currentPosition % sampleY.size()], sampleY[((int)currentPosition + 1) % sampleY.size()]) * 0.5f * settings.getDepth() + 0.5f;;

    currentPosition = fmod((currentPosition + increment), sampleY.size());
    return finalSample;
}
