/*
  ==============================================================================

    Utils.cpp
    Created: 18 Nov 2022 2:08:09pm
    Author:  honza

  ==============================================================================
*/

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
    g.drawImageAt(logo, (50 - 36) / 2, 7, false);
}

int Utils::msToSamples(float timeInMs, int sampleRate) {

    return Utils::secToSamples((timeInMs /(float) 1000), sampleRate);
}

float Utils::samplesToMs(int samplesCount, int sampleRate) {

    return (samplesCount /(float)sampleRate) * 1000;
}

int Utils::secToSamples(float timeInSec, int sampleRate) {
    int samples = std::round(sampleRate * timeInSec);
    return samples;
}

float Utils::percentToFloat(int8 percent)
{
    return (float)percent/100;
}

float Utils::samplesToPercent(int samplePosition, int totalSamples)
{
    return (samplePosition/(float) totalSamples) * 100.0;
}

void Utils::addToFb(FlexBox* fb, Component& c, int8 order, int minWidth,int minHeight) {
    fb->items.add(FlexItem(c).withMinWidth(minWidth).withMinHeight(minHeight).withMargin(0).withOrder(order));
}

void Utils::addToFb(FlexBox* fb, FlexBox f, int8 order, int minWidth, int minHeight) {
    fb->items.add(FlexItem(f).withMinWidth(minWidth).withMinHeight(minHeight).withMargin(0).withOrder(order));
}

void Utils::addToFb(FlexBox* fb, FlexItem i, int8 order, int minWidth, int minHeight) {
    fb->items.add(i.withMinWidth(minWidth).withMinHeight(minHeight).withMargin(0).withOrder(order));
}

double Utils::interpolateLinear(double x, double x1, double x2, double y1, double y2)
{
    if ((x2 - x1) == 0) {
        DBG("x2 " << x2 << " x1" << x1);
    }
    return y1 + ((x - x1) * ((y2 - y1) / (x2 - x1)));
}

double Utils::interpolateCubic(double x, Array<float>sampleY)
{
    int n = sampleY.size() - 1;
    int i = 0;

    // find the segment containing x
    while (i < n && x > i + 1)
        i++;

    // calculate the coefficients of the cubic polynomial for the segment
    double h = i + 1 - i;
    double t = (x - i) / h;
    double t2 = t * t;
    double t3 = t2 * t;
    double c0 = sampleY[i];
    double c1 = h * sampleY[i + 1] - h * sampleY[i];
    double c2 = -2 * h * sampleY[i + 1] + 2 * h * sampleY[i] + 3 * (sampleY[i + 1] - sampleY[i]);
    double c3 = 1 * h * sampleY[i + 1] - 1 * h * sampleY[i] - 2 * (sampleY[i + 1] - sampleY[i]);

    // evaluate the cubic polynomial at x
    double y = c0 + c1 * t + c2 * t2 + c3 * t3;
    /*
    DBG("x " << x);
    DBG("n " << n);
    DBG("h " << h);
    DBG("t " << t);
    DBG("t2 " << t2);
    DBG("t3 " << t3);
    DBG("c0 " << c0);
    DBG("c1 " << c1);
    DBG("c2 " << c2);
    DBG("c3 " << c3);

    DBG("i " << i);
    DBG("y " << y);*/
    return y;
}

double Utils::interpolateHermite(double wantedX, Array<float>sampleY)
{
    int n = sampleY.size();

    // Find the interval containing the wanted x
    int i = 0;
    while (i < n - 1 && wantedX > i + 1)
        i++;

    // Compute the tangents at the interval endpoints
    double m0, m1;
    if (i == 0) {
        m0 = (sampleY[1] - sampleY[0]) / (1);
        m1 = (sampleY[2] - sampleY[1]) / (1);
    }
    else if (i == n - 2) {
        m0 = (sampleY[n - 2] - sampleY[n - 3]) / ((n - 2) - (n - 3));
        m1 = (sampleY[n - 1] - sampleY[n - 2]) / ((n - 1) - (n - 2));
    }
    else {
        double t = (wantedX - i) / (i + 1 - i);
        double t2 = t * t;

        double h00 = 2 * t2 * t - 3 * t2 + 1;
        double h10 = t2 * t - 2 * t2 + t;
        double h01 = -2 * t2 * t + 3 * t2;
        double h11 = t2 * t - t2;

        m0 = (h00 * sampleY[i] + h10 * (i + 1 - i) * m0 + h01 * sampleY[i + 1] + h11 * (i + 1 - i) * m1) / (i + 1 - i);
        m1 = (h00 * sampleY[i + 1] + h10 * (i + 1 - i) * m0 + h01 * sampleY[i + 2] + h11 * (i + 2 - i + 1) * m1) / (i + 1 - i);
    }

    // Interpolate using the Hermite formula
    double t = (wantedX - i) / (i + 1 - i);
    double t2 = t * t;
    double t3 = t2 * t;

    double h00 = 2 * t3 - 3 * t2 + 1;
    double h10 = t3 - 2 * t2 + t;
    double h01 = -2 * t3 + 3 * t2;
    double h11 = t3 - t2;

    return h00 * sampleY[i] + h10 * (i + 1 - i) * m0 + h01 * sampleY[i + 1] + h11 * (i + 1 - i) * m1;
}