#include "BounceCanvas.h"


BounceCanvas::BounceCanvas()
{
}

BounceCanvas::~BounceCanvas()
{
}

void BounceCanvas::paint(Graphics& g)
{
    g.fillAll(C_GRAY);
    g.setColour(C_WHITE);
    g.fillRoundedRectangle(currentPosition.x - 10, currentPosition.y - 10, 20, 20, 10);

    g.setColour(C_WHITE);

    for (Path tmpPath: drawPaths)
    {
        g.strokePath(tmpPath, PathStrokeType(2.0f, PathStrokeType::JointStyle::curved, PathStrokeType::rounded));
    }

    // Green colision dot
    //g.setColour(C_ANDROID);
    //g.fillRect(colision.x - 2.f, colision.y - 2.f, 4.f, 4.f);   
}

double BounceCanvas::getOutput(bool getX)
{
    return getX ? (currentPosition.getX() / (double)getWidth()) : (currentPosition.getY() / (double)getHeight());
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
    repaint();
}

void BounceCanvas::moveBall()
{

    nextPosition = currentPosition + positionVector;

    // Walls
    if (nextPosition.x < 10 || nextPosition.x + 10 > (float) getWidth())
    {
        positionVector.x = -positionVector.x;
        nextPosition.x = currentPosition.x + positionVector.x;
    }
    if (nextPosition.y < 10 || nextPosition.y + 10 > (float) getHeight())
    {
        positionVector.y = -positionVector.y;
        nextPosition.y = currentPosition.y + positionVector.y;
    }


    for (Path tmpPath : drawPaths)
    {
        // X
        if (tmpPath.intersectsLine(Line<float>(nextPosition, nextPosition + Point<float>(11.f, 10)), 0) ||
            tmpPath.intersectsLine(Line<float>(nextPosition, nextPosition - Point<float>(11.f, 10)), 0))
        {
            colision = nextPosition;
            positionVector.x = -positionVector.x;
        }

        // Y
        if (tmpPath.intersectsLine(Line<float>(nextPosition, nextPosition + Point<float>(10, 11.f)), 0) ||
            tmpPath.intersectsLine(Line<float>(nextPosition, nextPosition - Point<float>(10, 11.f)), 0))
        {
            colision = nextPosition;
            positionVector.y = -positionVector.y;
        }
    }
    currentPosition = nextPosition;
    repaint();
}

void BounceCanvas::clearLines()
{
    drawPaths.clear();
    mousePositions.clear();
    repaint();
}
