/*
  ==============================================================================

    GranularSettings.cpp
    Created: 18 Nov 2022 12:48:24pm
    Author:  honza

  ==============================================================================
*/

#include <JuceHeader.h>
#include "GranularSettings.h"

//==============================================================================
GranularSettings::GranularSettings()
{
    addComponents();
}

GranularSettings::~GranularSettings()
{
   
}

void GranularSettings::addComponents()
{
    addAndMakeVisible(openBufferButton);
    addAndMakeVisible(timeLengthNum);
    addAndMakeVisible(openAudioButton);
    addChildComponent(playerSelectNum);
    addChildComponent(playerCountNum);

    timeLengthNum.clearTop();
    playerSelectNum.clearTop();
    playerCountNum.clearTop();
}

void GranularSettings::enablePlayers()
{
    // This prevents from creating players before file Load
    playerCountNum.slider.setValue(1, sendNotification);
    playerCountNum.slider.setRange(1, playerCountNum.slider.getMaximum(), playerCountNum.slider.getInterval());

    playerSelectNum.slider.setValue(1, dontSendNotification);
    playerSelectNum.slider.setRange(1, playerCountNum.slider.getMaximum(), playerCountNum.slider.getInterval());
    playerSelectNum.setVisible(true);
    playerCountNum.setVisible(true);
}

void GranularSettings::paint (Graphics& g)
{
    //g.fillAll(C_WHITE);
}

void GranularSettings::resized()
{
    FlexBox fb{
           FlexBox::Direction::row,
           FlexBox::Wrap::noWrap,
           FlexBox::AlignContent::center,
           FlexBox::AlignItems::center,
           FlexBox::JustifyContent::flexEnd
    };

    Utils::addToFb(&fb, openBufferButton, 0, 100, getHeight());

    Utils::addToFb(&fb, openAudioButton, 1, 100, getHeight());

    Utils::addToFb(&fb, timeLengthNum, 2, 100, getHeight());
    Utils::addToFb(&fb, playerCountNum, 3, 100, getHeight());
    Utils::addToFb(&fb, playerSelectNum, 4, 100, getHeight());

    fb.performLayout(getLocalBounds().withTrimmedLeft(250));
}

