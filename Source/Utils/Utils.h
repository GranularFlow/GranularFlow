/*
  ==============================================================================

    Utils.h
    Created: 18 Nov 2022 2:08:09pm
    Author:  honza

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "../CustomComponents/CustomLooks/Separator.h"
#include "Constants.h"


class Utils
{
public:
	Utils();
	~Utils();
    // GUI
    static void paintLogo(Graphics&);
    static void paintLogoWithUnderline(Graphics&);
    // Tools
    static double degToRad(double);
    static float percentToFloat(int);
    static float samplesToPercent(int,int);
    static int msToSamples(float, int);
    static float samplesToMs(int, int);
    static int secToSamples(float, int);

    static void addToFb(FlexBox*, Component&, int, int, int);
    static void addToFb(FlexBox*, FlexBox, int, int, int);
    static void addToFb(FlexBox*, FlexItem, int, int, int);

    //Interpolations
    static double interpolateCubic(double x, double y0, double y1, double y2, double y3);
    static double interpolateLinear(double x, double x1, double x2, double y1, double y2);
    static double interpolateCubic(double x, Array<float>sampleY);
    static double interpolateHermite(double x, Array<float>sampleY);
    static double snapToStep(double, double, double, double);
private:

};