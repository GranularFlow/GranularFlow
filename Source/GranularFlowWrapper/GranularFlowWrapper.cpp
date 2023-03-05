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
    // -----
    // GUI
    // -----
    // Separator
    addAndMakeVisible(topLine);
    // Reset SYNTH
    addAndMakeVisible(wavetableSynthReset);
    addAndMakeVisible(granularSynthReset);
    addAndMakeVisible(additiveSynthReset);
    // Synth squares
    addAndMakeVisible(wavetableSynthBox);
    addAndMakeVisible(granularSynthBox);
    addAndMakeVisible(additiveSynthBox);
    // Reset LFO
    addAndMakeVisible(colorLfoReset);
    addAndMakeVisible(bounceLfoReset);
    addAndMakeVisible(mathLfoReset);
    addAndMakeVisible(wavetableLfoReset);
    // Lfo squares
    addAndMakeVisible(colorLfoBox);
    addAndMakeVisible(bounceLfoBox);
    addAndMakeVisible(wavetableLfoBox);
    addAndMakeVisible(mathLfoBox);

    // Non visible process Synths  
    //SYNTH
    addChildComponent(wavetableSynth.get());
    addChildComponent(granularSynth.get());
    addChildComponent(additiveSynth.get());
    //LFO
    addChildComponent(colorLfo.get());
    addChildComponent(bounceLfo.get());
    //TODOaddChildComponent(mathLfo.get());
    addChildComponent(wavetableLfo.get());

    // -----
    // GUI WINDOWS
    // -----
    // add all components to separate windows
    // SYNTH
    synthWindows.add(new CustomWindow("Wavetable synth", wavetableSynth.get()));
    synthWindows.add(new CustomWindow("Granular synth", granularSynth.get()));
    synthWindows.add(new CustomWindow("Additive synth", additiveSynth.get()));
    // LFO
    lfoWindows.add(new CustomWindow("Color LFO", colorLfo.get()));
    lfoWindows.add(new CustomWindow("Bounce LFO", bounceLfo.get()));
    //TODOlfoWindows.add(new CustomWindow("Math LFO", mathLfo.get()));
    lfoWindows.add(new CustomWindow("Wavetable LFO", wavetableLfo.get()));

    // -----------------
    // IGNORE CLICKS
    // -----------------
    // Child ignores clicks and lets Wrapper take mouse events instead
    // Synth
    wavetableSynthBox->setInterceptsMouseClicks(false, false);
    granularSynthBox->setInterceptsMouseClicks(false, false);
    additiveSynthBox->setInterceptsMouseClicks(false, false);
    // Lfo
    colorLfoBox->setInterceptsMouseClicks(false, false);
    bounceLfoBox->setInterceptsMouseClicks(false, false);
    wavetableLfoBox->setInterceptsMouseClicks(false, false);
    mathLfoBox->setInterceptsMouseClicks(false, false);

    // -----------------
    // Listeners
    // -----------------
    // Reset buttons
    wavetableSynthReset.setListener(this);
    granularSynthReset.setListener(this);
    additiveSynthReset.setListener(this);

    colorLfoReset.setListener(this);
    bounceLfoReset.setListener(this);
    mathLfoReset.setListener(this);
    wavetableLfoReset.setListener(this);

    setAllKnobs();
}

GranularFlowWrapper::~GranularFlowWrapper()
{
    // -----------------
    // Listeners
    // -----------------
    // Reset buttons
    //SYNTH
    wavetableSynthReset.removeListener();
    granularSynthReset.removeListener();
    additiveSynthReset.removeListener();
    //LFO
    colorLfoReset.removeListener();
    bounceLfoReset.removeListener();
    mathLfoReset.removeListener();
    wavetableLfoReset.removeListener();
    
    // Delete synths that are inside boxes
    //SYNTH
    wavetableSynth.release();
    additiveSynth.release();
    granularSynth.release();
    //LFO
    colorLfo.release();
    bounceLfo.release();
    //TODOmathLfo.release();
    wavetableLfo.release();

    // Clean non-visible synths and lfos
    closeWindows();

    // clean boxes
    //SYNTH
    delete wavetableSynthBox;
    delete granularSynthBox;
    delete additiveSynthBox;
    //LFO
    delete colorLfoBox;
    delete bounceLfoBox;
    delete wavetableLfoBox;
    delete mathLfoBox;   
}

