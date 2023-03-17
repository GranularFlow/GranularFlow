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
    initGui();
    addAllListeners();
    makeWindowsIgnoreClicks();
    startTimer(TIMER_MS);
}

GranularFlowWrapper::~GranularFlowWrapper()
{
    removeThisFromAllListeners();
    
    // Delete synths that are inside boxes
    //SYNTH
    wavetableSynth.release();
    additiveSynth.release();
    granularSynth.release();
    //LFO
    colorLfo.release();
    bounceLfo.release();
    mathLfo.release();
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
    pathL.applyTransform(AffineTransform::rotation(-30.0 * MathConstants<double>::pi / 180.0, rectL.getCentre().toFloat().x, rectL.getCentre().toFloat().y));
    juce::Rectangle<int> rectR(center + circleRadius - 7, endY - 8, jackWidht, jackHeight);
    Path pathR;
    pathR.addRectangle(rectR.toFloat());
    pathR.applyTransform(AffineTransform::rotation(30.0 * MathConstants<double>::pi / 180.0, rectR.getCentre().toFloat().x, rectR.getCentre().toFloat().y));

    g.fillPath(pathL);
    g.fillPath(pathR);
    g.fillRect(center - jackHeight / 2, endY - circleRadius - jackWidht + 3-20, jackHeight, jackWidht);
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

    //ValueType initialX, ValueType initialY,ValueType width, ValueType height

    cableColorLfo = juce::Rectangle<float>(278, 540, 30.f, 30.f);
    cableBounceLfo = juce::Rectangle<float>(484, 540, 30.f, 30.f);
    cableMathLfo = juce::Rectangle<float>(690, 540, 30.f, 30.f);
    cableWavetableLfo = juce::Rectangle<float>(896 , 540, 30.f, 30.f);

    //550 az 625

    Colour colorOn = C_ANDROID;

    if (processWavetable) { g.setColour(colorOn); }
    else { g.setColour(C_GRAY); }
    g.fillPath(cableWavetable);

    if (processGranular) { g.setColour(colorOn); }
    else { g.setColour(C_GRAY); }
    g.fillPath(cableGranular);

    if (processAdditive) { g.setColour(colorOn); }
    else { g.setColour(C_GRAY); }
    g.fillPath(cableAdditive);

    if (processColorLfo) { g.setColour(colorOn); }
    else { g.setColour(C_GRAY); }
    g.fillRoundedRectangle(cableColorLfo, cableColorLfo.getHeight()/2.f);

    if (processBounceLfo) { g.setColour(colorOn); }
    else { g.setColour(C_GRAY); }
    g.fillRoundedRectangle(cableBounceLfo, cableBounceLfo.getHeight() / 2.f);

    if (processMathLfo) { g.setColour(colorOn); }
    else { g.setColour(C_GRAY); }
    g.fillRoundedRectangle(cableMathLfo, cableMathLfo.getHeight() / 2.f);

    if (processWavetableLfo) { g.setColour(colorOn); }
    else { g.setColour(C_GRAY); }
    g.fillRoundedRectangle(cableWavetableLfo, cableWavetableLfo.getHeight() / 2.f);
}

