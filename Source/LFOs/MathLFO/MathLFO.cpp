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

    settings.addRateListener(this);    
    settings.addEnterListener(this);
}

MathLFO::~MathLFO()
{
    settings.removeRateListener(this);
    settings.removeEnterListener(this);
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

void MathLFO::addTimerListener(Slider::Listener* listener)
{
    settings.addRateListener(listener);
}

void MathLFO::removeTimerListener(Slider::Listener* listener)
{
    settings.removeRateListener(listener);
}

void MathLFO::timeCallback()
{
    if (isValidExpression(expressionString))
    {
        updateKnobs(getNext());
    }    
}

void MathLFO::sliderValueChanged(Slider* slider)
{
    if (settings.isRateSlider(slider))
    {     
        frequency = slider->getValue();
        calculateDelta();
    }
}

void MathLFO::buttonClicked(Button* button)
{
    if (settings.isEnterButton(button))
    {        
        std::string tmpExpressionString = settings.getText();

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
    exprtk::parser<double> parser;
    exprtk::expression<double> expr;
    exprtk::symbol_table<double> symbolTable;

    symbolTable.add_variable("x", x);
    symbolTable.add_constants();
    expr.register_symbol_table(symbolTable);   
    // Parse expression
    // "sin(x) + 2 * cos(x)";
    parser.compile(expressionString, expr);
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

int MathLFO::getTimerHz() {
    return settings.getRate();
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