void GranularFlowWrapper::paintJacks(Graphics& g, int center, int circleRadius, int endY)
{
    g.setColour(C_VL_GRAY);
    int jackWidht = 40;
    int jackHeight = 25;

    juce::Rectangle<int> rectL(center - circleRadius - jackWidht + 7, endY - 8, jackWidht, jackHeight);
    Path pathL;
    pathL.addRectangle(rectL.toFloat());
    pathL.applyTransform(AffineTransform::rotation(-25.0 * MathConstants<double>::pi / 180.0, rectL.getCentre().toFloat().x, rectL.getCentre().toFloat().y));
    juce::Rectangle<int> rectR(center + circleRadius - 7, endY - 8, jackWidht, jackHeight);
    Path pathR;
    pathR.addRectangle(rectR.toFloat());
    pathR.applyTransform(AffineTransform::rotation(25.0 * MathConstants<double>::pi / 180.0, rectR.getCentre().toFloat().x, rectR.getCentre().toFloat().y));

    g.fillPath(pathL);
    g.fillPath(pathR);
    g.fillRect(center - jackHeight / 2, endY - circleRadius - jackWidht + 3, jackHeight, jackWidht);
}

void GranularFlowWrapper::paintCables(Graphics& g, int winWidth, int space, int startY, int endY, int center, int circleRadius)
{
    int startX = winWidth / 2 + space;
    cableWavetable.startNewSubPath(startX - 6, startY);
    cableWavetable.cubicTo(startX - 6, startY, startX - 100, endY + 200, center - circleRadius, endY + 6);
    cableWavetable.lineTo(center - circleRadius, endY - 6);
    cableWavetable.cubicTo(center - circleRadius, endY - 6, startX - 64, endY + 200, startX + 6, startY);
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

    if (processWavetable) { g.setColour(C_BARARED); }
    else { g.setColour(C_GRAY); }
    g.fillPath(cableWavetable);

    if (processGranular) { g.setColour(C_BARARED); }
    else { g.setColour(C_GRAY); }
    g.fillPath(cableGranular);

    if (processAdditive) { g.setColour(C_BARARED); }
    else { g.setColour(C_GRAY); }
    g.fillPath(cableAdditive);
}

void GranularFlowWrapper::paint(Graphics&g)
{
    g.fillAll(C_DARK);
    Utils::paintLogo(g);

    float thickness = 1;
    int space = 30;
    int marginY = 50;

    int winWidth = 320;
    int winHeight = 180;

    int startY = marginY + winHeight * 0.8 ;

    int endY = (W_HEIGHT * 2/(float)3) - 20;
    int center = W_WIDTH/2;
    int circleRadius = 60;

    // Cables
    paintCables(g, winWidth, space, startY, endY, center, circleRadius);
    // Jacks
    paintJacks(g, center, circleRadius, endY);

    // Middle Circle
    g.setColour(C_WHITE);
    g.fillRoundedRectangle(center - circleRadius, endY - circleRadius, circleRadius*2, circleRadius*2, circleRadius);


    // LFO Background
    g.setColour(L_GRAY);
    juce::Rectangle<float> lfoRect = getLocalBounds().withSize(820, 90).withCentre(Point<int>(getWidth() / 2, 640)).toFloat();
    g.drawRoundedRectangle(lfoRect, getHeight() * 0.01, 2);
}

