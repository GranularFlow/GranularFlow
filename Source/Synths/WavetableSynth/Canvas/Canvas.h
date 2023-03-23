#pragma once
#include <JuceHeader.h>
#include "../../../Utils/Constants.h"
#include "../../../Utils/Utils.h"
class Canvas : public Component
{
public:  
    // -----------------------
    // Class
    Canvas(String);
    ~Canvas();
    // -----------------------
    // GUI
    void paintPath(Graphics& g);
    void paint(Graphics& g) override;
    // -----------------------
    // Listeners
    void mouseDown(const MouseEvent& e) override;
    void mouseDrag(const MouseEvent& e) override;
    void mouseUp(const MouseEvent&) override;
    // -----------------------
    // Points
    float snapToClosestXPoint(float xValue);
    void addPoint(float newX, float newY);
    float interpolateY(float x, float x1, float y1, float x2, float y2);
    // -----------------------
    // Conversion
    void convertPointsToAmplitude();
    float yValueToAmplitude(float);
    // -----------------------
    // TODO
    Array<float> xPos;
    Array<float> yPos;
    Array<float> waveTableSamples;
    // -----------------------
    int waveTableIndex = 0;
    float sampleDistance = 2.5;
    String text;
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Canvas);

};