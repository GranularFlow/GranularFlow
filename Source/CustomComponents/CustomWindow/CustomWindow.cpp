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
