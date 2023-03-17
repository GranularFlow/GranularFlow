#pragma once
#include <JuceHeader.h>
#include "../../../Utils/Constants.h"

class BounceCanvas : public Component
{
public:
    // ----------------------------------------
    // Class
	BounceCanvas();
	~BounceCanvas();
    // ----------------------------------------
    // GUI
    void paint(Graphics&) override; 
    // ----------------------------------------
    // Listeners
    void mouseDrag(const MouseEvent& e) override;
    void mouseUp(const MouseEvent&) override;
    // ----------------------------------------
    // Get
    double getOutput(bool);
    // ----------------------------------------
    // Tools
    void moveBall();
    void clearLines();
private:
    Array<Point<float>> mousePositions;
    Array<Path> drawPaths;
    // ----------------------------------------
    Point<float> currentPosition = { 500.0, 200.0 };
    Point<float> nextPosition = { 500.0, 200.0 };
    Point<float> positionVector = { 2.0, 2.0 };
    Point<float> colision = { 2.0, 2.0 };
    // ----------------------------------------
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(BounceCanvas);
};
