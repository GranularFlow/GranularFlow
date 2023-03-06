/*
  ==============================================================================

    BounceCanvas.h
    Created: 16 Feb 2023 7:29:57pm
    Author:  honza

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "../../../Utils/Constants.h"
#include "../../../Utils/Timing/Timing.h"

class BounceCanvas : public Component, public Timing::TimingListener
{
public:
    // Class
	BounceCanvas();
	~BounceCanvas();
    // GUI
    void paint(Graphics&) override;
    // Setters
    void setBallSpeed(int);
    // Getters
    double getOutput(bool);    
    // Listeners
    void timeCall(Timing*)override;

    void mouseDrag(const MouseEvent& e) override;
    void mouseUp(const MouseEvent&) override;
    // Tools
    void startStop(int);
    void moveBall();
    void clearLines();


private:
    Timing moveBallTiming;
    Timing paintTiming;

    float radius = 20.f;
    bool wasDrawn = false;
    Array<Point<float>> mousePositions;
    Array<Path> drawPaths;
    
    Point<float> currentPosition = { 500.0, 200.0 };
    Point<float> positionVector = { 2.0, 2.0 };
    Point<float> colision = { 1.0, 1.0 };
    Point<float> correctionPosition = {10.f, 10.f};
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(BounceCanvas);
};