void GranularFlowWrapper::paint(Graphics&g)
{
    g.fillAll(C_DARK);
    Utils::paintLogo(g);

    float thickness = 1;
    int space = 30;
    int marginY = 60;

    int winWidth = 320;
    int winHeight = 180;

    int startY = marginY + winHeight;

    int endY = (W_HEIGHT * 2/(float)3) - 20;
    int center = W_WIDTH/2;
    int circleRadius = 60;

    // Cables
    paintCables(g, winWidth, space, startY, endY + 20, center, circleRadius);
    // Jacks
    paintJacks(g, center, circleRadius, endY+20);
    // Middle Circle
    g.setColour(L_GRAY);
    g.fillRoundedRectangle(center - circleRadius, endY - circleRadius, circleRadius * 2, circleRadius * 2, circleRadius);

    const Image tLogo = ImageFileFormat::loadFrom(BinaryData::wave_png, BinaryData::wave_pngSize);
    g.drawImageWithin(tLogo, center - 30, endY - 30, circleRadius, circleRadius, RectanglePlacement::centred, false);

    // LFO Background
    g.setColour(L_GRAY);
    juce::Rectangle<float> lfoRect = getLocalBounds().withSize(820, 155).withCentre(Point<int>(getWidth() / 2, 615)).toFloat();
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
    wavetableSynthReset.setBounds(getLocalBounds().withSize(40, 40).withCentre(Point<int>(190, 110)));
    granularSynthReset.setBounds(getLocalBounds().withSize(40, 40).withCentre(Point<int>(600, 110)));
    additiveSynthReset.setBounds(getLocalBounds().withSize(40, 40).withCentre(Point<int>(1010, 110)));
    // GUI SYNTH
    wavetableSynthBox->setBounds(getLocalBounds().withSize(320, 180).withCentre(Point<int>(190, 180)));
    granularSynthBox->setBounds(getLocalBounds().withSize(320, 180).withCentre(Point<int>(600, 180)));
    additiveSynthBox->setBounds(getLocalBounds().withSize(320, 180).withCentre(Point<int>(1010, 180)));

    // RESET LFO
    colorLfoReset.setBounds(getLocalBounds().withSize(30, 30).withCentre(Point<int>(292, 595)));
    bounceLfoReset.setBounds(getLocalBounds().withSize(30, 30).withCentre(Point<int>(498, 595)));
    mathLfoReset.setBounds(getLocalBounds().withSize(30, 30).withCentre(Point<int>(704, 595)));
    wavetableLfoReset.setBounds(getLocalBounds().withSize(30, 30).withCentre(Point<int>(910, 595)));
    //GUI LFO
    colorLfoBox->setBounds(getLocalBounds().withSize(185, 105).withCentre(Point<int>(292, 630)));
    bounceLfoBox->setBounds(getLocalBounds().withSize(185, 105).withCentre(Point<int>(498, 630)));
    mathLfoBox->setBounds(getLocalBounds().withSize(185, 105).withCentre(Point<int>(704, 630)));
    wavetableLfoBox->setBounds(getLocalBounds().withSize(185, 105).withCentre(Point<int>(910, 630)));
}

