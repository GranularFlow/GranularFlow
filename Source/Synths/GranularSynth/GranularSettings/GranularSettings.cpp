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
    addAndMakeVisible(openBufferButton);
    addAndMakeVisible(openAudioButton);
    addChildComponent(playerSelectNum);
    addChildComponent(playerCountNum);
}

GranularSettings::~GranularSettings()
{
   
}

void GranularSettings::enablePlayers()
{
    // This prevents from creating players before file Load
    playerCountNum.setValue(1, sendNotification);
    playerCountNum.setRange(1, playerCountNum.getMaximum(), playerCountNum.getInterval());

    playerSelectNum.setValue(1, dontSendNotification);
    playerSelectNum.setRange(1, playerCountNum.getMaximum(), playerCountNum.getInterval());

    playerSelectNum.setVisible(true);
    playerCountNum.setVisible(true);
}

bool GranularSettings::isPlayerCountSlider(Slider* slider)
{
    return playerCountNum.isCurrentSlider(slider);
}

bool GranularSettings::isPlayerSelectSlider(Slider* slider)
{
    return playerSelectNum.isCurrentSlider(slider);
}

bool GranularSettings::isOpenAudioButton(Button* button)
{
    return  button == &openAudioButton;
}

bool GranularSettings::isOpenBufferButton(Button* button)
{
    return  button == &openBufferButton;
}

NumberSelect& GranularSettings::getPlayerCountNum()
{
    return playerCountNum;
}

NumberSelect& GranularSettings::getPlayerSelectNum()
{
    return playerSelectNum;
}

Button& GranularSettings::getOpenBufferButton()
{
    return openBufferButton;
}

Button& GranularSettings::getOpenAudioButton()
{
    return openAudioButton;
}

void GranularSettings::paint (Graphics& g)
{
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

    Utils::addToFb(&fb, openBufferButton, 0, 100, getHeight() * 0.8);
    Utils::addToFb(&fb, openAudioButton, 1, 100, getHeight() * 0.8);
    Utils::addToFb(&fb, playerCountNum, 2, 100, getHeight() * 0.8);
    Utils::addToFb(&fb, playerSelectNum, 3, 100, getHeight() * 0.8);

    fb.performLayout(getLocalBounds().withTrimmedLeft(IMAGE_WIDTH));
}

void GranularSettings::addButtonListener(Button::Listener* listener)
{
    openAudioButton.addListener(listener);
    openBufferButton.addListener(listener);
}

void GranularSettings::removeButtonListener(Button::Listener* listener)
{
    openAudioButton.removeListener(listener);
    openBufferButton.removeListener(listener);
}

void GranularSettings::addSliderListener(Slider::Listener* listener)
{
    playerSelectNum.addListener(listener);
    playerCountNum.addListener(listener);
}

void GranularSettings::removeSliderListener(Slider::Listener* listener)
{
    playerSelectNum.removeListener(listener);
    playerCountNum.removeListener(listener);
}

int8 GranularSettings::getPlayerCount()
{
    return playerCountNum.getValue();
}

