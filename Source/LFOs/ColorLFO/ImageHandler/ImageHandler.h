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

class ImageHandler : public Component, public Slider::Listener
{
public:
    // Class
	ImageHandler(Component::SafePointer<LfoSettings>);
	~ImageHandler();

    // GUI
    void paint(Graphics&)override;
    void resized()override;
    void setImage(File);
    void loadImage();
    bool isImageSet();

    // Listeners
    void prepareToPlay(float);
    void sliderValueChanged(Slider*);

    // Getters
    int getRed(int, int);
    int getGreen(int, int);
    int getBlue(int, int);
    void getNext();

    // image
    int getImageHeight();
    int getImageWidth();

private:
    float outputValue = 0;
    int currentX = 1;
    int currentY = 1;
    float sampleRate = 48000;
    float increment = 1;
    float phase = 0;

    std::unique_ptr<juce::FileChooser> fileChooser;
    LfoSettings* settings;

    Image image;
    ColorDecomposer decomposer;
};
