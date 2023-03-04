/*
  ==============================================================================

    Window.cpp
    Created: 21 Feb 2023 3:50:16pm
    Author:  honza

  ==============================================================================
*/

#include "CustomWindow.h"

CustomWindow::CustomWindow(String windowName, Component* componentIn) : DocumentWindow(windowName,
    juce::Colours::lightgrey,
    DocumentWindow::minimiseButton){
    setContentOwned(componentIn, false);
    centreWithSize(W_WIDTH, W_HEIGHT);
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
