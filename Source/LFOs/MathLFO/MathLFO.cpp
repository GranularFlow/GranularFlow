#include "MathLFO.h"

MathLFO::MathLFO()
{
    addAndMakeVisible(visualiser);
    addAndMakeVisible(settings);   
    settings.addEnterListener(this);
    setOpaque(true);
}

MathLFO::~MathLFO()
{
    settings.removeEnterListener(this);
}

void MathLFO::paint(Graphics& g)
{
    g.fillAll(Colour::fromRGB(33,33,33));
}

void MathLFO::resized()
{
    settings.setBounds(SETTINGS_SIZE.withSizeKeepingCentre(750, 220));
    visualiser.setBounds(getLocalBounds().withTrimmedLeft(25).withTrimmedRight(25).withTrimmedTop(60 + 10).withTrimmedBottom(SETTINGS_SIZE.getHeight() + 20));
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
    if (isValidExpression() && !knobPntrsEmpty())
    {
        updateKnobs(std::abs(getNext()));
    }    
}

bool MathLFO::isTimerSlider(Slider* slider)
{
    return settings.isRateSlider(slider);
}

void MathLFO::buttonClicked(Button* button)
{
    if (settings.isEnterButton(button))
    {        
        if (isValidExpression(settings.getText()))
        {
            index = 0;
            initSamples(settings.getText(), 100);
        }
    }
}

void MathLFO::initSamples(std::string expressionString, int sampleCount)
{
    samples.clear();
    double x = 0;
    double pi = PI;

    exprtk::parser<double> parser;
    exprtk::expression<double> expr;
    exprtk::symbol_table<double> symbolTable;

    expr.register_symbol_table(symbolTable);
    symbolTable.add_variable("x", x);
    symbolTable.add_constant("pi", pi);    

    for (int i = 0; i < sampleCount; i++)
    {
        x = i * 0.1f;
        parser.compile(expressionString, expr);
        samples.add(0.5f * sin(expr.value()) + 0.5f);
    }

    visualiser.setSamples(samples);
    index = 0;
}

float MathLFO::getTimerHz() {
    return settings.getRate();
}

double MathLFO::getNext()
{    
    value = samples[index] * settings.getDepth();
    index = std::fmod(index + (settings.getRate() * samples.size() /Utils::msToHz(TIMER_MS)), (float)samples.size());
    return value;
}

bool MathLFO::isValidExpression()
{
    return validExp;
}

bool MathLFO::isValidExpression(const std::string& expression)
{

    if (expression == "")
    {
        validExp = false;
        return false;
    }

    exprtk::parser<double> tmpParser;
    exprtk::expression<double> tmpExpr;
    exprtk::symbol_table<double> tmpSymbol;
    double tmpX = 1;
    tmpSymbol.add_constants();
    tmpSymbol.add_variable("x", tmpX);
    tmpExpr.register_symbol_table(tmpSymbol);

    validExp = tmpParser.compile(expression, tmpExpr);
    return validExp;
}