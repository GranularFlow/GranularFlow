/*
  ==============================================================================

    Wrapper.cpp
    Created: 21 Feb 2023 3:43:03pm
    Author:  honza

  ==============================================================================
*/

#include "GranularFlowWrapper.h"


GranularFlowWrapper::GranularFlowWrapper()
{
    // GUI
    addAndMakeVisible(wavetableSynthBox);
    addAndMakeVisible(granularSynthBox);
    addAndMakeVisible(additiveSynthBox);
    addAndMakeVisible(lfoPanel);

    // Synths
    addChildComponent(wavetableSynth);
    addChildComponent(granularSynth);
    addChildComponent(additiveSynth);

    // Child ignores clicks and lets Wrapper take mouse events instead
    wavetableSynthBox->setInterceptsMouseClicks(false, false);
    granularSynthBox->setInterceptsMouseClicks(false, false);
    additiveSynthBox->setInterceptsMouseClicks(false, false);

    // add all components to separate windows
    windows.add(new CustomWindow("Wavetable synth", wavetableSynth));
    windows.add(new CustomWindow("Granular synth", granularSynth));
    windows.add(new CustomWindow("Additive synth", additiveSynth));
}

GranularFlowWrapper::~GranularFlowWrapper()
{
    // GUI
    delete wavetableSynthBox;
    delete granularSynthBox;
    delete additiveSynthBox;

    // Synth
    delete wavetableSynth;

    closeWindows();
}

void GranularFlowWrapper::paint(Graphics&g)
{
    g.fillAll(C_DARK);

    float thickness = 1;
    int space = 30;
    int marginY = 127;

    int winWidth = 320;
    int winHeight = 210;

    int startY = marginY + winHeight * 0.8 ;

    int endY = W_HEIGHT * 2/3;
    int center = W_WIDTH/2;
    int circleRadius = 60;

    // Cables
      
    int startX = winWidth/2 + space;
    cableWavetable.startNewSubPath(startX - 6, startY);
    cableWavetable.cubicTo(startX-6, startY, startX - 100, endY + 200, center - circleRadius, endY + 6);
    cableWavetable.lineTo(center - circleRadius, endY - 6);
    cableWavetable.cubicTo(center - circleRadius, endY - 6, startX - 64, endY + 200 ,startX+6, startY);
    cableWavetable.closeSubPath(); 

    startX = center;
    cableGranular.startNewSubPath(startX - 6, startY);
    cableGranular.lineTo(startX - 6, endY - circleRadius);
    cableGranular.lineTo(startX + 6, endY - circleRadius);
    cableGranular.lineTo(startX + 6, startY);
    cableGranular.closeSubPath();
    
    startX = W_WIDTH - space - winWidth / 2;
    cableAdditive.startNewSubPath(startX + 6, startY);
    cableAdditive.cubicTo(startX + 6, startY, startX + 100, endY + 200, center + circleRadius, endY + 6);
    cableAdditive.lineTo(center + circleRadius, endY - 6);
    cableAdditive.cubicTo(center + circleRadius, endY - 6, startX + 64, endY + 200, startX - 6, startY);
    cableAdditive.closeSubPath();
    
    if (processWavetable) { g.setColour(C_BARARED); } else { g.setColour(C_GRAY); }
    g.fillPath(cableWavetable);

    if (processGranular) { g.setColour(C_BARARED); } else { g.setColour(C_GRAY); }
    g.fillPath(cableGranular);

    if (processAdditive) { g.setColour(C_BARARED); } else { g.setColour(C_GRAY); }
    g.fillPath(cableAdditive);

    // Jacks
    g.setColour(C_VL_GRAY);
    int jackWidht = 40;
    int jackHeight = 25;

    Rectangle<int> rectL(center - circleRadius - jackWidht + 7, endY - 8, jackWidht, jackHeight);
    Path pathL;
    pathL.addRectangle(rectL.toFloat());
    pathL.applyTransform(AffineTransform::rotation(-25.0 * MathConstants<double>::pi / 180.0, rectL.getCentre().toFloat().x, rectL.getCentre().toFloat().y));
    Rectangle<int> rectR(center + circleRadius - 7, endY - 8, jackWidht, jackHeight);
    Path pathR;
    pathR.addRectangle(rectR.toFloat());
    pathR.applyTransform(AffineTransform::rotation(25.0 * MathConstants<double>::pi / 180.0, rectR.getCentre().toFloat().x, rectR.getCentre().toFloat().y));

    g.fillPath(pathL);
    g.fillPath(pathR);
    g.fillRect(center - jackHeight / 2, endY - circleRadius - jackWidht + 3, jackHeight, jackWidht);

    // Middle Circle
    g.setColour(C_WHITE);
    g.fillRoundedRectangle(center - circleRadius, endY - circleRadius, circleRadius*2, circleRadius*2, circleRadius);


    // LFOS
    g.setColour(L_GRAY);
    Rectangle<float> lfoRect = getLocalBounds().withSize(820, 90).withCentre(Point<int>(getWidth() / 2,(getHeight() * (2 / 3)) + 163)).toFloat();
    g.fillRoundedRectangle(lfoRect, getHeight() * 0.01);
}