void GranularFlowWrapper::prepareToPlay(float sampleRate, int bufferSize)
{
    wavetableSynth->prepareToPlay(sampleRate, bufferSize);
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

void GranularFlowWrapper::sliderValueChanged(Slider* slider)
{
    if (colorLfo->isTimerSlider(slider))
    {
        colorLfoTimer = 0;
    }
    else if (bounceLfo->isTimerSlider(slider))
    {
        bounceLfoTimer = 0;
    }
    else if (mathLfo->isTimerSlider(slider))
    {
        mathLfoTimer = 0;
    }
    else if (wavetableLfo->isTimerSlider(slider))
    {
        wavetableLfoTimer = 0;
    }
    else if (bounceLfo->isBallSpeedSlider(slider))
    {
        bounceBallSpeed = slider->getValue();
        bounceBallTimer = 0;
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

    if (button == &colorLfoReset && colorLfo->knobPntrsEmpty() && !processColorLfo)
    {
        lfoWindows[0].deleteAndZero();
        colorLfo.release();
        colorLfo = std::make_unique<ColorLFO>();
        lfoWindows.set(0, new CustomWindow("Color LFO", colorLfo.get()));
        repaint();
    }
    else if (button == &bounceLfoReset && bounceLfo->knobPntrsEmpty() && !processBounceLfo)
    {
        lfoWindows[1].deleteAndZero();
        bounceLfo.release();
        bounceLfo = std::make_unique<BounceLFO>();
        lfoWindows.set(1, new CustomWindow("Bounce LFO", bounceLfo.get()));
        repaint();
    }
    else if (button == &mathLfoReset && mathLfo->knobPntrsEmpty() && !processMathLfo)
    {
        lfoWindows[2].deleteAndZero();
        mathLfo.release();
        mathLfo = std::make_unique<MathLFO>();
        lfoWindows.set(2, new CustomWindow("Math LFO", mathLfo.get()));
        repaint();
    }
    else if (button == &wavetableLfoReset && wavetableLfo->knobPntrsEmpty() && !processWavetableLfo)
    {
        lfoWindows[3].deleteAndZero();
        wavetableLfo.release();
        wavetableLfo = std::make_unique<WavetableLFO>();
        lfoWindows.set(3, new CustomWindow("Wavetable LFO", wavetableLfo.get()));
        repaint();
    }

}

void GranularFlowWrapper::setKnobToLfo(Knob* knobPntr, int lfoId)
{
    switch (lfoId)
    {
    case 2:
        colorLfo->addKnobToListeners(knobPntr);
        break;
    case 3:
        bounceLfo->addKnobToListeners(knobPntr);
        break;
    case 4:
        mathLfo->addKnobToListeners(knobPntr);
        break;
    case 5:
        wavetableLfo->addKnobToListeners(knobPntr);
        break;
    default:
        break;
    }
}

void GranularFlowWrapper::removeKnobFromLfo(Knob* knobPntr, int lfoId)
{
    switch (lfoId)
    {
    case 2:
        colorLfo->removeKnobFromListeners(knobPntr);
        break;
    case 3:
        bounceLfo->removeKnobFromListeners(knobPntr);
        break;
    case 4:
        mathLfo->removeKnobFromListeners(knobPntr);
        break;
    case 5:
        wavetableLfo->removeKnobFromListeners(knobPntr);
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
    else if (cableColorLfo.contains(e.getPosition().toFloat()) && !colorLfoBox->getBounds().contains(e.getPosition()))
    {
        processColorLfo = !processColorLfo;
        repaint();
    }
    else if (cableBounceLfo.contains(e.getPosition().toFloat()) && !bounceLfoBox->getBounds().contains(e.getPosition()))
    {
        processBounceLfo = !processBounceLfo;
        repaint();
    }
    else if (cableMathLfo.contains(e.getPosition().toFloat()) && !mathLfoBox->getBounds().contains(e.getPosition()))
    {
        processMathLfo = !processMathLfo;
        repaint();
    }
    else if (cableWavetableLfo.contains(e.getPosition().toFloat()) && !wavetableLfoBox->getBounds().contains(e.getPosition()))
    {
        processWavetableLfo = !processWavetableLfo;
        repaint();        
    }
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
    else if (colorLfoBox->getBounds().contains(e.getPosition()))
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

}

void GranularFlowWrapper::timerCallback() 
{
    // TODO: 20x za sekundu cele, ne po 1/20s krok

    colorLfoTimer++;
    bounceLfoTimer++;
    mathLfoTimer++;
    wavetableLfoTimer++; 

    granularPlayerTimer++;
    bounceBallTimer++;
    colorRepaintTimer++;
    granularSynthVisualiserTimer++;
    
    

    if (colorLfoTimer * TIMER_MS >= Utils::msToHz(colorLfo->getTimerHz()) && !colorLfo->knobPntrsEmpty() && colorLfo->isImageSet() && processColorLfo) {
        colorLfo->timeCallback();
        colorLfoTimer = 0;
    }

    if (bounceLfoTimer * TIMER_MS >= Utils::msToHz(bounceLfo->getTimerHz()) && !bounceLfo->knobPntrsEmpty() && bounceLfo->getBallSpeed() != 0 && processBounceLfo) {
        bounceLfo->timeCallback();
        bounceLfoTimer = 0;
    }

    if (mathLfoTimer * TIMER_MS >= Utils::msToHz(mathLfo->getTimerHz()) && !mathLfo->knobPntrsEmpty() && processMathLfo && mathLfo->isValidExpression()) {
        mathLfo->timeCallback();
        mathLfoTimer = 0;
    }

    if (wavetableLfoTimer * TIMER_MS >= Utils::msToHz(wavetableLfo->getTimerHz()) && !wavetableLfo->knobPntrsEmpty() && !wavetableLfo->isEmpty() && processWavetableLfo) {
        wavetableLfo->timeCallback();
        wavetableLfoTimer = 0;
    }
    //  GUI
    if (colorRepaintTimer * TIMER_MS >= Utils::msToHz(30) && !colorLfo->knobPntrsEmpty() && colorLfo->isImageSet())
    {
        colorLfo->repaintCanvas();
        colorRepaintTimer = 0;
    }
    
    if (granularPlayerTimer * TIMER_MS >= Utils::msToHz(30) && processGranular) {
        granularSynth->movePositionCallback();
        granularPlayerTimer = 0;
    }

    if (granularSynthVisualiserTimer * TIMER_MS >= Utils::msToHz(1) && !granularSynth->isFileInput() && processGranular)
    {
        granularSynth->setWaveCallback();
        granularSynthVisualiserTimer = 0;
    }

    if (bounceBallTimer * TIMER_MS >= Utils::msToHz(bounceBallSpeed) && !bounceLfo->knobPntrsEmpty() && bounceLfo->getBallSpeed() != 0) {
        bounceLfo->moveBall();
        bounceBallTimer = 0;
    }
    
}

void GranularFlowWrapper::removeThisFromAllListeners() {
    // -----------------
    // Listeners
    // -----------------
    // Reset buttons
    // =====SYNTH
    wavetableSynthReset.removeListener();
    granularSynthReset.removeListener();
    additiveSynthReset.removeListener();
    // =====LFO
    colorLfoReset.removeListener();
    bounceLfoReset.removeListener();
    mathLfoReset.removeListener();
    wavetableLfoReset.removeListener();
    // Sliders
    // =====LFO
    colorLfo->removeTimerListener(this);

}

void GranularFlowWrapper::initGui() {
    // -----
    // Components
    // -----
    // Separator
    addAndMakeVisible(topLine);
    // Synth squares
    addAndMakeVisible(wavetableSynthBox);
    addAndMakeVisible(granularSynthBox);
    addAndMakeVisible(additiveSynthBox);
    // Reset SYNTH
    addAndMakeVisible(wavetableSynthReset);
    addAndMakeVisible(granularSynthReset);
    addAndMakeVisible(additiveSynthReset);
    // Lfo squares
    addAndMakeVisible(colorLfoBox);
    addAndMakeVisible(bounceLfoBox);
    addAndMakeVisible(wavetableLfoBox);
    addAndMakeVisible(mathLfoBox);
    // Reset LFO
    addAndMakeVisible(colorLfoReset);
    addAndMakeVisible(bounceLfoReset);
    addAndMakeVisible(mathLfoReset);
    addAndMakeVisible(wavetableLfoReset);
    // -----
    // Non visible process Synths
    // -----
    // SYNTH
    addChildComponent(wavetableSynth.get());
    addChildComponent(granularSynth.get());
    addChildComponent(additiveSynth.get());
    // LFO
    addChildComponent(colorLfo.get());
    addChildComponent(bounceLfo.get());
    addChildComponent(mathLfo.get());
    addChildComponent(wavetableLfo.get());
    // -----
    // WINDOWS
    // -----
    // add all components to separate windows
    // SYNTH
    synthWindows.add(new CustomWindow("Wavetable synth", wavetableSynth.get()));
    synthWindows.add(new CustomWindow("Granular synth", granularSynth.get()));
    synthWindows.add(new CustomWindow("Additive synth", additiveSynth.get()));
    // LFO
    lfoWindows.add(new CustomWindow("Color LFO", colorLfo.get()));
    lfoWindows.add(new CustomWindow("Bounce LFO", bounceLfo.get()));
    lfoWindows.add(new CustomWindow("Math LFO", mathLfo.get()));
    lfoWindows.add(new CustomWindow("Wavetable LFO", wavetableLfo.get()));
}

void GranularFlowWrapper::makeWindowsIgnoreClicks() {
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
}

void GranularFlowWrapper::addAllListeners() {
    // -----------------
    // Reset buttons
    // -----------------
    // SYNTH
    wavetableSynthReset.setListener(this);
    granularSynthReset.setListener(this);
    additiveSynthReset.setListener(this);
    // LFO
    colorLfoReset.setListener(this);
    bounceLfoReset.setListener(this);
    mathLfoReset.setListener(this);
    wavetableLfoReset.setListener(this);
    // -----------------
    // Timer Listeners
    // -----------------
    colorLfo->addTimerListener(this);
    bounceLfo->addTimerListener(this);
    mathLfo->addTimerListener(this);
    wavetableLfo->addTimerListener(this);

    //BallSpeed
    bounceLfo->addBallSpeedListener(this);
    // ---------------
    // Knobs listeners
    // ---------------
    // SYNTHS
    wavetableSynth->setKnobsListener(this);
    granularSynth->setKnobsListener(this);
    additiveSynth->setKnobsListener(this);
}

void GranularFlowWrapper::removeAllListeners()
{
    // -----------------
    // Reset buttons
    // -----------------
    // SYNTH
    wavetableSynthReset.removeListener();
    granularSynthReset.removeListener();
    additiveSynthReset.removeListener();
    // LFO
    colorLfoReset.removeListener();
    bounceLfoReset.removeListener();
    mathLfoReset.removeListener();
    wavetableLfoReset.removeListener();
    // -----------------
    // Timer Listeners
    // -----------------
    colorLfo->removeTimerListener(this);
    bounceLfo->removeTimerListener(this);
    mathLfo->removeTimerListener(this);
    wavetableLfo->removeTimerListener(this);
    // ball
    bounceLfo->removeBallSpeedListener(this);
    // ---------------
    // Knobs listeners
    // ---------------
    // SYNTHS
    wavetableSynth->removeKnobsListener();
    granularSynth->removeKnobsListener();
    additiveSynth->removeKnobsListener();
    
}
