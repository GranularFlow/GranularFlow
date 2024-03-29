#include "Knob.h"

Knob::Knob(String nameIn, Colour guiColorIn, float startRangIn, float endRangeIn, float stepIn, float defaultValueIn, bool displayLFO=true)
{

    guiColor = guiColorIn;
    name = nameIn;
    defaultValue = defaultValueIn;
    setLookAndFeel(&customLook);
    slider.setRange(startRangIn, endRangeIn, stepIn);
    slider.setValue(defaultValue, NotificationType::sendNotification);
    slider.setColour(Slider::ColourIds::rotarySliderFillColourId, guiColorIn);
    slider.setColour(Slider::ColourIds::thumbColourId, guiColorIn);
    slider.setColour(Slider::ColourIds::textBoxBackgroundColourId, Colour::fromRGBA(0, 0, 0, 0));
    slider.setColour(Slider::ColourIds::textBoxOutlineColourId, Colour::fromRGBA(0, 0, 0, 0));
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
    comboBox->setSelectedItemIndex(0, NotificationType::sendNotification);    

    setOpaque(true);
}

Knob::~Knob()
{    
    setLookAndFeel(nullptr);
    comboBox->setLookAndFeel(nullptr);
    removeKnobListener();
}

void Knob::paint(Graphics& g)
{
    g.fillAll(C_GRAY);
    g.setColour(guiColor);
    g.fillRect(Rectangle<float>(50, 10).withCentre(Point<float>(getWidth() / (float)2.0, 0)));
    g.setColour(Colours::white);
    g.drawText(name, getLocalBounds().withSize(getWidth(), 20).withCentre(Point<int>(getWidth() / 2, 20)), Justification::centred, false);       
}

void Knob::resized()
{    
    slider.setBounds(getLocalBounds().withSize(100, 120).withCentre(Point<int>(getWidth() / 2, 110)));
    comboBox->setBounds(getLocalBounds().withSize(getWidth() * 0.7, 25).withCentre(Point<int>(getWidth() / 2, getHeight() - 30 )));
}

void Knob::setValue(float value)
{
    slider.setValue(value);
}

void Knob::setDefaultValue()
{
    slider.setValue(defaultValue);
    comboBox->setSelectedItemIndex(0, NotificationType::sendNotification);
}


void Knob::addSliderListener(Slider::Listener* listener)
{
    slider.addListener(listener);
}

void Knob::removeSliderListener(Slider::Listener* listener)
{
    slider.removeListener(listener);
}

void Knob::comboBoxChanged(ComboBox* box)
{
    if (box == comboBox.get() && knobListenerPntr != nullptr)
    {
        if (box->getSelectedId() == 1)
        {
            if (lastSelectedLFO != 0 || lastSelectedLFO != 1)
            {
                knobListenerPntr->removeKnobFromLfo(this, lastSelectedLFO);
                lastSelectedLFO = 0;
                slider.setVisible(true);
            }
        }
        else
        {            
            knobListenerPntr->removeKnobFromLfo(this, lastSelectedLFO);
            knobListenerPntr->setKnobToLfo(this, box->getSelectedId());
            lastSelectedLFO = box->getSelectedId();
            slider.setVisible(false);
        }
    }
}

void Knob::setLfoValue(float value)
{
    // Formula is out = dry + lfoOut * depth
    slider.setValue(slider.getMaximum() * value);
}

float Knob::getValue()
{
    return slider.getValue();
}

bool Knob::isCurrentSlider(Slider* currentSlider)
{
    return currentSlider == &slider;
}

Slider& Knob::getSlider()
{
    return slider;
}