void GranularFlowWrapper::resized()
{
    topLine.setBounds(getLocalBounds().withSize(getWidth(), 2).withCentre(Point<int>(W_WIDTH/2, 49)));
    // Synth non visible windows set bounds
    for (auto& window : synthWindows)
    {
        window->setBounds(getLocalBounds().withSizeKeepingCentre(W_WIDTH,W_HEIGHT));
    }

    for (auto& window : lfoWindows)
    {
        window->setBounds(getLocalBounds().withSizeKeepingCentre(W_WIDTH, W_HEIGHT));
    }

    // RESET SYNTH
    wavetableSynthReset.setBounds(getLocalBounds().withSize(30, 30).withCentre(Point<int>(190, 70)));
    granularSynthReset.setBounds(getLocalBounds().withSize(30, 30).withCentre(Point<int>(600, 70)));
    additiveSynthReset.setBounds(getLocalBounds().withSize(30, 30).withCentre(Point<int>(1010, 70)));
    // GUI SYNTH
    wavetableSynthBox->setBounds(getLocalBounds().withSize(320, 180).withCentre(Point<int>(190, 180)));
    granularSynthBox->setBounds(getLocalBounds().withSize(320, 180).withCentre(Point<int>(600, 180)));
    additiveSynthBox->setBounds(getLocalBounds().withSize(320, 180).withCentre(Point<int>(1010, 180)));
    
    int marginLeft = 190;
    int sectionWidth = 820 / 4;
    int centerSectionY = 640;
    int sectionHeight = 90;
    // RESET LFO
    colorLfoReset.setBounds(getLocalBounds().withSize(30, 30).withCentre(Point<int>(marginLeft + (sectionWidth/ (float)2), centerSectionY - (sectionHeight/2) - 20)));
    bounceLfoReset.setBounds(getLocalBounds().withSize(30, 30).withCentre(Point<int>(marginLeft + (sectionWidth * 3/ (float)2), centerSectionY - (sectionHeight / 2) - 20)));
    mathLfoReset.setBounds(getLocalBounds().withSize(30, 30).withCentre(Point<int>(marginLeft + (sectionWidth * 5/ (float)2), centerSectionY - (sectionHeight / 2) - 20)));
    wavetableLfoReset.setBounds(getLocalBounds().withSize(30, 30).withCentre(Point<int>(marginLeft + (sectionWidth * 7/ (float)2), centerSectionY - (sectionHeight / 2) - 20)));
    //GUI LFO
    colorLfoBox->setBounds(getLocalBounds().withSize(sectionWidth-20, 70).withCentre(Point<int>(marginLeft + (sectionWidth / (float)2), centerSectionY)));
    bounceLfoBox->setBounds(getLocalBounds().withSize(sectionWidth - 20, 70).withCentre(Point<int>(marginLeft + (sectionWidth * 3 / (float)2), centerSectionY)));
    mathLfoBox->setBounds(getLocalBounds().withSize(sectionWidth - 20, 70).withCentre(Point<int>(marginLeft + (sectionWidth * 5 / (float)2), centerSectionY)));
    wavetableLfoBox->setBounds(getLocalBounds().withSize(sectionWidth - 20, 70).withCentre(Point<int>(marginLeft + (sectionWidth * 7 / (float)2), centerSectionY)));
}

void GranularFlowWrapper::prepareToPlay(float sampleRate, int bufferSize)
{
    //TODOwavetableSynth->prepareToPlay(sampleRate, bufferSize);
    granularSynth->prepareToPlay(sampleRate, bufferSize);
    additiveSynth->prepareToPlay(sampleRate, bufferSize);
}

void GranularFlowWrapper::processBlock(AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    // as granularSynth can take buffer IN, it needs to process first
    if (processGranular)
    {
        granularSynth->processBlock(buffer, midiMessages);
    }

    if (processWavetable)
    {
        wavetableSynth->processBlock(buffer, midiMessages);
    }

    if (processAdditive)
    {
        additiveSynth->processBlock(buffer, midiMessages);
    }
}

void GranularFlowWrapper::reseted(ResetButton* button)
{
    if (button == &wavetableSynthReset && !processWavetable)
    {
        synthWindows[0].deleteAndZero();
        wavetableSynth.release();
        wavetableSynth = std::make_unique<WavetableSynth>();
        synthWindows.set(0, new CustomWindow("Wavetable synth", wavetableSynth.get()));
        repaint();
    }
    else if (button == &granularSynthReset && !processGranular)
    {
        synthWindows[1].deleteAndZero();
        granularSynth.release();
        granularSynth = std::make_unique<GranularSynth>();
        synthWindows.set(1, new CustomWindow("Granular synth", granularSynth.get()));
        repaint();
    }
    else if (button == &additiveSynthReset && !processAdditive)
    {
        synthWindows[2].deleteAndZero();
        additiveSynth.release();
        additiveSynth = std::make_unique<AdditiveSynth>();
        synthWindows.set(2, new CustomWindow("Additive synth", additiveSynth.get()));
        repaint();
    }

    if (button == &colorLfoReset)
    {
        lfoWindows[0].deleteAndZero();
        colorLfo.release();
        colorLfo = std::make_unique<ColorLFO>();
        lfoWindows.set(0, new CustomWindow("Color LFO", colorLfo.get()));
        repaint();
    }
    else if (button == &bounceLfoReset)
    {
        lfoWindows[1].deleteAndZero();
        bounceLfo.release();
        bounceLfo = std::make_unique<BounceLFO>();
        lfoWindows.set(1, new CustomWindow("Bounce LFO", bounceLfo.get()));
        repaint();
    }
    else if (button == &mathLfoReset)
    {
        lfoWindows[2].deleteAndZero();
        //TODOmathLfo.release();
        //TODOmathLfo = std::make_unique<MathLFO>();
        //TODOlfoWindows.set(2, new CustomWindow("Math LFO", mathLfo.get()));
        repaint();
    }
    else if (button == &wavetableLfoReset)
    {
        lfoWindows[3].deleteAndZero();
        wavetableLfo.release();
        wavetableLfo = std::make_unique<WavetableLFO>();
        lfoWindows.set(3, new CustomWindow("Wavetable LFO", wavetableLfo.get()));
        repaint();
    }

}

