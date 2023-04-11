#include "ImageHandler.h"

ImageHandler::ImageHandler()
{
    addAndMakeVisible(decomposer);
    setOpaque(true);
}

ImageHandler::~ImageHandler()
{
}

void ImageHandler::paint(Graphics& g)
{
    g.fillAll(C_DARK_GRAY);
    if (isImageSet())
    {
        g.drawImageWithin(image, 0, 10, (getWidth()/2) - 20, getHeight() - 20, juce::RectanglePlacement::centred);
        setBufferedToImage(true);
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
    fileChooser = std::make_unique<juce::FileChooser>("Select a png file...", juce::File{}, "*.png;*.jpg");

    fileChooser->launchAsync({}, [this](const FileChooser& fc) {
        setImage(fc.getResult());
        repaint();
    });

}

bool ImageHandler::isImageSet()
{
    return !image.isNull();
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

void ImageHandler::repaintCanvas() {
    decomposer.setRGB(
        image.getPixelAt(currentX, currentY).getRed(),
        image.getPixelAt(currentX, currentY).getGreen(),
        image.getPixelAt(currentX, currentY).getBlue()
    );
}

double ImageHandler::getNext()
{     
    if (direction == LfoSettings::RANDOM)
    {        
        currentX = random.nextInt((getWidth() / 2) - 20);
        currentY = random.nextInt(getHeight() - 20);
    }
    else if (direction == LfoSettings::FORWARD) {
        phase = abs(fmod(phase+0.1, 1.f));

        currentX = phase * getImageWidth();
        if (currentX == getImageWidth() - 1)
        {
            currentX = 0;
            currentY = (currentY + 1) % getImageHeight();
        }
    }
    else if (direction == LfoSettings::REVERSED) {
        phase -= 0.1f;
        phase = abs(fmod(phase + 1.f, 1.f));

        currentX = phase * getImageWidth();
        if (currentX == 0)
        {
            currentX = getImageWidth() - 1;
            currentY = (currentY - 1) % getImageHeight();
        }
    }

    
    if (color == LfoSettings::RED)
    {
        outputValue = getRed(currentX, currentY);
    }
    else if (color == LfoSettings::GREEN)
    {
        outputValue = getGreen(currentX, currentY);
    }
    else if (color == LfoSettings::BLUE)
    {
        outputValue = getBlue(currentX, currentY);
    }

    return outputValue;    
}

int ImageHandler::getImageHeight()
{
    return image.getHeight();
}

int ImageHandler::getImageWidth()
{
    return image.getWidth();
}

void ImageHandler::setDirection(LfoSettings::Direction directionIn)
{
    direction = directionIn;
}

void ImageHandler::setColor(LfoSettings::SelectedColor colorIn)
{
    color = colorIn;
}
