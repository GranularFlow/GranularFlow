/*
  ==============================================================================

    MathSettings.cpp
    Created: 20 Feb 2023 9:02:07pm
    Author:  honza

  ==============================================================================
*/

#include "MathSettings.h"

MathSettings::MathSettings()
{
    addAndMakeVisible(rateKnob);
    addAndMakeVisible(depthKnob);
    addAndMakeVisible(textEditor);
    addAndMakeVisible(enterButton);

    textEditor.setJustification(Justification::horizontallyCentred);

    
}

MathSettings::~MathSettings()
{
}

void MathSettings::paint(Graphics& g)
{
    g.setColour(L_GRAY);
    g.fillRoundedRectangle(getLocalBounds().toFloat(), 30);
}

void MathSettings::resized()
{
    FlexBox fb{
            FlexBox::Direction::row,
            FlexBox::Wrap::noWrap,
            FlexBox::AlignContent::center,
            FlexBox::AlignItems::center,
            FlexBox::JustifyContent::spaceAround
    };

    int tmpWidth = getWidth() * 1 / 5 * 0.85;
    int tmpHeight = getHeight() * 0.85;

    Utils::addToFb(&fb, rateKnob, 1, tmpWidth, tmpHeight);
    Utils::addToFb(&fb, depthKnob, 3, tmpWidth, tmpHeight);
    Utils::addToFb(&fb, textEditor, 5, 300, 50);
    Utils::addToFb(&fb, enterButton, 7, tmpWidth, 50);

    for (int8 i = 0; i < 2; i++)
    {
        separators.add(new Separator());
        addAndMakeVisible(separators.getLast());
    }

    // White lines
    for (int8 i = 0; i < 2; i++)
    {
        fb.items.add(FlexItem(*separators[i]).withMinWidth(1).withHeight(tmpHeight).withOrder((i + 1) * 2));
    }

    fb.performLayout(getLocalBounds());

}

