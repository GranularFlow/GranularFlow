/*
  ==============================================================================

    Constants.h
    Created: 17 Nov 2022 11:37:18am
    Author:  honza

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
// -----------------------
//        CONSTANTS
// -----------------------
// -----------------------
// Timer
const int TIMER_MS = 8;
// -----------------------
const int W_WIDTH = 1200;
const int W_HEIGHT = 700;


const int CANVAS_SAMPLES = 100;

const juce::Rectangle<int> SETTINGS_SIZE = juce::Rectangle<int>().withSize(1150, 225).withCentre(Point<int>(600, 550));
const juce::Rectangle<int> GRANULAR_PLAYER_SETTINGS_SIZE = SETTINGS_SIZE.withSize(SETTINGS_SIZE.getWidth(), SETTINGS_SIZE.getHeight() + 25).withCentre(Point<int>(SETTINGS_SIZE.getCentreX(), SETTINGS_SIZE.getCentreY() - 70));
const juce::Rectangle<int> BOUNCE_LFO_SETINGSS_SIZE = SETTINGS_SIZE.withSizeKeepingCentre(750, 200);
// COLOR
const juce::Colour C_WHITE = Colours::white;
const juce::Colour C_DARK_GRAY = Colour::fromRGB(33, 33, 33);
const juce::Colour C_DARKER_GRAY = Colour::fromRGB(40, 40, 40);
const juce::Colour C_GRAY = Colour::fromRGB(50, 50, 50);

const juce::Colour C_LIGTHER_GRAY = Colour::fromRGB(60, 60, 60);
const juce::Colour C_LIGTH_GRAY = Colour::fromRGB(118, 118, 118);

// Palette
const juce::Colour C_SUNFLOWER = Colour::fromRGB(255, 195, 18);
const juce::Colour C_RADIANT_YELLOW = Colour::fromRGB(247, 159, 31);
const juce::Colour C_PUFFINS_BILL = Colour::fromRGB(238, 90, 36);
const juce::Colour C_RED_PIGMENT = Colour::fromRGB(234, 32, 39);
//
const juce::Colour C_ENERGOS = Colour::fromRGB(196, 229, 56);

const juce::Colour C_ANDROID_GREEN = Colour::fromRGB(163, 203, 56);
//
const juce::Colour C_BLUE_MARTINA = Colour::fromRGB(18, 203, 196);
const juce::Colour C_MEDITERRANEAN_SEA = Colour::fromRGB(18, 137, 167);
//
const juce::Colour C_LAVENDER_ROSE = Colour::fromRGB(253, 167, 223);
//
const juce::Colour C_CIRCUMORBITAL_RING = Colour::fromRGB(87, 88, 187);
//
const juce::Colour C_BARA_RED = Colour::fromRGB(237, 76, 103);
//
const juce::Colour C_PROTOSS_PYLON = Colour::fromRGB(0, 168, 255);
//
const juce::Colour C_VANADYL_BLUE = Colour::fromRGB(52, 152, 219);


// -----------------------
// Math
const double PI = 3.141592653589793238f;