void GranularFlowWrapper::resized()
{
    for (auto& window : windows)
    {
        window->setBounds(getLocalBounds().withSizeKeepingCentre(W_WIDTH,W_HEIGHT));
    }
    wavetableSynthBox->setBounds(getLocalBounds().withSize(320, 210).withCentre(Point<int>(190, 212)));
    granularSynthBox->setBounds(getLocalBounds().withSize(320, 210).withCentre(Point<int>(600, 212)));
    additiveSynthBox->setBounds(getLocalBounds().withSize(320, 210).withCentre(Point<int>(1010, 212)));
    
    FlexBox fb{
            FlexBox::Direction::row,
            FlexBox::Wrap::noWrap,
            FlexBox::AlignContent::center,
            FlexBox::AlignItems::center,
            FlexBox::JustifyContent::spaceAround
    };

    Utils::addToFb(&fb, harmonicCount, 0, 800 / 4, getHeight());
    fb.performLayout(getLocalBounds().withSize(820, 90).withCentre(Point<int>(getWidth() / 2, (getHeight() * (2 / 3)) + 163)).toFloat());
}

void GranularFlowWrapper::prepareToPlay(float sampleRate)
{
}

void GranularFlowWrapper::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
}

void GranularFlowWrapper::closeWindows()
{
    for (auto& window : windows)
    {
        window.deleteAndZero();
    }
    windows.clear();
}

void GranularFlowWrapper::minimizeWindows()
{
    for (auto& window : windows)
    {
        window->hideWindow();
    }
}

void GranularFlowWrapper::mouseDown(const MouseEvent& e)
{

    if (wavetableSynthBox->getBounds().contains(e.getPosition()))
    {
        minimizeWindows();
        windows[0]->showWindow();
        windows[0]->toFront(true);
    }
    else if (granularSynthBox->getBounds().contains(e.getPosition()))
    {
        minimizeWindows();
        windows[1]->showWindow();
        windows[1]->toFront(true);
    }
    else if (additiveSynthBox->getBounds().contains(e.getPosition()))
    {
        minimizeWindows();
        windows[2]->showWindow();
        windows[2]->toFront(true);
    }

    if (cableWavetable.contains(e.getPosition().toFloat(), 20.f))
    {
        processWavetable = !processWavetable;
        repaint();
    }
    else if (cableGranular.contains(e.getPosition().toFloat(), 20.f))
    {
        processGranular = !processGranular;
        repaint();
    }
    else if (cableAdditive.contains(e.getPosition().toFloat(), 20.f))
    {
        processAdditive = !processAdditive;
        repaint();
    }
}
