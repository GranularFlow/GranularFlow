#include <JuceHeader.h>
#include "AdditiveSynthSettings.h"

AdditiveSynthSettings::AdditiveSynthSettings()
{
    addAndMakeVisible(harmonicCount);
    addAndMakeVisible(harmonicSelect);

    harmonicCount.setValue(1, sendNotification);
    harmonicCount.setRange(1, harmonicCount.getMaximum(), harmonicCount.getInterval());

    harmonicSelect.setValue(1, dontSendNotification);
    harmonicSelect.setRange(1, harmonicCount.getMaximum(), harmonicCount.getInterval());

    setOpaque(true);
}

AdditiveSynthSettings::~AdditiveSynthSettings()
{
}

void AdditiveSynthSettings::paint(Graphics& g)
{
   // DBG("AdditiveSynthSettings::paint");
    g.fillAll(C_DARK_GRAY);
}

void AdditiveSynthSettings::resized()
{

    FlexBox fb{
            FlexBox::Direction::row,
            FlexBox::Wrap::noWrap,
            FlexBox::AlignContent::center,
            FlexBox::AlignItems::flexStart,
            FlexBox::JustifyContent::flexEnd
    };

    Utils::addToFb(&fb, harmonicCount, 0, 100, 48);
    Utils::addToFb(&fb, harmonicSelect, 1, 100, 48);

    fb.performLayout(getLocalBounds().withTrimmedLeft(250));    
}

void AdditiveSynthSettings::addListener(Slider::Listener* listener)
{
    harmonicCount.addListener(listener);
    harmonicSelect.addListener(listener);
}

void AdditiveSynthSettings::removeListener(Slider::Listener* listener)
{
    harmonicCount.removeListener(listener);
    harmonicSelect.removeListener(listener);
}

bool AdditiveSynthSettings::isHarmonicCountSlider(Slider* slider)
{
    return harmonicCount.isCurrentSlider(slider);
}

bool AdditiveSynthSettings::isHarmonicSelectSlider(Slider* slider)
{
    return harmonicSelect.isCurrentSlider(slider);
}

NumberSelect& AdditiveSynthSettings::getHarmonicCount()
{
    return harmonicCount;
}

NumberSelect& AdditiveSynthSettings::getHarmonicSelect()
{
    return harmonicSelect;
}
