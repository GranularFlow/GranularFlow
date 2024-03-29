//
// Created by honza on 15. 11. 2022.
//
#include "RadioBox.h"

RadioBox::RadioBox(String nameIn, Colour guiColorIn, Array<String> elementsIn)
{
    setLookAndFeel(&customLook);

    name = nameIn;
    guiColor = guiColorIn;

    for (String element : elementsIn)
    {
        auto button = new ToggleButton(element);
        button->setRadioGroupId(1);
        button->setColour(ToggleButton::ColourIds::tickColourId, guiColorIn);
        button->addListener(this);
        addAndMakeVisible(button);
        toggleButtons.add(button);
    }
    toggleButtons[0]->setToggleState(true, true);

    setOpaque(true);
}

RadioBox::~RadioBox() {

    for (ToggleButton* button : toggleButtons)
    {
        button->removeListener(this);
    }

    setLookAndFeel(nullptr);
    toggleButtons.clear();
}

void RadioBox::paint(Graphics& g) {
    g.fillAll(C_GRAY);
    g.setColour(guiColor);
    g.fillRect((getWidth() / 4), 0, (getWidth() / 2), 5);

    g.setColour(Colours::white);
    g.drawFittedText(name, getLocalBounds().withTrimmedTop(10).withTrimmedRight(getWidth() * 0.05).withTrimmedLeft(getWidth() * 0.05), Justification::centredTop, 1);
}

void RadioBox::buttonStateChanged(Button* button)
{   //TODO
    /*const MessageManagerLock mmLock;
    repaint();*/
}

void RadioBox::buttonClicked(Button* button){
    for (int i = 0; i < toggleButtons.size(); ++i) {
        if (toggleButtons[i]->getToggleState()) {
            if (radioBoxListenerPntr != nullptr)
            {
                radioBoxListenerPntr->onValueChange(this, i);
            }
        }
    }
}


int RadioBox::getValue(){
    for (int i = 0; i < toggleButtons.size(); ++i) {
        if (toggleButtons[i]->getToggleState()) {
            return i;
        }
    }
    return -666;    
}

void RadioBox::resetDefaultValue()
{
    for (ToggleButton* button: toggleButtons) {
        button->setToggleState(false, NotificationType::sendNotification);
    }

    toggleButtons[0]->setToggleState(true, NotificationType::sendNotification);
}

void RadioBox::resized()
{
    FlexBox fb {
        FlexBox::Direction::column,
        FlexBox::Wrap::wrap,
        FlexBox::AlignContent::center,
        FlexBox::AlignItems::center,
        FlexBox::JustifyContent::center
    };

    for (ToggleButton* toggleButton : toggleButtons)
    {
        fb.items.add(juce::FlexItem(*toggleButton).withMinWidth(getWidth()*0.8).withHeight(20).withMaxHeight((getHeight() - 30) / toggleButtons.size()));
    }
    fb.performLayout(getLocalBounds().toFloat());
}