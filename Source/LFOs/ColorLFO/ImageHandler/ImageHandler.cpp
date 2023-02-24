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
    
    settings->rateKnob.removeListener(this);
    settings->depthKnob.removeListener(this);
    delete settings;
}

void ImageHandler::paint(Graphics& g)
{
    
    if (isImageSet())
    {
        g.drawImageWithin(image, 0, 10, (getWidth()/2) - 20, getHeight() - 20, juce::RectanglePlacement::centred);
    }

    g.setColour(M_T_LIGHT);

    Path p1;
    p1.startNewSubPath(Point<float>(currentX, 0));
    p1.lineTo(currentX, getHeight());
    g.strokePath(p1, PathStrokeType(1.f));

    Path p2;
    p2.startNewSubPath(Point<float>(0, currentY));
    p2.lineTo(getWidth(), currentY);
    g.strokePath(p2, PathStrokeType(1.f));    
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
    });

}

bool ImageHandler::isImageSet()
{
    return !image.isNull();
}

void ImageHandler::prepareToPlay(float sampleRateIn)
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

int ImageHandler::getRed(int x, int y)
{
    return image.getPixelAt(x, y).getRed();
}

int ImageHandler::getGreen(int x, int y)
{
    return image.getPixelAt(x, y).getGreen();
}

int ImageHandler::getBlue(int x, int y)
{
    return image.getPixelAt(x, y).getBlue();
}

void ImageHandler::getNext()
{
    if (!isImageSet()) {
        return ;
    }   

    // What direction to go for a pixel
    if (settings->isCurrentDirection(LfoSettings::RANDOM))
    {
        Random random;
        currentX = random.nextInt(getImageWidth());
        currentY = random.nextInt(getImageHeight());
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

    decomposer.setRGB(getRed(currentX, currentY), getGreen(currentX, currentY), getBlue(currentX, currentY));

    

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

    outputValue = (outputValue /(float)255) * (settings->getDepth() / (float)100);
}

int ImageHandler::getImageHeight()
{
    return image.getHeight();
}

int ImageHandler::getImageWidth()
{
    return image.getWidth();
}