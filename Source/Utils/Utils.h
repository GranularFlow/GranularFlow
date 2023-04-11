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
    // -----------------------
    // GUI
    static void paintLogo(Graphics&);
    // --- Flex box
    static void addToFb(FlexBox*, Component&, int, int, int);
    static void addToFb(FlexBox*, FlexBox, int, int, int);
    static void addToFb(FlexBox*, FlexItem, int, int, int);
    // -----------------------
    // --- Math
    static double degToRad(double);
    // -----------------------
    // --- Samples
    static int msToSamples(float, int);
    static int secToSamples(float, int);
    // --- Time
    static float msToHz(float);
    static float hzToMs(float);
    static float msToS(double);
    // -----------------------
    //Interpolations
    static double interpolateCubic(double x, double y0, double y1, double y2, double y3);
    static double interpolateLinear(double x, double x1, double x2, double y1, double y2);
};