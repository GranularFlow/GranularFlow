/*
  ==============================================================================

    Wrapper.cpp
    Created: 21 Feb 2023 3:43:03pm
    Author:  honza

  ==============================================================================
*/

#include "GranularFlowWrapper.h"


GranularFlowWrapper::GranularFlowWrapper()
{
    //windows.add(new CustomWindow("testik", panel));
    addAndMakeVisible(waveSynthBox);
    addAndMakeVisible(granularSynthBox);
    addAndMakeVisible(additiveSynthBox);

}

GranularFlowWrapper::~GranularFlowWrapper()
{
    delete waveSynthBox;
    delete granularSynthBox;
    delete additiveSynthBox;
    closeWindows();
}

void GranularFlowWrapper::paint(Graphics&g)
{
    g.fillAll(C_DARK);

    float thickness = 10.f;
    int space = 30;
    int marginY = 127;

    int winWidth = 320;
    int winHeight = 210;

    int startY = marginY + winHeight * 0.8 ;

    int endY = W_HEIGHT * 5/6;
    int center = W_WIDTH/2;
    int circleRadius = 60;

    // Cables
    g.setColour(C_BARARED);

    Path curve;
    int startX = winWidth/2 + space;
    curve.startNewSubPath(startX, startY);
    curve.cubicTo(startX, startY, startX - 100, endY + 200, center - circleRadius, endY);

    Path curve2;
    startX = center;
    curve2.startNewSubPath(startX, startY);
    curve2.lineTo(startX, endY - circleRadius);

    Path curve3;
    startX = W_WIDTH - space - winWidth / 2;
    curve3.startNewSubPath(startX, startY);
    curve3.cubicTo(startX, startY, startX + 100, endY + 200, endY + circleRadius, endY);

    g.strokePath(curve, PathStrokeType(thickness));
    g.strokePath(curve2, PathStrokeType(thickness));
    g.strokePath(curve3, PathStrokeType(thickness));

    // Jacks
    g.setColour(L_GRAY);
    int jackWidht = 40;
    int jackHeight = 20;

    Rectangle<int> rectL(center - circleRadius - jackWidht + 7, endY - 6, jackWidht, jackHeight);
    Path pathL;
    pathL.addRectangle(rectL.toFloat());
    pathL.applyTransform(AffineTransform::rotation(-25.0 * MathConstants<double>::pi / 180.0, rectL.getCentre().toFloat().x, rectL.getCentre().toFloat().y));
    Rectangle<int> rectR(center + circleRadius - 7, endY, jackWidht, jackHeight);
    Path pathR;
    pathR.addRectangle(rectR.toFloat());
    pathR.applyTransform(AffineTransform::rotation(25.0 * MathConstants<double>::pi / 180.0, rectR.getCentre().toFloat().x, rectR.getCentre().toFloat().y));

    g.fillPath(pathL);
    g.fillPath(pathR);
    g.fillRect(center - jackHeight / 2, endY - circleRadius - jackWidht + 3, jackHeight, jackWidht);

    // Middle Circle
    g.setColour(C_WHITE);
    g.fillRoundedRectangle(center - circleRadius, endY - circleRadius, circleRadius*2, circleRadius*2, circleRadius);
}

void GranularFlowWrapper::resized()
{
    for (auto& window : windows)
    {
        window->setBounds(getLocalBounds().withSizeKeepingCentre(50,50));
    }
    waveSynthBox->setBounds(getLocalBounds().withSize(320, 210).withCentre(Point<int>(190, 212)));
    granularSynthBox->setBounds(getLocalBounds().withSize(320, 210).withCentre(Point<int>(600, 212)));
    additiveSynthBox->setBounds(getLocalBounds().withSize(320, 210).withCentre(Point<int>(1010, 212)));
}

void GranularFlowWrapper::closeWindows()
{
    for (auto& window : windows)
    {
        window.deleteAndZero();
    }
    windows.clear();
}
