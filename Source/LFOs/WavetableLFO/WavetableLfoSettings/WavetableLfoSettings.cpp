#include "WavetableLfoSettings.h"


WavetableLfoSettings::WavetableLfoSettings()
{
    addAndMakeVisible(depthKnob);
    addAndMakeVisible(rateKnob);
    addAndMakeVisible(waveCountKnob);

    for (int i = 0; i < 2; i++)
    {
        separators.add(new Separator());
        addAndMakeVisible(separators.getLast());
    }
    setOpaque(true);
}

WavetableLfoSettings::~WavetableLfoSettings()
{
}

void WavetableLfoSettings::paint(Graphics& g)
{
    g.fillAll(Colour::fromRGB(33, 33, 33));
    g.setColour(Colour::fromRGB(50, 50, 50));
    g.fillRoundedRectangle(getLocalBounds().toFloat(), 25);
}

void WavetableLfoSettings::resized()
{
    int sectionWidth = (getWidth() * 0.9) / 6;
    int sectionHeight = getHeight();

    FlexBox fb{
            FlexBox::Direction::row,
            FlexBox::Wrap::noWrap,
            FlexBox::AlignContent::center,
            FlexBox::AlignItems::flexStart,
            FlexBox::JustifyContent::spaceAround
    };

    // Second column
    int tmp_height = sectionHeight;
    Utils::addToFb(&fb, rateKnob, 1, 110, 225);
    Utils::addToFb(&fb, depthKnob, 3, 110, 225);
    Utils::addToFb(&fb, waveCountKnob, 5, 110, 225);

    // White lines
    for (int i = 0; i < separators.size(); i++)
    {
        Utils::addToFb(&fb, *separators[i], (i + 1) * 2, 1, 225);
    }

    fb.performLayout(getLocalBounds().withTrimmedLeft(15).withTrimmedRight(15));

}

void WavetableLfoSettings::addRateListener(Slider::Listener* listener)
{
    rateKnob.addSliderListener(listener);
}

void WavetableLfoSettings::removeRateListener(Slider::Listener* listener)
{
    rateKnob.removeSliderListener(listener);
}

void WavetableLfoSettings::addWaveCountListener(Slider::Listener* listener)
{
    waveCountKnob.addSliderListener(listener);
}

void WavetableLfoSettings::removeWaveCountListener(Slider::Listener* listener)
{
    waveCountKnob.removeSliderListener(listener);
}


double WavetableLfoSettings::getRate()
{
    return rateKnob.getValue();
}

double WavetableLfoSettings::getDepth()
{
    return depthKnob.getValue();
}

int WavetableLfoSettings::getWaveCount()
{
    return waveCountKnob.getValue();
}

bool WavetableLfoSettings::isWaveCountSlider(Slider* slider)
{
    return waveCountKnob.isCurrentSlider(slider);
}

bool WavetableLfoSettings::isRateSlider(Slider* slider)
{
    return rateKnob.isCurrentSlider(slider);
}
