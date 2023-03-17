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
const int W_WIDTH = 1200;
const int W_HEIGHT = 700;
// -----------------------
// Timer
const int TIMER_MS = 2;
// -----------------------
// Component sizes
const int KNOB_WIDTH = 100;
const int KNOB_HEIGHT = 120;
const int TOP_BAR_HEIGHT = 60;
const int IMAGE_WIDTH = 250;
const juce::Rectangle<int> SETTINGS_SIZE = juce::Rectangle<int>().withSize(W_WIDTH-50,225).withCentre(Point<int>(W_WIDTH / 2, W_HEIGHT - 150));
const int CURSOR_BALL_RADIUS = 10;
// -----------------------
// Math
const double PI = 3.141592653589793238;
// -----------------------
// Font sizes
const float T_S_SIZE = 10.f;
const float T_M_SIZE = 12.f;
const float T_MH_SIZE = 14.f;
const float T_H_SIZE = 18.f;
// -----------------------
// BufferSize/Length for Synth
const int SAMPLE_RATE = 48000;
const int BUFFER_SAMPLES = 240000;
const int NUM_BUFFERS = 100;
// -----------------------
// GranularPlayer enumToString
const Array<String> INPUT_TYPE = { "BUFFER", "FILE" };
const Array<String> GRANULAR_MODE = {"ORDER", "REV.ORDER", "MIRROR", "REV.MIRROR"};
const Array<String> RUNNING_MODE = {"STATIC", "RUNNING"};
const Array<String> MIDI_MODE = {"OFF", "ON"};
const Array<String> WINDOW_TYPE = { "HALF SINE", "HANN", "TRIANGLE"};
const Array<String> INTERPOLATION_TYPE = { "LINEAR", "CUBIC", "HEARMITE" };
const Array<String> DIRECTION_MODE = { "RANDOM", "FORWARD", "REVERSED" };
const Array<String> SELECTED_COLOR = { "RED", "GREEN", "BLUE" };
const Array<String> COORDINATE = { "X", "Y" };
const Array<String> EQUATIONS = { "2pi", "triangle"};
// ----------------------------
// Colours for buttons and knobs
// ----------------------------
// Basic colours
const Colour C_WHITE = Colours::white;
const Colour C_SMOKE = Colours::whitesmoke;
const Colour C_DARK = Colour::fromRGB(33,33,33);
const Colour C_GRAY = Colour::fromRGB(40, 40, 40);
const Colour C_TRANSPARENT = Colour::fromRGBA(0, 0, 0, 0);
const Colour M_DARK = Colour::fromRGBA(0, 0, 0, 50);
const Colour M_LIGHT = Colour::fromRGBA(255, 255, 255, 50);
const Colour M_T_LIGHT = Colour::fromRGBA(255, 255, 255, 25);
const Colour VUT_COLOR = Colour::fromRGBA(229, 0, 43, 255);
// Light colours
const Colour L_GREEN = Colour::fromRGB(170, 212, 0);
const Colour L_AQUA = Colour::fromRGB(121, 186, 175);
const Colour L_RED = Colour::fromRGB(254, 85, 85);
const Colour L_ORANGE = Colour::fromRGB(242, 102, 38);
const Colour L_GRAY = Colour::fromRGB(50, 50, 50);
// Grey-filled colours
const Colour G_YELLOW = Colour::fromRGB(254, 177, 255);
const Colour G_DARK = Colour::fromRGB(45, 45, 45);
// Neon-like colours
const Colour N_MAGENTA = Colour::fromRGB(208, 70, 253);
const Colour N_AQUA = Colour::fromRGB(76, 240, 198);
const Colour N_YELLOW = Colour::fromRGB(254, 214, 36);
const Colour N_PINK = Colour::fromRGB(252, 56, 84);
// -----------------------
// PALETTE
// -----------------------
const Colour C_SUNFLOWER = Colour::fromRGB(255, 195, 18);
const Colour C_RADIANTYELLOW = Colour::fromRGB(247, 159, 31);
const Colour C_BILLS = Colour::fromRGB(238, 90, 36);
const Colour C_PIGMENT = Colour::fromRGB(234, 32, 39);
// -----------------------
const Colour C_ENERGOS = Colour::fromRGB(196, 229, 56);
const Colour C_ANDROID = Colour::fromRGB(163, 203, 56);
const Colour C_GRASS = Colour::fromRGB(0, 148, 50);
const Colour C_TURKISH_AQUA = Colour::fromRGB(52, 152, 219);
// -----------------------
const Colour C_MARTINA = Colour::fromRGB(18, 203, 196);
const Colour C_MEDITERRANEAN = Colour::fromRGB(18, 137, 167);
const Colour C_MARINE = Colour::fromRGB(0, 168, 255);
// -----------------------
const Colour C_LAVENDER_ROSE = Colour::fromRGB(253, 167, 223);
const Colour C_LAVENDER_TEA = Colour::fromRGB(217, 128, 250);
const Colour C_FORGOTEN = Colour::fromRGB(153, 128, 250);
const Colour C_CIRCUMMORBITAL = Colour::fromRGB(87, 88, 187);
// -----------------------
const Colour C_BARARED = Colour::fromRGB(237, 76, 103);
const Colour C_MAGENTA = Colour::fromRGB(111, 30, 81);
// -----------------------
const Colour C_VL_GRAY = Colour::fromRGB(118, 118, 118);
