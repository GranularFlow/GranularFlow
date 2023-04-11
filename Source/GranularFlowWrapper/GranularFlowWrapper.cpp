#include "GranularFlowWrapper.h"

GranularFlowWrapper::GranularFlowWrapper() :
    Component("GranularFlowWrapper")
{
    setSize(W_WIDTH, W_HEIGHT);
    initGui();
    addAllListeners();
    makeWindowsIgnoreClicks();
    setRepaintsOnMouseActivity(false);
    startTimer(TIMER_MS);
}

GranularFlowWrapper::~GranularFlowWrapper()
{
    removeThisFromAllListeners();
    // Clean non-visible synths and lfos FIRST
    // MUST CLOSE
    closeWindows();
    // clean boxes
    
    // MUST DELETE
    //SYNTH
    delete wavetableSynthBox;
    delete granularSynthBox;
    delete additiveSynthBox;
    //LFO
    delete colorLfoBox;
    delete bounceLfoBox;
    delete wavetableLfoBox;
    delete mathLfoBox;

    // MUST DELETE AFTER CLICKABLE WINDOWS
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
}

void GranularFlowWrapper::paintJacks(Graphics& g)
{
    Path pathL;
    pathL.addRectangle(juce::Rectangle<int>(507, 458, 40, 25).toFloat());
    pathL.applyTransform(AffineTransform::rotation(-0.52359879016876221, 527, 470));
    juce::Rectangle<int> rectR(653, 458, 40, 25);

    Path pathR;
    pathR.addRectangle(rectR.toFloat());
    pathR.applyTransform(AffineTransform::rotation(0.52359879016876221, 673, 470));
    g.setColour(C_LIGTH_GRAY);
    g.fillPath(pathL);
    g.fillPath(pathR);
    g.fillRect(588, 349, 25, 40);
}

void GranularFlowWrapper::paintCables(Graphics& g)
{
    if (processWavetable) { g.setColour(C_ANDROID_GREEN); }
    else { g.setColour(C_DARKER_GRAY); }
    g.fillPath(cableWavetable);

    if (processGranular) { g.setColour(C_ANDROID_GREEN); }
    else { g.setColour(C_DARKER_GRAY); }
    g.fillPath(cableGranular);

    if (processAdditive) { g.setColour(C_ANDROID_GREEN); }
    else { g.setColour(C_DARKER_GRAY); }
    g.fillPath(cableAdditive);

    if (processColorLfo) { g.setColour(C_ANDROID_GREEN); }
    else { g.setColour(C_DARKER_GRAY); }
    g.fillRoundedRectangle(cableColorLfo, 15);

    if (processBounceLfo) { g.setColour(C_ANDROID_GREEN); }
    else { g.setColour(C_DARKER_GRAY); }
    g.fillRoundedRectangle(cableBounceLfo, 15);

    if (processMathLfo) { g.setColour(C_ANDROID_GREEN); }
    else { g.setColour(C_DARKER_GRAY); }
    g.fillRoundedRectangle(cableMathLfo, 15);

    if (processWavetableLfo) { g.setColour(C_ANDROID_GREEN); }
    else { g.setColour(C_DARKER_GRAY); }
    g.fillRoundedRectangle(cableWavetableLfo, 15);
}

void GranularFlowWrapper::paint(Graphics&g)
{
    
  // DBG("GranularFlowWrapper::paint");
    // Cables
    paintCables(g);
    // Jacks
    paintJacks(g);
    // Middle Circle
    g.setColour(Colour::fromRGB(50, 50, 50));
    g.fillRoundedRectangle(540, 386, 120, 120, 60);

    //g.drawImageWithin(ImageFileFormat::loadFrom(BinaryData::wave_png, BinaryData::wave_pngSize), 570, 416, 60, 60, RectanglePlacement::centred, false);

    // LFO Background
    g.setColour(Colour::fromRGB(50, 50, 50));
    g.drawRoundedRectangle(juce::Rectangle<float>(190, 538, 820, 155), 7, 2);
}

void GranularFlowWrapper::resized()
{
   //// DBG("GranularFlowWrapper::resized");
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
        bounceLfoRepaintTimer = slider->getValue();
        bounceLfoBallMoveTimer = 0;
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

    else if (button == &colorLfoReset && colorLfo->knobPntrsEmpty() && !processColorLfo)
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
    additiveBoxIsVisible = false;
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
        repaint(cableWavetable.getBounds().toNearestInt());
    }
    else if (cableGranular.contains(e.getPosition().toFloat(), 20.f))
    {
        processGranular = !processGranular;
        repaint(cableGranular.getBounds().toNearestInt());
    }
    else if (cableAdditive.contains(e.getPosition().toFloat(), 20.f))
    {
        processAdditive = !processAdditive;
        repaint(cableAdditive.getBounds().toNearestInt());
    }
    else if (cableColorLfo.contains(e.getPosition().toFloat()) && !colorLfoBox->getBounds().contains(e.getPosition()))
    {
        processColorLfo = !processColorLfo;
        repaint(cableColorLfo.toNearestInt());
    }
    else if (cableBounceLfo.contains(e.getPosition().toFloat()) && !bounceLfoBox->getBounds().contains(e.getPosition()))
    {
        processBounceLfo = !processBounceLfo;
        repaint(cableBounceLfo.toNearestInt());
    }
    else if (cableMathLfo.contains(e.getPosition().toFloat()) && !mathLfoBox->getBounds().contains(e.getPosition()))
    {
        processMathLfo = !processMathLfo;
        repaint(cableMathLfo.toNearestInt());
    }
    else if (cableWavetableLfo.contains(e.getPosition().toFloat()) && !wavetableLfoBox->getBounds().contains(e.getPosition()))
    {
        processWavetableLfo = !processWavetableLfo;
        repaint(cableWavetableLfo.toNearestInt());
    }
    else if (wavetableSynthBox->getBounds().contains(e.getPosition()))
    {        
        synthWindows[0]->showWindow();
    }
    else if (granularSynthBox->getBounds().contains(e.getPosition()))
    {        
        synthWindows[1]->showWindow();
    }
    else if (additiveSynthBox->getBounds().contains(e.getPosition()))
    {
        additiveBoxIsVisible = true;
        synthWindows[2]->showWindow();
    }
    else if (colorLfoBox->getBounds().contains(e.getPosition()))
    {
        lfoWindows[0]->showWindow();
    }
    else if (bounceLfoBox->getBounds().contains(e.getPosition()))
    {
        lfoWindows[1]->showWindow();
    }
    else if (mathLfoBox->getBounds().contains(e.getPosition()))
    {
        lfoWindows[2]->showWindow();
    }
    else if (wavetableLfoBox->getBounds().contains(e.getPosition()))
    {
        lfoWindows[3]->showWindow();
    }

}

