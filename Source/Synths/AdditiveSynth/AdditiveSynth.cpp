#include "AdditiveSynth.h"

AdditiveSynth::AdditiveSynth()
{
    addAndMakeVisible(settings);
    addAndMakeVisible(visualiser);
    settings.addListener(this);

    for (int i = 0; i < 5; i++)
    {
        harmonics.add(new AdditiveHarmonic());
        addAndMakeVisible(harmonics.getLast());
    }
    harmonics[0]->toFront(true);
    setOpaque(true);
}

AdditiveSynth::~AdditiveSynth()
{
    settings.removeListener(this);
    harmonics.clear();
}

void AdditiveSynth::paint(Graphics& g)
{
   // DBG("AdditiveSynth::paint");
    g.fillAll(Colour::fromRGB(33,33,33));
}

void AdditiveSynth::resized()
{
    settings.setBounds(getLocalBounds().withTrimmedBottom(getHeight() - 60));
    // Harmonics
    for (int i = 0; i < harmonics.size(); i++)
    {
        harmonics[i]->setBounds(SETTINGS_SIZE);
    }
    // AudioVisualiser
    visualiser.setBounds(getLocalBounds().withTrimmedTop(60).withTrimmedBottom(SETTINGS_SIZE.getHeight() + 40));
}

void AdditiveSynth::sliderValueChanged(Slider* slider)
{

    if (settings.isHarmonicCountSlider(slider))
    {
        int val = static_cast<int>(slider->getValue());

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

        int val = static_cast<int>(slider->getValue());

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
    harmonics[activeHarmonics]->setAngle(harmonics[0]->getAngle());
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

void AdditiveSynth::repaintVisualiser()
{
    visualiser.repaintCallBack();
}

void AdditiveSynth::processBlock(AudioBuffer<float>& bufferToFill, juce::MidiBuffer& midiMessages)
{
    for (int i = 0; i < activeHarmonics; i++)
    {
        harmonics[i]->processBlock(bufferToFill, midiMessages);
    }

    counterPush++;
    if (counterPush > 100)
    {
        visualiser.setWaveForm(bufferToFill);
        counterPush = 0;
    }
}

void AdditiveSynth::prepareToPlay(float sampleRate, int bufferSize)
{
    for (AdditiveHarmonic* harmonic : harmonics)
    {
        harmonic->prepareToPlay(sampleRate, bufferSize);
    }
}

void AdditiveSynth::setKnobsListener(Knob::Listener* knobListenerPntr)
{
    for (AdditiveHarmonic* harmonic : harmonics)
    {
        harmonic->setKnobsListener(knobListenerPntr);
    }
}

void AdditiveSynth::removeKnobsListener()
{
    // DO nothing pointer gets nulled at deconstructor
}
