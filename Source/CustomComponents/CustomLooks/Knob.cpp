/*
  ==============================================================================

    Knob.cpp
    Created: 16 Nov 2022 1:43:43am
    Author:  honza

  ==============================================================================
*/

#include "Knob.h"

Knob::Knob(String nameIn, Colour guiColorIn, float startRangIn, float endRangeIn, float stepIn, float defaultValue, bool displayLFO=true)
{

    guiColor = guiColorIn;
    name = nameIn;
    value = defaultValue;

    setLookAndFeel(&customLook);
    slider.setRange(startRangIn, endRangeIn, stepIn);
    slider.setValue(defaultValue, NotificationType::sendNotification);
    slider.setColour(Slider::ColourIds::rotarySliderFillColourId, guiColorIn);
    slider.setColour(Slider::ColourIds::thumbColourId, guiColorIn);
    slider.setColour(Slider::ColourIds::textBoxBackgroundColourId, C_TRANSPARENT);
    slider.setColour(Slider::ColourIds::textBoxOutlineColourId, C_TRANSPARENT);

    addAndMakeVisible(slider);
    comboBox.reset(new ComboBox());

    if (displayLFO)
    {       
        addAndMakeVisible(comboBox.get());
    }

    comboBox->setLookAndFeel(&customLook);
    comboBox->addItem("--", 1);
    comboBox->addItem("Color", 2);
    comboBox->addItem("Bounce", 3);
    comboBox->addItem("Math", 4);
    comboBox->addItem("Wavetable", 5);

    comboBox->addListener(this);
    comboBox->setSelectedItemIndex(0, NotificationType::dontSendNotification);    
}

Knob::~Knob()
{
    knobListenerPntr = nullptr;
    setLookAndFeel(nullptr);
    comboBox->setLookAndFeel(nullptr);
}

void Knob::paint(Graphics& g)
{
    g.setColour(guiColor);
    g.fillRect(Rectangle<float>(50, 10).withCentre(Point<float>(getWidth()/(float)2.0, 0)));

    g.setColour(C_SMOKE);
    g.drawFittedText(name, getLocalBounds().withTrimmedTop(10).withTrimmedRight(getWidth() * 0.1).withTrimmedLeft(getWidth() * 0.1), Justification::centredTop, 1);
}

void Knob::resized()
{
    slider.setBounds(
        getLocalBounds()
        .withTrimmedTop(25)
        .withTrimmedBottom(50)
        .withTrimmedLeft(getWidth()* 0.15)
        .withTrimmedRight(getWidth() * 0.15)
    );

    comboBox->setBounds(
        getLocalBounds()
        .withTrimmedTop(getHeight()-50)
        .withTrimmedBottom(25)
        .withTrimmedLeft(getWidth() * 0.15)
        .withTrimmedRight(getWidth() * 0.15)
    );
}


void Knob::addListener(Slider::Listener* listener)
{
    slider.addListener(listener);
}

void Knob::removeListener(Slider::Listener* listener)
{
    slider.removeListener(listener);
}

void Knob::comboBoxChanged(ComboBox* box)
{
    if (box == comboBox.get() && knobListenerPntr != nullptr)
    {
        if (box->getSelectedId() == 1)
        {
            knobListenerPntr->removeLfoPointer(this, lastSelectedLFO);
            lastSelectedLFO = 0;
        }
        else
        {
            knobListenerPntr->removeLfoPointer(this, lastSelectedLFO);
            knobListenerPntr->setLfoPointer(this, box->getSelectedId());
            lastSelectedLFO = box->getSelectedId();
        }
    }
}

void Knob::setLfoValue(float value)
{
    // Formula is out = dry + lfoOut * depth
    slider.setValue(Utils::snapToStep(slider.getMinimum(), slider.getMaximum(), slider.getInterval(), slider.getMaximum() * value));
    repaint();
}

float Knob::getValue()
{
    return slider.getValue();
}
