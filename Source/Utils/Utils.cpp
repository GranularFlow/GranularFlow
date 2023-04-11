#include "Utils.h"


void Utils::paintLogo(Graphics& g)
{
    const Image logo = ImageFileFormat::loadFrom(BinaryData::logo250_png, BinaryData::logo250_pngSize);
    g.drawImageAt(logo, 7, 7, false);
}

int Utils::msToSamples(float timeInMs, int sampleRate) {

    return Utils::secToSamples((timeInMs /(float) 1000), sampleRate);
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
    if (x2 - x1 == 0) {
        return 0;
    }
    return y1 + ( (x - x1) * ( (y2 - y1) / (x2 - x1)));
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
    /*    return  (y3 - y2 - y0 + y1) * (x * x * x)
            + (y0 - y1 - (y3 - y2 - y0 + y1) ) * (x * x)
            + (y2 - y0) * x 
            + y1;*/
    // fastest method
    return y1 + x *(-y0 + y2 + x *(2 * y0 - 2 *y1 + y2 - y3 + x *(-y0 + y1 - y2 + y3)));
}