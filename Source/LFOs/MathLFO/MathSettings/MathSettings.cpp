#include "MathSettings.h"

MathSettings::MathSettings()
{
    addAndMakeVisible(rateKnob);
    addAndMakeVisible(depthKnob);
    addAndMakeVisible(textEditor);
    addAndMakeVisible(enterButton);
    textEditor.setJustification(Justification::horizontallyCentred);
    setOpaque(true);
}

MathSettings::~MathSettings()
{
}

void MathSettings::paint(Graphics& g)
{
    g.fillAll(C_DARK_GRAY);
    g.setColour(C_GRAY);
    g.fillRoundedRectangle(getLocalBounds().toFloat(), 25);
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

    Utils::addToFb(&fb, rateKnob, 1, 110, 220);
    Utils::addToFb(&fb, depthKnob, 3, 110, 220);
    Utils::addToFb(&fb, textEditor, 5, 300, 60);
    Utils::addToFb(&fb, enterButton, 7, 80, 60);

    for (int i = 0; i < 2; i++)
    {
        separators.add(new Separator());
        addAndMakeVisible(separators.getLast());
    }

    // White lines
    for (int i = 0; i < separators.size(); i++)
    {
        Utils::addToFb(&fb, *separators[i], (i + 1) * 2, 1, 220);
    }

    fb.performLayout(getLocalBounds().withTrimmedLeft(15).withTrimmedRight(15));

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

