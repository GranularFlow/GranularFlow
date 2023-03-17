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

    Utils::addToFb(&fb, rateKnob, 1, 195, 191);
    Utils::addToFb(&fb, depthKnob, 3, 195, 191);
    Utils::addToFb(&fb, textEditor, 5, 300, 50);
    Utils::addToFb(&fb, enterButton, 7, 195, 50);

    for (int i = 0; i < 2; i++)
    {
        separators.add(new Separator());
        addAndMakeVisible(separators.getLast());
    }

    // White lines
    for (int i = 0; i < 2; i++)
    {
        fb.items.add(FlexItem(*separators[i]).withMinWidth(1).withHeight(191).withOrder((i + 1) * 2));
    }

    fb.performLayout(getLocalBounds());

}

void MathSettings::addRateListener(Slider::Listener* listener)
{
    rateKnob.addSliderListener(listener);
}

void MathSettings::removeRateListener(Slider::Listener* listener)
{
    rateKnob.removeSliderListener(listener);
}

void MathSettings::addEnterListener(Button::Listener* listener)
{
    enterButton.addListener(listener);
}

void MathSettings::removeEnterListener(Button::Listener* listener)
{
    enterButton.removeListener(listener);
}

void MathSettings::clickEnterButton()
{
    enterButton.triggerClick();
}

std::string MathSettings::getText()
{
    return textEditor.getText().toStdString();
}

int MathSettings::getRate()
{
    return rateKnob.getValue();
}

float MathSettings::getDepth()
{
    return depthKnob.getValue();
}

bool MathSettings::isRateSlider(Slider* slider)
{
    return rateKnob.isCurrentSlider(slider);
}

bool MathSettings::isDepthSlider(Slider* slider)
{
    return depthKnob.isCurrentSlider(slider);
}

bool MathSettings::isEnterButton(Button* button)
{
    return button == &enterButton;
}

