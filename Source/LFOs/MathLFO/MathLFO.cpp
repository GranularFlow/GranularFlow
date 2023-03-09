/*
  ==============================================================================

    MathLFO.cpp
    Created: 20 Feb 2023 9:01:58pm
    Author:  honza

  ==============================================================================
*/

#include "MathLFO.h"

MathLFO::MathLFO()
{
    addAndMakeVisible(visualiser);
    addAndMakeVisible(settings);

    settings.rateKnob.addSliderListener(this);
    settings.enterButton.addListener(this);
}

MathLFO::~MathLFO()
{
    stopTimer();
    settings.rateKnob.removeSliderListener(this);
    settings.enterButton.removeListener(this);
}

void MathLFO::paint(Graphics& g)
{
    g.fillAll(C_DARK);
    Utils::paintLogo(g);
}

void MathLFO::resized()
{
    juce::Rectangle<int> settingsBounds = getLocalBounds().withSize(820, 180).withCentre(Point<int>(getWidth()/2, getHeight() - 110));
    settings.setBounds(settingsBounds);
    visualiser.setBounds(getLocalBounds().withSize(1000,400).withCentre(Point<int>(getWidth()/2, 200 + 60 )));
}

void MathLFO::timerCallback()
{
    if (isValidExpression(expressionString))
    {
        updateKnobs(getNext());
    }    
}

void MathLFO::sliderValueChanged(Slider* slider)
{
    if (slider == &settings.rateKnob.getSlider())
    {
        stopTimer();        
        frequency = slider->getValue();
        calculateDelta();
        startTimerHz(frequency);
    }
}

void MathLFO::buttonClicked(Button* button)
{
    if (button == &settings.enterButton)
    {        
        std::string tmpExpressionString = settings.textEditor.getText().toStdString();

        if (isValidExpression(tmpExpressionString))
        {
            calculateDelta();
            expressionString = tmpExpressionString;
            initSamples();
        }
    }
}

void MathLFO::calculateDelta()
{
    delta = 2 * PI /(float) 256;
}

double MathLFO::calculateEquation(double x) {
    // Create expression and variables
    //DBG("x" << x);
    exprtk::parser<double> parser;
    exprtk::expression<double> expr;
    exprtk::symbol_table<double> symbolTable;

    symbolTable.add_variable("x", x);
    symbolTable.add_constants();
    expr.register_symbol_table(symbolTable);   
    // Parse expression
    // "sin(x) + 2 * cos(x)";
    parser.compile(expressionString, expr);
    //DBG("expr.value()" << expr.value());
    return expr.value();
}

void MathLFO::initSamples()
{
    samples.clear();
    for (int i = 0; i < 256; i++)
    {
        samples.add(getNext());
    }
    visualiser.setSamples(samples);
}

double MathLFO::getNext()
{    
    double output = calculateEquation(angle);
    angle = fmod(angle + delta,(double) 2 * PI);
    return output;
}

bool MathLFO::isValidExpression(const std::string& expression)
{
    if (expression == "")
    {
        return false;
    }

    exprtk::parser<double> tmpParser;
    exprtk::expression<double> tmpExpr;
    exprtk::symbol_table<double> tmpSymbol;
    double tmpX = 1;
    tmpSymbol.add_constants();
    tmpSymbol.add_variable("x", tmpX);
    tmpExpr.register_symbol_table(tmpSymbol);

    return tmpParser.compile(expression, tmpExpr);
}