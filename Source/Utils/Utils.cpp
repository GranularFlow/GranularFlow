#include "Utils.h"


Utils::Utils()
{
}

Utils::~Utils()
{
}

void Utils::paintLogo(Graphics& g)
{
    const Image logo = ImageFileFormat::loadFrom(BinaryData::logo250_png, BinaryData::logo250_pngSize);
    g.drawImageAt(logo, 7, 7, false);
}

void Utils::paintLogoWithUnderline(Graphics& g)
{
    paintLogo(g);
    g.setColour(C_GRAY);
    g.fillRect(0, TOP_BAR_HEIGHT - 2, W_WIDTH, 2);
}

int Utils::msToSamples(float timeInMs, int sampleRate) {

    return Utils::secToSamples((timeInMs /(float) 1000), sampleRate);
}

float Utils::samplesToMs(int samplesCount, int sampleRate) {

    return (samplesCount /(float)sampleRate) * 1000;
}

int Utils::secToSamples(float timeInSec, int sampleRate) {
    return std::round(sampleRate * timeInSec);
}

float Utils::msToHz(float ms)
{
    return 1000.f / ms;
}

float Utils::hzToMs(float hz)
{
    return 1000.f / hz;
}

float Utils::msToS(double ms)
{
    return ms / (float)1000;
}

double Utils::degToRad(double phase)
{
    return ((phase * PI) / (double)180);
}

float Utils::percentToFloat(int percent)
{
    return (float)percent / 100;
}

float Utils::samplesToPercent(int samplePosition, int totalSamples)
{
    return (samplePosition / (float)totalSamples) * 100.0;
}

void Utils::addToFb(FlexBox* fb, Component& c, int order, int minWidth,int minHeight) {
    Utils::addToFb(fb, FlexItem(c), order, minWidth, minHeight);
}

void Utils::addToFb(FlexBox* fb, FlexBox f, int order, int minWidth, int minHeight) {
    Utils::addToFb(fb, FlexItem(f), order, minWidth, minHeight);
}

void Utils::addToFb(FlexBox* fb, FlexItem i, int order, int minWidth, int minHeight) {
    fb->items.add(i.withMinWidth(minWidth).withMinHeight(minHeight).withMargin(0).withOrder(order));
}


double Utils::interpolateLinear(double x, double x1, double x2, double y1, double y2)
{
    return y1 + ( (x - x1) * ( (y2 - y1) / (x2 - x1)));
}

double Utils::interpolateCubic(double wantedX, Array<float>sampleY)
{
    int index = 0;
    while (index < sampleY.size() - 1 && wantedX > index)
        ++index;


    double y = Utils::interpolateCubic(wantedX - index, 
        sampleY[(index - 1 + sampleY.size()) % sampleY.size()],
        sampleY[(index + sampleY.size()) % sampleY.size()],
        sampleY[(index + 1 + sampleY.size()) % sampleY.size()],
        sampleY[(index + 2 + sampleY.size()) % sampleY.size()]
    );

    return y;
}

double Utils::interpolateCubic(double x, double y0, double y1, double y2, double y3)
{
    /*
        y = a0* x3 + a1 * x2 + a2 * x + a3;

        a0 = y3 - y2 - y0 + y1;
        a1 = y0 - y1 - a0;
        a2 = y2 - y0;
        a3 = y1;
    */
    //return y1 + 0.5 * x * (y2 - y0 + x * (2.0 * y0 - 5.0 * y1 + 4.0 * y2 - y3 + x * (3.0 * (y1 - y2) + y3 - y0)));
    return  (y3 - y2 - y0 + y1) * std::pow(x,3) 
            + (y0 - y1 - (y3 - y2 - y0 + y1) ) * std::pow(x, 2)
            + (y2 - y0) * x 
            + y1;
}

double Utils::interpolateHermite(double wantedX, Array<float>sampleY)
{
    // ---------------------------------------------------
    // This is Carmul-rom spline a type of hermite spline
    // ---------------------------------------------------

    // Find the interval containing the wanted x
    int i = 0;
    while (i < sampleY.size() - 1 && wantedX > i + 1)
        i++;
    // ---------------------------------------------------
    // Compute the tangents at the interval endpoints
    // ---------------------------------------------------

    // four basis blending functions
    // p(u) = | 2u^3 - 3u^2 + 1|
    //        |-2u^3 + 3u^2    |
    //        |  u^3 - 2u^2 + u|
    //        |  u^3 - u^2     |
    // Slopes
    // p = p0 * StartPoint + p1 * EndPoint + p3 * Tangent1 + p4 * Tangent2
    // in catmull Tangent = 0.5 * (EndPoint - StartPoint)
    //
    //

    // Slopes
    double m0 = 1;
    double m1 = 1;
    double u = wantedX - i;

    double p0 = 2 * pow(u, 3) - 3 * pow(u, 2) + 1;
    double p1 = pow(u, 3) - 2 * pow(u, 2) + u;
    double p2 = -2 * pow(u, 3) + 3 * pow(u, 2);
    double p3 = pow(u, 3) - pow(u, 2);

    if (i == 0) {
        // Case: wantedX is first interval
        m0 = (sampleY[1] - sampleY[0]);
        m1 = (sampleY[2] - sampleY[1]);
    }
    else if (i == sampleY.size() - 2) {
        // Case: wantedX is last interval
        m0 = sampleY[sampleY.size() - 2] - sampleY[sampleY.size() - 3];
        m1 = sampleY[sampleY.size() - 1] - sampleY[sampleY.size() - 2];
    }
    else {
        // Case: wantedX is between first and last interval
        

        m0 =  p0 * sampleY[i] 
            + p1 * m0 
            + p2 * sampleY[i + 1] 
            + p3 * m1;        
        
        
        m1 =  p0 * sampleY[i + 1] 
            + p1 * m0 
            + p2 * sampleY[i + 2] 
            + p3 * 3 * m1;
    }

    return p0 * sampleY[i] 
         + p1 * m0 
         + p2 * sampleY[i + 1] 
         + p3 * m1;

}

double Utils::snapToStep(double min, double max, double step, double value)
{
    double diff = value - min;
    double steps = round(diff / step);
    double snappedValue = min + steps * step;
    return std::min(max, std::max(min, snappedValue));
}