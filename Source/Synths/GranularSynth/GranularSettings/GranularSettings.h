#pragma once

#include <JuceHeader.h>
#include "../../../Utils/Constants.h"
#include "../../../Utils/Utils.h"
#include "../../../CustomComponents/CustomLooks/Knob.h"
#include "../../../CustomComponents/CustomLooks/RadioBox.h"
#include "../../../CustomComponents/CustomLooks/NumberSelect.h"

class GranularSettings : public Component
{
public:
    enum INPUT
    {
        BUFFER,
        FILE
    };
    // -----------------------
    // Class
    GranularSettings();
    ~GranularSettings();
    // -----------------------
    // GUI
    void paint(Graphics&) override;
    void resized();
    // -----------------------
    // Listeners
    // ---Buttons
    void addButtonListener(Button::Listener*);
    void removeButtonListener(Button::Listener*);
    // ---Sliders
    void addSliderListener(Slider::Listener*);
    void removeSliderListener(Slider::Listener*);
    // -----------------------
    // Get
    int getPlayerCount();
    int getSampleLength();
    // -----------------------
    // Set
    void setPlayerNum(float);
    // -----------------------
    // Tools
    void enablePlayers();
    bool isPlayerCountSlider(Slider*);
    bool isPlayerSelectSlider(Slider*);
    bool isLengthSlider(Slider*);
    bool isOpenAudioButton(Button*);
    bool isOpenBufferButton(Button*);
    // -----------------------
    Button& getOpenBufferButton();
    Button& getOpenAudioButton();

private:
    // -----------------------
    TextButton openBufferButton{ "BUFFER" };
    TextButton openAudioButton{ "FILE" };
    // -----------------------
    NumberSelect playerCountNum{ "Count", C_BARA_RED, 0, 3, 1, 0 };
    NumberSelect playerSelectNum{ "Select", C_PROTOSS_PYLON, 0, 3, 1, 0 };

    NumberSelect lengthNum{ "LENGTH", C_BARA_RED, 1000, 144000, 1, 144000 };

    // -----------------------
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GranularSettings)
};
