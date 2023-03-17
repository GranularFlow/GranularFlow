#pragma once
#include <JuceHeader.h>
#include "../../../Utils/Constants.h"
class WavetableLfoCanvas : public Component
{
public:  
    // -----------------------
    // Class
    WavetableLfoCanvas(String);
    ~WavetableLfoCanvas();
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
    Array<float> xPos;
    Array<float> yPos;
    Array<float> waveTableSamples;
    // -----------------------
    //TODO
    int waveTableIndex = 0;
    const int waveTableSampleCount = 100;
    float sampleDistance = 2.5; // 250 / 100 samples
    String text;
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(WavetableLfoCanvas);
};