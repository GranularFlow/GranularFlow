#include "ColorLFO.h"


ColorLFO::ColorLFO()
{
    addAndMakeVisible(settings);    
    addAndMakeVisible(imageHandler);
    // Listeners
    settings.addDirectionListener(this);
    settings.addColorListener(this);
    settings.addButtonsListener(this);

    setOpaque(true);
}

ColorLFO::~ColorLFO()
{
    settings.removeDirectionListener();
    settings.removeColorListener();
    settings.removeButtonsListener(this);

}

void ColorLFO::paint(Graphics& g)
{
    g.fillAll(Colour::fromRGB(33,33,33));
    Utils::paintLogo(g);
}

void ColorLFO::resized()
{
    settings.setBounds(SETTINGS_SIZE.withSizeKeepingCentre(750,225));
    imageHandler.setBounds(getLocalBounds().withTrimmedTop(60).withTrimmedBottom(SETTINGS_SIZE.getHeight() + 40).withTrimmedLeft(20).withTrimmedRight(20));
}

void ColorLFO::buttonClicked(Button* button)
{
    if (settings.isUploadButton(button))
    {
        imageHandler.loadImage();
    }
}
void ColorLFO::timeCallback()
{
    updateKnobs(imageHandler.getNext() * settings.getDepth());
}

void ColorLFO::repaintCanvas()
{
    imageHandler.repaintCanvas();
}

bool ColorLFO::isTimerSlider(Slider* slider)
{
    return settings.isRateSlider(slider);
}


void ColorLFO::onValueChange(RadioBox* radioBox, int selectedButton)
{
    if (settings.isColourRadioBox(radioBox))
    {
        imageHandler.setColor((LfoSettings::SelectedColor)selectedButton);
    }
    if (settings.isDirectionRadioBox(radioBox))
    {
        imageHandler.setDirection((LfoSettings::Direction)selectedButton);
    }    
}

int ColorLFO::getTimerHz() {
    return settings.getRate();
}

bool ColorLFO::isImageSet()
{
    return imageHandler.isImageSet();
}

void ColorLFO::addTimerListener(Slider::Listener* listener) {
    settings.addRateListener(listener);
}

void ColorLFO::removeTimerListener(Slider::Listener* listener) {
    settings.removeRateListener(listener);
}