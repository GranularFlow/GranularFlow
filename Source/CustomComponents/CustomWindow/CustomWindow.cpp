/*
  ==============================================================================

    Window.cpp
    Created: 21 Feb 2023 3:50:16pm
    Author:  honza

  ==============================================================================
*/

#include "CustomWindow.h"

CustomWindow::CustomWindow(String windowName, Component::SafePointer<Component> c) : DocumentWindow(windowName,
    juce::Colours::lightgrey,
    DocumentWindow::minimiseButton)
{
    setContentOwned(c, false);
    //centreWithSize(W_WIDTH, W_HEIGHT);
}

CustomWindow::~CustomWindow()
{
}

void CustomWindow::closeButtonPressed()
{
    hideWindow();
}

void CustomWindow::showWindow()
{
    setVisible(true);
}

void CustomWindow::hideWindow()
{
    setVisible(false);
}
