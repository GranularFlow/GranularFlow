/*
  ==============================================================================

    Utils.h
    Created: 18 Nov 2022 2:08:09pm
    Author:  honza

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "Constants.h"


class Utils
{
public:
	Utils();
	~Utils();
    // GUI
    static void paintLogo(Graphics&);
    // Tools
    static float percentToFloat(int8);
    static float samplesToPercent(int,int);
    static int msToSamples(float, int);
    static float samplesToMs(int, int);
    static int secToSamples(float, int);
    static void addToFb(FlexBox*, Component&, int8, int, int);
    static void addToFb(FlexBox*, FlexBox, int8, int, int);
    static void addToFb(FlexBox*, FlexItem, int8, int, int);

private:

};