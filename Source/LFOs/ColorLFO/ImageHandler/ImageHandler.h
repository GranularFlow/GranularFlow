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
    struct ImageHandlerListener
    {
        virtual void imageLoaded() = 0;
    };
    void setListener(ImageHandlerListener* imageHandlerListenerIn) { imageHandlerListener = imageHandlerListenerIn; }
    void removeListener() { imageHandlerListener = nullptr; }

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
    void prepareToPlay(double);
    void sliderValueChanged(Slider*);

    // Getters
    float getRed(int, int);
    float getGreen(int, int);
    float getBlue(int, int);
    double getNext();

    // image
    int getImageHeight();
    int getImageWidth();

private:
    ImageHandlerListener* imageHandlerListener = nullptr;
    int currentX = 1;
    int currentY = 1;
    float sampleRate = 48000;
    float increment = 1;
    float phase = 0;

    std::unique_ptr<juce::FileChooser> fileChooser;
    Component::SafePointer<LfoSettings> settings;

    Image image;
    ColorDecomposer decomposer;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ImageHandler);
};
