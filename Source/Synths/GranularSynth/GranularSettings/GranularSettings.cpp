
#include <JuceHeader.h>
#include "GranularSettings.h"

GranularSettings::GranularSettings()
{
    addAndMakeVisible(openBufferButton);
    addAndMakeVisible(openAudioButton);
    addChildComponent(playerSelectNum);
    addChildComponent(playerCountNum);

    setBounds(0,0,1200,60);
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
  // DBG("TOPGranularSettings::paint");
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

    Utils::addToFb(&fb, openBufferButton, 0, 100, 48);
    Utils::addToFb(&fb, openAudioButton, 1, 100, 48);
    Utils::addToFb(&fb, playerCountNum, 2, 100, 48);
    Utils::addToFb(&fb, playerSelectNum, 3, 100, 48);

    fb.performLayout(getLocalBounds().withTrimmedLeft(250));
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

int GranularSettings::getPlayerCount()
{
    return playerCountNum.getValue();
}

void GranularSettings::setPlayerNum(float val)
{
    playerSelectNum.setValue(val, sendNotification);
}

