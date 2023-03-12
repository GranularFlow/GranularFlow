/*
  ==============================================================================

    ImageHandler.h
    Created: 8 Feb 2023 6:28:33pm
    Author:  honza

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "../../../Utils/Constants.h"
#include "ColorDecomposer/ColorDecomposer.h"
#include "../LfoSettings/LfoSettings.h"

class ImageHandler : public Component
{
public:
    // Class
	ImageHandler();
	~ImageHandler();
    // GUI
    void paint(Graphics&)override;
    void resized()override;
    // Image
    void setImage(File);
    void loadImage();
    bool isImageSet();
    // Listeners
    // Getters
    float getRed(int, int);
    float getGreen(int, int);
    float getBlue(int, int);
    double getNext();
    int getImageHeight();
    int getImageWidth();

private:
    int currentX = 1;
    int currentY = 1;
    float phase = 0;

    std::unique_ptr<juce::FileChooser> fileChooser;

    Image image;
    ColorDecomposer decomposer;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ImageHandler);
};
