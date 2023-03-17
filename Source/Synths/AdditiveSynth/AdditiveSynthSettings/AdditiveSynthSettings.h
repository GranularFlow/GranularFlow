#pragma once
#include <JuceHeader.h>
#include "../../../Utils/Utils.h"
#include "../../../Utils/Constants.h"
#include "../../../CustomComponents/CustomLooks/Knob.h"
#include "../../../CustomComponents/CustomLooks/NumberSelect.h"

class AdditiveSynthSettings : public Component
{
public:
    // Class
	AdditiveSynthSettings();
	~AdditiveSynthSettings();
    // GUI
    void paint(Graphics&) override;
    void resized() override;
    // Listeners
    void addListener(Slider::Listener*);
    void removeListener(Slider::Listener*);
    // Tools
    bool isHarmonicCountSlider(Slider*);
    bool isHarmonicSelectSlider(Slider*);
    // Get
    NumberSelect& getHarmonicCount();
    NumberSelect& getHarmonicSelect();

private:
    NumberSelect harmonicCount { "Count", L_GREEN, 0, 5, 1, 0 };
    NumberSelect harmonicSelect { "Selected", L_ORANGE, 0, 5, 1, 0 };
};
