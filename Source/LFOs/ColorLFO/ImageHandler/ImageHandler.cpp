/*
  ==============================================================================

    ImageHandler.cpp
    Created: 8 Feb 2023 6:28:33pm
    Author:  honza

  ==============================================================================
*/

#include "ImageHandler.h"

ImageHandler::ImageHandler(Component::SafePointer<LfoSettings> settingsIn)
{
    settings = settingsIn;
    addAndMakeVisible(decomposer);
    settings->rateKnob.addListener(this);
    settings->depthKnob.addListener(this);
}

ImageHandler::~ImageHandler()
{
    imageHandlerListener = nullptr;
    settings->rateKnob.removeListener(this);
    settings->depthKnob.removeListener(this);
}

void ImageHandler::paint(Graphics& g)
{
    if (isImageSet())
    {
        g.drawImageWithin(image, 0, 10, (getWidth()/2) - 20, getHeight() - 20, juce::RectanglePlacement::centred);
    }    
}

void ImageHandler::resized()
{
    decomposer.setBounds(getLocalBounds().withTrimmedRight(20).withTrimmedLeft(20 + getWidth()/2));    
}

void ImageHandler::setImage(File file)
{
    image = juce::ImageCache::getFromFile(juce::File(file.getFullPathName()));   
}

void ImageHandler::loadImage()
{
    fileChooser = std::make_unique<juce::FileChooser>("Select a png file...", juce::File{}, "*.png");

    fileChooser->launchAsync({}, [this](const FileChooser& fc) {
        setImage(fc.getResult());
        repaint();

        if (imageHandlerListener != nullptr)
        {
            imageHandlerListener->imageLoaded();
        }
    });

}

bool ImageHandler::isImageSet()
{
    return !image.isNull();
}

void ImageHandler::prepareToPlay(double sampleRateIn)
{
    sampleRate = sampleRateIn;
}

void ImageHandler::sliderValueChanged(Slider* slider)
{
    if (slider == &settings->rateKnob.slider)
    {
        increment = slider->getValue() / (float)sampleRate;
    }
}

float ImageHandler::getRed(int x, int y)
{
    return image.getPixelAt(x, y).getFloatRed();
}
    

float ImageHandler::getGreen(int x, int y)
{
    return image.getPixelAt(x, y).getFloatGreen();
}

float ImageHandler::getBlue(int x, int y)
{
    return image.getPixelAt(x, y).getFloatBlue();
}

double ImageHandler::getNext()
{     

    // What direction to go for a pixel
    if (settings->isCurrentDirection(LfoSettings::RANDOM))
    {
        Random random;
        currentX = random.nextInt((getWidth() / 2) - 20);
        currentY = random.nextInt(getHeight() - 20);
    }
    else if (settings->isCurrentDirection(LfoSettings::FORWARD)) {
        phase = abs(fmod(phase + increment, 1.f));

        currentX = phase * getImageWidth();
        if (currentX == getImageWidth() - 1)
        {
            currentX = 0;
            currentY = (currentY + 1) % getImageHeight();
        }
    }
    else if (settings->isCurrentDirection(LfoSettings::REVERSED)) {
        phase = abs(fmod(phase - increment, 1.f));

        currentX = phase * getImageWidth();
        if (currentX == 0)
        {
            currentX = getImageWidth() - 1;
            currentY = (currentY - 1) % getImageHeight();
        }
    }

    decomposer.setRGB(
        image.getPixelAt(currentX, currentY).getRed(),
        image.getPixelAt(currentX, currentY).getGreen(),
        image.getPixelAt(currentX, currentY).getBlue());

    double outputValue = 0;
    // What color to get
    if (settings->isCurrentSelectedColor(LfoSettings::RED))
    {
        outputValue = getRed(currentX, currentY);
    }
    else if (settings->isCurrentSelectedColor(LfoSettings::GREEN))
    {
        outputValue = getGreen(currentX, currentY);
    }
    else if (settings->isCurrentSelectedColor(LfoSettings::BLUE))
    {
        outputValue = getBlue(currentX, currentY);
    }

    return outputValue * settings->getDepth();
}

int ImageHandler::getImageHeight()
{
    return image.getHeight();
}

int ImageHandler::getImageWidth()
{
    return image.getWidth();
}