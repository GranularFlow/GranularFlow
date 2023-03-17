#include "NumberSelect.h"

NumberSelect::NumberSelect(String nameIn, Colour guiColorIn, int startRangeIn, int endRangeIn, int stepIn, int initialValue)
{
    setLookAndFeel(&customLook);

    guiColor = guiColorIn;
    name = nameIn;
    // Number selector
    slider.setValue(initialValue);
    slider.setRange(startRangeIn, endRangeIn, stepIn);
    slider.setTextBoxStyle(Slider::TextBoxBelow, true, 60, 10);
    slider.setColour(Slider::ColourIds::trackColourId, guiColorIn);
    slider.setColour(Slider::ColourIds::thumbColourId, guiColorIn);
    slider.setColour(Slider::ColourIds::textBoxOutlineColourId, C_TRANSPARENT); 
    slider.setColour(Slider::ColourIds::textBoxTextColourId, C_WHITE);
    // Visibility
    addAndMakeVisible(slider);    
}

NumberSelect::~NumberSelect() {
    setLookAndFeel(nullptr);
}

double NumberSelect::getValue()
{
    return slider.getValue();
}

double NumberSelect::getMaximum()
{
    return slider.getMaximum();
}

double NumberSelect::getMinimum()
{
    return slider.getMinimum();
}

double NumberSelect::getInterval()
{
    return slider.getInterval();
}

void NumberSelect::setValue(double newValue, NotificationType notification = NotificationType::sendNotification)
{
    slider.setValue(newValue, notification);
}

void NumberSelect::setRange(double newMin, double newMax, double newInt)
{
    slider.setRange(newMin, newMax, newInt);
}

void NumberSelect::addListener(Slider::Listener* listener)
{
    slider.addListener(listener);
}

void NumberSelect::removeListener(Slider::Listener* listener)
{
    slider.removeListener(listener);
}

bool NumberSelect::isCurrentSlider(Slider* currentSlider)
{
    return currentSlider == &slider;
}

void NumberSelect::paint(Graphics& g) {
    // Top colour
    g.setColour(guiColor);
    g.fillRect((getWidth() / 2) / 2, 0, (getWidth() / 2), 2);
    // Text
    g.setColour(C_SMOKE);
    g.drawText(name, getLocalBounds().withSize(getWidth() * 0.8, getHeight() * 1/3).withCentre(Point<int>(getWidth()/2, getHeight()* 1/6)), Justification::centred, 1);
    
}

void NumberSelect::resized() {
    // SLIDER
    slider.setBounds(getLocalBounds().withSize(getWidth() * 0.8, getHeight() * 2/3).withCentre(Point<int>(getWidth()/2, getHeight() * 2/3)));
}