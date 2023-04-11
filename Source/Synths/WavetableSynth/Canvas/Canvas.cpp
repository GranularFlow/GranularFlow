#include "Canvas.h"

Canvas::Canvas(String textIn)
{
    text = textIn;
    setOpaque(true);
}

Canvas::~Canvas()
{
}

void Canvas::paintPath(Graphics& g)
{
    
    Path path;
    path.startNewSubPath(xPos.getFirst(), yPos.getFirst());
    for (int i = 1; i < xPos.size(); i++)
    {
        path.lineTo(xPos[i], yPos[i]);
    }
    g.setColour(C_WHITE);
    g.strokePath(path, PathStrokeType(2.0f, PathStrokeType::JointStyle::curved, PathStrokeType::rounded));
}

void Canvas::paint(Graphics& g)
{
    g.fillAll(C_GRAY);
    g.setColour(C_WHITE);
    g.drawText(text, getLocalBounds(), Justification::centredTop);

    paintPath(g);

    g.setColour(C_LIGTHER_GRAY);
    g.drawRect(getWidth()/2, 10, 1, getHeight());
    g.drawRect(0, getHeight()/2, getWidth(), 1);
}

void Canvas::mouseDrag(const MouseEvent& e)
{
    addPoint(e.x, e.y);
}

float Canvas::snapToClosestXPoint(float xValue)
{

    float absMin = fabs(xValue - (sampleDistance * 0));
    int closestPointIndex = 0;

    for (int i = 1; i < CANVAS_SAMPLES; i++)
    {
        float tmpAbs = fabs(xValue - (sampleDistance * i));
        if (tmpAbs < absMin) {
            absMin = fabs(xValue - (sampleDistance * i));
            closestPointIndex = i;
        }
    }

    return sampleDistance * closestPointIndex;
}

void Canvas::addPoint(float newX, float newY)
{

    // Filter out
    if (newX > getWidth() ||
        newX < 0 ||
        newY > getHeight() ||
        newY < 0 ||
        xPos.size() == CANVAS_SAMPLES) 
    {
        return;
    }

    // First value only
    if (xPos.size() == 0)
    {
        xPos.add(0);
        yPos.add(newY);
        return;
    }

    newX = snapToClosestXPoint(newX);

    // Check for X duplicate
    // Check mouse is moving forward only
    if (xPos.indexOf(newX) != -1) {

        return;
    }
    if (xPos.getLast() >= newX)
    {
        return;
    }

    // Check that every new element to be added did not skip previous X point
    // This prevents mouse skipping pixels 
    if (xPos.size() * sampleDistance != newX)
    {
        // create skipped value average from last one and current one => their position is counted from left top corner

        int lastIndex = xPos.indexOf(xPos.getLast());

        for (int i = lastIndex + 1; i < (newX / sampleDistance); i++)
        {
            //DBG("want to add x: " << i * sampleDistance << " y: " << newY);
            addPoint(i * sampleDistance, newY);
        }
        return;
    }

    // Finally add values after filtering
    xPos.add(newX);
    yPos.add(newY);   

    // Skip repainting if there are less than 2 points.
    if (xPos.size() >= 2) {
        repaint();
    }
}

void Canvas::mouseDown(const MouseEvent& e)
{
    // Clear X and Y points
    xPos.clear();
    yPos.clear();

    // Clear audio samples
    waveTableSamples.clear();

    addPoint(e.x, e.y);
}

float Canvas::interpolateY(float x, float x1, float y1, float x2, float y2)
{
    return(y1 + (x - x1) * (y2 - y1) / (x2 - x1));
}

void Canvas::mouseUp(const MouseEvent& e)
{    
    // Interpolate wavetable
    if (xPos.size() != CANVAS_SAMPLES)
    {
        //Has to be defined, because each loop xPos size is larger thus infinite loop
        int size = xPos.size();
        for (int i = 1; i <= (CANVAS_SAMPLES - size); i++)
        {
            addPoint(xPos.getLast() + sampleDistance,
                Utils::interpolateLinear(xPos.getLast() + sampleDistance, xPos.getLast(), getWidth(), yPos.getLast(), yPos.getLast()));
        }
    }
    convertPointsToAmplitude();
    setBufferedToImage(true);
}

void Canvas::convertPointsToAmplitude()
{
    // Somehow array set is reverted, but now its not ???
    for (int i = 0; i < yPos.size(); i++)
    {
        waveTableSamples.add(yValueToAmplitude(yPos[i]));
    }
}

float Canvas::yValueToAmplitude(float yVal)
{
    return jlimit(-1.f, 1.f, 1.f - ((2 * yVal) / getHeight()));
}
