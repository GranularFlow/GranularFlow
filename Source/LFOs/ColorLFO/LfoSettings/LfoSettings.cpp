#include "LfoSettings.h"

LfoSettings::LfoSettings()
{
    addAndMakeVisible(colorSelectRadioBox);
    addAndMakeVisible(directionRadioBox);
    addAndMakeVisible(depthKnob);
    addAndMakeVisible(rateKnob);
    addAndMakeVisible(uploadButton);

    for (int i = 0; i < 4; i++)
    {
        separators.add(new Separator());
        addAndMakeVisible(separators.getLast());
    }
    setOpaque(true);
}

LfoSettings::~LfoSettings()
{
    separators.clear();
}

void LfoSettings::paint(Graphics& g)
{
    g.fillAll(C_DARK_GRAY);
    g.setColour(C_GRAY);
    g.fillRoundedRectangle(getLocalBounds().toFloat(), 25);
}

void LfoSettings::resized()
{
    FlexBox fb{
            FlexBox::Direction::row,
            FlexBox::Wrap::noWrap,
            FlexBox::AlignContent::center,
            FlexBox::AlignItems::center,
            FlexBox::JustifyContent::spaceAround
    };
    
    //int tmpWidth = getWidth() * 1/5 * 0.85; //195
    //int tmpHeight = getHeight() * 0.85; //191
    Utils::addToFb(&fb, directionRadioBox, 1, 110, 191);
    Utils::addToFb(&fb, rateKnob, 3, 110, 191);
    Utils::addToFb(&fb, depthKnob, 5, 110, 191);
    Utils::addToFb(&fb, colorSelectRadioBox, 7, 110, 191);
    Utils::addToFb(&fb, uploadButton, 9, 80, 60);
    // White lines
    for (int i = 0; i < separators.size(); i++)
    {
        fb.items.add(FlexItem(*separators[i]).withMinWidth(1).withHeight(191).withOrder((i + 1) * 2));
    }
    fb.performLayout(getLocalBounds().withTrimmedLeft(15).withTrimmedRight(15));
}

void LfoSettings::addRateListener(Slider::Listener* listener)
{
    rateKnob.addSliderListener(listener);
}

void LfoSettings::removeRateListener(Slider::Listener* listener)
{
    rateKnob.removeSliderListener(listener);
}

void LfoSettings::addDirectionListener(RadioBox::Listener* listener)
{
    directionRadioBox.setListener(listener);
}

void LfoSettings::removeDirectionListener()
{
    directionRadioBox.removeListener();
}

void LfoSettings::addColorListener(RadioBox::Listener* listener)
{
    colorSelectRadioBox.setListener(listener);
}

void LfoSettings::removeColorListener()
{
    colorSelectRadioBox.removeListener();
}

void LfoSettings::addButtonsListener(Button::Listener* listener)
{
    uploadButton.addListener(listener);
}

void LfoSettings::removeButtonsListener(Button::Listener* listener)
{
    uploadButton.removeListener(listener);
}

bool LfoSettings::isUploadButton(Button* button)
{
    return button == &uploadButton;
}

bool LfoSettings::isRateSlider(Slider* slider)
{
    return rateKnob.isCurrentSlider(slider);
}

bool LfoSettings::isColourRadioBox(RadioBox* box)
{
    return box == &colorSelectRadioBox;
}

bool LfoSettings::isDirectionRadioBox(RadioBox* box)
{
    return box == &directionRadioBox;
}

float LfoSettings::getRate()
{
    return rateKnob.getValue();
}

float LfoSettings::getDepth()
{
    return depthKnob.getValue();
}
