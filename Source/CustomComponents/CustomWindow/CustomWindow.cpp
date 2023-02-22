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
    DocumentWindow::closeButton)
{
    setContentOwned(c, false);
    centreWithSize(W_WIDTH, W_HEIGHT);
    setVisible(true);
}

CustomWindow::~CustomWindow()
{
}

void CustomWindow::close()
{
    setContentOwned(nullptr, false);
    delete this;
}

void CustomWindow::closeButtonPressed()
{
    delete this;
}