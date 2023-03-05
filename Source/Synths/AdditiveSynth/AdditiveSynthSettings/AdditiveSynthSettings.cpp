/*
  ==============================================================================

    AdditiveSettings.cpp
    Created: 1 Feb 2023 10:10:45pm
    Author:  honza

  ==============================================================================
*/
#include <JuceHeader.h>
#include "AdditiveSynthSettings.h"

AdditiveSynthSettings::AdditiveSynthSettings()
{
    addAndMakeVisible(harmonicCount);
    addAndMakeVisible(harmonicSelect);

    harmonicCount.slider.setValue(1, sendNotification);
    harmonicCount.slider.setRange(1, harmonicCount.slider.getMaximum(), harmonicCount.slider.getInterval());

    harmonicSelect.slider.setValue(1, dontSendNotification);
    harmonicSelect.slider.setRange(1, harmonicCount.slider.getMaximum(), harmonicCount.slider.getInterval());
}

AdditiveSynthSettings::~AdditiveSynthSettings()
{
}

void AdditiveSynthSettings::paint(Graphics& g)
{
    //g.fillAll(C_RADIANTYELLOW);
}

void AdditiveSynthSettings::resized()
{

    FlexBox fb{
            FlexBox::Direction::row,
            FlexBox::Wrap::noWrap,
            FlexBox::AlignContent::center,
            FlexBox::AlignItems::center,
            FlexBox::JustifyContent::flexEnd
    };

    Utils::addToFb(&fb, harmonicCount, 0, 100, getHeight());

    Utils::addToFb(&fb, harmonicSelect, 1, 100, getHeight());
    fb.performLayout(getLocalBounds().withTrimmedLeft(250));    
}
