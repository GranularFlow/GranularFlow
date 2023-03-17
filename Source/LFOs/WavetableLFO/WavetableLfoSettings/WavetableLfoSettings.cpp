#include "WavetableLfoSettings.h"


WavetableLfoSettings::WavetableLfoSettings()
{
    addAndMakeVisible(depthKnob);
    addAndMakeVisible(rateKnob);
    addAndMakeVisible(waveCountKnob);
    addAndMakeVisible(incrementKnob);
}

WavetableLfoSettings::~WavetableLfoSettings()
{
}

void WavetableLfoSettings::paint(Graphics& g)
{
    g.setColour(L_GRAY);
    g.fillRoundedRectangle(getLocalBounds().toFloat(), 30);
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
    Utils::addToFb(&fb, incrementKnob, 7, 110, 225);

    // White lines
    for (int i = 0; i < 3; i++)
    {
        Utils::addToFb(&fb, *separators[i], (i + 1) * 2, 2, getWidth());
    }

    fb.performLayout(getLocalBounds());

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

double WavetableLfoSettings::getIncrement()
{
    return incrementKnob.getValue();
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