void GranularFlowWrapper::setAllKnobs()
{

}

void GranularFlowWrapper::timerCallback() 
{
    if (colorLfo)
    {
        colorLfoTimer++;
    }
    if (processBounceLfo)
    {
        bounceLfoTimer++;
        bounceLfoBallMoveTimer++;
    }
    if (processMathLfo)
    {
        mathLfoTimer++;
    }
    if (processWavetableLfo)
    {
        wavetableLfoTimer++;
    }
    // gui
    granularPlayerTimer++;
    colorLfoRepaintTimer++;
    granularRepaintTimer++;
    additiveRepaintTimer++;

    if (colorLfoTimer * TIMER_MS >= Utils::hzToMs(colorLfo->getTimerHz()) && !colorLfo->knobPntrsEmpty() && colorLfo->isImageSet() && processColorLfo) {
        colorLfo->timeCallback();
        colorLfoTimer = 0;
    }

    if (bounceLfoTimer * TIMER_MS >= Utils::hzToMs(bounceLfo->getTimerHz()) && !bounceLfo->knobPntrsEmpty() && bounceLfo->getBallSpeed() != 0 && processBounceLfo) {
        bounceLfo->timeCallback();
        bounceLfoTimer = 0;
    }

    if (mathLfoTimer * TIMER_MS >= Utils::hzToMs(mathLfo->getTimerHz()) && !mathLfo->knobPntrsEmpty() && processMathLfo && mathLfo->isValidExpression()) {
        mathLfo->timeCallback();
        mathLfoTimer = 0;
    }

    if (wavetableLfoTimer * TIMER_MS >= Utils::hzToMs(wavetableLfo->getTimerHz()) && !wavetableLfo->knobPntrsEmpty() && !wavetableLfo->isEmpty() && processWavetableLfo) {
        wavetableLfo->timeCallback();
        wavetableLfoTimer = 0;
    }
    //  GUI
    if (colorLfoRepaintTimer * TIMER_MS >= Utils::hzToMs(15) && !colorLfo->knobPntrsEmpty() && colorLfo->isImageSet())
    {
        colorLfo->repaintCanvas();
        colorLfoRepaintTimer = 0;
    }
    
    if (granularPlayerTimer * TIMER_MS >= Utils::hzToMs(30) && processGranular) {
        granularSynth->movePositionCallback();
        granularPlayerTimer = 0;
    }

    if (granularRepaintTimer * TIMER_MS >= Utils::hzToMs(1) && !granularSynth->isFileInput() && processGranular)
    {
        granularSynth->setWaveCallback();
        granularRepaintTimer = 0;
    }

    if (bounceLfoBallMoveTimer * TIMER_MS >= Utils::hzToMs(bounceLfoRepaintTimer) && !bounceLfo->knobPntrsEmpty() && bounceLfo->getBallSpeed() != 0 && processBounceLfo) {
        bounceLfo->moveBall();
        bounceLfoBallMoveTimer = 0;
    }    

    if (additiveRepaintTimer * TIMER_MS >= Utils::hzToMs(1) && processAdditive && additiveBoxIsVisible) {
        additiveSynth->repaintVisualiser();
        additiveRepaintTimer = 0;
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

    cableWavetable.startNewSubPath(184, 240);
    cableWavetable.cubicTo(184, 240, 90, 666, 540, 472);
    cableWavetable.lineTo(540, 460);
    cableWavetable.cubicTo(540, 460, 126, 666, 196, 240);
    cableWavetable.closeSubPath();
    //
    cableGranular.startNewSubPath(594, 240);
    cableGranular.lineTo(594, 406);
    cableGranular.lineTo(606, 406);
    cableGranular.lineTo(606, 240);
    cableGranular.closeSubPath();
    //
    cableAdditive.startNewSubPath(1010 + 6, 240);
    cableAdditive.cubicTo(1016, 240, 1110, 666, 660, 472);
    cableAdditive.lineTo(660, 460);
    cableAdditive.cubicTo(660, 460, 1074, 666, 1004, 240);
    cableAdditive.closeSubPath();
    // 
    cableColorLfo = juce::Rectangle<float>(278, 540, 30.f, 30.f);
    cableBounceLfo = juce::Rectangle<float>(484, 540, 30.f, 30.f);
    cableMathLfo = juce::Rectangle<float>(690, 540, 30.f, 30.f);
    cableWavetableLfo = juce::Rectangle<float>(896, 540, 30.f, 30.f);
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
