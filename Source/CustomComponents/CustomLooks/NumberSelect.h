#pragma once
#include <JuceHeader.h>
#include "../../Utils/Constants.h"
#include "CustomLook.h"

class NumberSelect : public Component
{
public:
    // ----------------------
    // Class
	NumberSelect(String, Colour, int, int, int, int);
	~NumberSelect();
    // ----------------------
    // GUI
    void paint(Graphics&) override;
    void resized() override;
    // ----------------------
    // Listener
    void addListener(Slider::Listener*);
    void removeListener(Slider::Listener*);
    // ----------------------
    // Get
    double getValue();
    double getMaximum();
    double getMinimum();
    double getInterval();
    bool isCurrentSlider(Slider*);
    // ----------------------
    // Set
    void setValue(double, NotificationType);
    void setRange(double, double, double);
    // ----------------------    
private:
    CustomLook customLook;
    String name;
    Colour guiColor;
    // ----------------------   
    Slider slider{ Slider::SliderStyle::LinearHorizontal, Slider::TextEntryBoxPosition::TextBoxBelow };
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(NumberSelect);
};
