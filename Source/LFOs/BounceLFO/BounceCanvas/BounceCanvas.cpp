/*
  ==============================================================================

    BounceCanvas.cpp
    Created: 16 Feb 2023 7:29:57pm
    Author:  honza

  ==============================================================================
*/

#include "BounceCanvas.h"


BounceCanvas::BounceCanvas()
{
    paintTiming.setListener(this);
    moveBallTiming.setListener(this);
    paintTiming.startTimerHz(33);
    moveBallTiming.startTimerHz(1);
}

BounceCanvas::~BounceCanvas()
{
    paintTiming.stopTimer();
    moveBallTiming.stopTimer();
    paintTiming.removeListener();
    moveBallTiming.removeListener();
}

void BounceCanvas::paint(Graphics& g)
{
    g.fillAll(C_GRAY);
    g.setColour(C_WHITE);
    g.fillRoundedRectangle(currentPosition.x - correctionPosition.x, currentPosition.y - correctionPosition.y, radius, radius, correctionPosition.x);

    g.setColour(C_WHITE);

    for (Path tmpPath: drawPaths)
    {
        g.strokePath(tmpPath, PathStrokeType(2.0f, PathStrokeType::JointStyle::curved, PathStrokeType::rounded));
    }

    g.setColour(C_ANDROID);

    g.fillRoundedRectangle(colision.x - 2.f, colision.y - 2.f, 4.f, 4.f, 2.f);
    
}

void BounceCanvas::setBallSpeed(int speed)
{
    moveBallTiming.stopTimer();
    moveBallTiming.startTimerHz(speed);
}

int BounceCanvas::getCoord(bool getX)
{
    return getX ? 0 : 1;
}

void BounceCanvas::timeCall(Timing* timing)
{
    if (timing == &moveBallTiming)
    {
        moveBall();
    }
    else if (timing == &paintTiming)
    {
        repaint();
    }
}

void BounceCanvas::mouseDown(const MouseEvent& e)
{

}

void BounceCanvas::mouseDrag(const MouseEvent& e)
{

    if (mousePositions.indexOf(e.position) == -1)
    {
        mousePositions.add(e.position);

    }
}

void BounceCanvas::mouseUp(const MouseEvent& e)
{
   
    Path tmpPath;

    tmpPath.startNewSubPath(mousePositions.getFirst().x, mousePositions.getFirst().y);

    for (Point<float> tmpPoint : mousePositions)
    {
        tmpPath.lineTo(tmpPoint);
    }

    drawPaths.add(tmpPath);

    mousePositions.clear();
}

void BounceCanvas::moveBall()
{

    auto nextPosition = currentPosition + positionVector;

    if (nextPosition.x < correctionPosition.x || nextPosition.x + correctionPosition.x > (float) getWidth())
    {
        positionVector.x = -positionVector.x;
        nextPosition.x = currentPosition.x + positionVector.x;
    }

    if (nextPosition.y < correctionPosition.y || nextPosition.y + correctionPosition.y > (float) getHeight())
    {
        positionVector.y = -positionVector.y;
        nextPosition.y = currentPosition.y + positionVector.y;
    }


    for (Path tmpPath : drawPaths)
    {
        Line<float> tmpNextPlus;
        Line<float> tmpNextMinus;

        // X
        tmpNextPlus = Line<float>(nextPosition, nextPosition + Point<float>(1.f, 0) + correctionPosition);
        tmpNextMinus = Line<float>(nextPosition, nextPosition - Point<float>(1.f, 0) - correctionPosition);

        if (tmpPath.intersectsLine(tmpNextPlus, 0) || tmpPath.intersectsLine(tmpNextMinus, 0))
        {
            colision = nextPosition;
            positionVector.x = -positionVector.x;
        }

        // Y
        tmpNextPlus = Line<float>(nextPosition, nextPosition + Point<float>(0, 1.f) + correctionPosition) ;
        tmpNextMinus = Line<float>(nextPosition, nextPosition - Point<float>(0, 1.f) - correctionPosition);

        if (tmpPath.intersectsLine(tmpNextPlus, 0) || tmpPath.intersectsLine(tmpNextMinus, 0))
        {
            colision = nextPosition;
            positionVector.y = -positionVector.y;

        }

    }
    currentPosition = nextPosition;
}

void BounceCanvas::clearLines()
{
    drawPaths.clear();
    mousePositions.clear();
}
