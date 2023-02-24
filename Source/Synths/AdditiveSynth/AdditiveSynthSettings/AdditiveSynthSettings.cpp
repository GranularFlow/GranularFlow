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
    addComponents();
}

AdditiveSynthSettings::~AdditiveSynthSettings()
{
}

void AdditiveSynthSettings::addComponents()
{
    addAndMakeVisible(harmonicCount);
    addAndMakeVisible(harmonicSelect);
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