void GranularFlowWrapper::setLfoPointer(Knob* knobPntr, int lfoId)
{
    DBG("add pointerLFO" << lfoId);

    switch (lfoId)
    {
    case 2:
        colorLfo.get()->addKnobToListeners(knobPntr);
        break;
    case 3:
        //bounceLfo.get()->addKnobToListeners(knobPntr);
        break;
    case 4:
        //TODOmathLfo.get()->addKnobToListeners(knobPntr);
        break;
    case 5:
        //wavetableLfo.get()->addKnobToListeners(knobPntr);
        break;
    default:
        break;
    }
}

void GranularFlowWrapper::removeLfoPointer(Knob* knobPntr, int lfoId)
{
    DBG("remove pointerLFO" << lfoId);

    switch (lfoId)
    {
    case 2:
        colorLfo->removeKnobFromListeners(knobPntr);
        break;
    case 3:
        //bounceLfo.get()->addKnobToListeners(knobPntr);
        break;
    case 4:
        //TODOmathLfo.get()->addKnobToListeners(knobPntr);
        break;
    case 5:
        //wavetableLfo.get()->addKnobToListeners(knobPntr);
        break;
    default:
        break;
    }
}

void GranularFlowWrapper::closeWindows()
{
    for (auto& window : synthWindows)
    {
        window.deleteAndZero();
    }

    synthWindows.clear();

    for (auto& window : lfoWindows)
    {
        window.deleteAndZero();
    }

    lfoWindows.clear();
}

void GranularFlowWrapper::minimizeWindows()
{
    for (auto& window : synthWindows)
    {
        window->hideWindow();
    }

    for (auto& window : lfoWindows)
    {
        window->hideWindow();
    }
}

void GranularFlowWrapper::mouseDown(const MouseEvent& e)
{
    minimizeWindows();
    // SYNTH
    if (wavetableSynthBox->getBounds().contains(e.getPosition()))
    {        
        synthWindows[0]->showWindow();
        synthWindows[0]->toFront(true);
    }
    else if (granularSynthBox->getBounds().contains(e.getPosition()))
    {
        synthWindows[1]->showWindow();
        synthWindows[1]->toFront(true);
    }
    else if (additiveSynthBox->getBounds().contains(e.getPosition()))
    {
        synthWindows[2]->showWindow();
        synthWindows[2]->toFront(true);
    }
    // Cables
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
    // LFO
    if (colorLfoBox->getBounds().contains(e.getPosition()))
    {
        lfoWindows[0]->showWindow();
        lfoWindows[0]->toFront(true);
    }
    else if (bounceLfoBox->getBounds().contains(e.getPosition()))
    {
        lfoWindows[1]->showWindow();
        lfoWindows[1]->toFront(true);
    }
    else if (mathLfoBox->getBounds().contains(e.getPosition()))
    {
        lfoWindows[2]->showWindow();
        lfoWindows[2]->toFront(true);
    }
    else if (wavetableLfoBox->getBounds().contains(e.getPosition()))
    {
        lfoWindows[3]->showWindow();
        lfoWindows[3]->toFront(true);
    }
}

void GranularFlowWrapper::setAllKnobs()
{
    additiveSynth->setKnobsListener(this);
}
