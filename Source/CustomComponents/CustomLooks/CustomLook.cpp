/*
  ==============================================================================

    KnobDraw.cpp
    Created: 22 Nov 2022 10:25:16pm
    Author:  honza

  ==============================================================================
*/

#include "CustomLook.h"

CustomLook::CustomLook() {}
CustomLook::~CustomLook() {}

void CustomLook::drawPopupMenuItem(Graphics& g, const Rectangle<int>& area, const bool isSeparator, const bool isActive, const bool isHighlighted, const bool isTicked, const bool hasSubMenu, const String& text, const String& shortcutKeyText, const Drawable* icon, const Colour* textColourToUse)
{
    Colour backgroundColour = C_DARK;
    Colour textColour = C_WHITE;

    if (isHighlighted)
    {
        backgroundColour = M_T_LIGHT;
        textColour = Colours::white;
    }

    g.setColour(backgroundColour);
    g.fillRect(area);

    g.setColour(textColour);
    g.setFont(getPopupMenuFont());
    g.drawFittedText(text, area.reduced(2), juce::Justification::centred, 1);
}
void CustomLook::drawComboBox(Graphics& g, int width, int height, bool isButtonDown, int buttonX, int buttonY, int buttonW, int buttonH, ComboBox& box)
{
    auto cornerSize = box.findParentComponentOfClass<ChoicePropertyComponent>() != nullptr ? 0.0f : 3.0f;
    Rectangle<int> boxBounds(0, 0, width, height);

    

    g.setColour(C_WHITE);
    g.drawRoundedRectangle(boxBounds.toFloat().reduced(0.5f, 0.5f), cornerSize, 1.0f);

    Rectangle<int> arrowZone(width - 30, 0, 20, height);
    Path path;
    path.startNewSubPath((float)arrowZone.getX() + 3.0f, (float)arrowZone.getCentreY() - 2.0f);
    path.lineTo((float)arrowZone.getCentreX(), (float)arrowZone.getCentreY() + 3.0f);
    path.lineTo((float)arrowZone.getRight() - 3.0f, (float)arrowZone.getCentreY() - 2.0f);

    g.strokePath(path, PathStrokeType(2.0f));
}

void CustomLook::drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height, float sliderPos,
    const float rotaryStartAngle, const float rotaryEndAngle, juce::Slider& slider)
{
    auto outline = M_DARK;
    auto fill = slider.findColour(Slider::rotarySliderFillColourId);

    auto bounds = Rectangle<int>(x, y, width, height).toFloat().reduced(10);

    auto radius = jmin(bounds.getWidth(), bounds.getHeight()) / 2.0f;
    auto toAngle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
    auto lineW = jmin(5.0f, radius /2.f);
    auto arcRadius = radius - lineW / 2.f;

    Path backgroundArc;
    backgroundArc.addCentredArc(bounds.getCentreX(),
        bounds.getCentreY(),
        arcRadius,
        arcRadius,
        0.0f,
        rotaryStartAngle,
        rotaryEndAngle,
        true);

    g.setColour(outline);
    g.strokePath(backgroundArc, PathStrokeType(lineW, PathStrokeType::curved, PathStrokeType::rounded));

    if (slider.isEnabled())
    {
        Path valueArc;
        valueArc.addCentredArc(bounds.getCentreX(),
            bounds.getCentreY(),
            arcRadius,
            arcRadius,
            0.0f,
            rotaryStartAngle,
            toAngle,
            true);

        g.setColour(fill);
        g.strokePath(valueArc, PathStrokeType(lineW, PathStrokeType::curved, PathStrokeType::butt));
    }

    Point<float> thumbPoint(bounds.getCentreX() + arcRadius * std::cos(toAngle - MathConstants<float>::halfPi),
        bounds.getCentreY() + arcRadius * std::sin(toAngle - MathConstants<float>::halfPi));



    // Thumb
    juce::Path thumb;
    auto thumbLength = radius * 0.75f;
    auto thumbThickness = 5.0f;

    g.setColour(C_GRAY);
    g.fillEllipse(Rectangle<float>(thumbLength * 2, thumbLength * 2).withCentre(Point<float>(bounds.getCentreX(), bounds.getCentreY())));

    thumb.addRoundedRectangle(Rectangle<float>(-thumbThickness / 2, -thumbLength, thumbThickness, thumbLength), 1);
    thumb.applyTransform(juce::AffineTransform::rotation(toAngle).translated(bounds.getCentreX(), bounds.getCentreY()));

    g.setColour(C_SMOKE);
    g.fillPath(thumb);

    
}
void CustomLook::drawLinearSlider(Graphics& g, int x, int y, int width, int height,
    float sliderPos,
    float minSliderPos,
    float maxSliderPos,
    const Slider::SliderStyle style, Slider& slider)
{
    if (slider.isBar())
    {
        g.setColour(slider.findColour(Slider::trackColourId));
        g.fillRect(slider.isHorizontal() ? Rectangle<float>(static_cast<float> (x), (float)y + 0.5f, sliderPos - (float)x, (float)height - 1.0f)
            : Rectangle<float>((float)x + 0.5f, sliderPos, (float)width - 1.0f, (float)y + ((float)height - sliderPos)));
    }
    else
    {
        auto isTwoVal = (style == Slider::SliderStyle::TwoValueVertical || style == Slider::SliderStyle::TwoValueHorizontal);
        auto isThreeVal = (style == Slider::SliderStyle::ThreeValueVertical || style == Slider::SliderStyle::ThreeValueHorizontal);

        auto trackWidth = jmax(6.0f, slider.isHorizontal() ? (float)height * 0.25f : (float)width * 0.25f);

        Point<float> startPoint(slider.isHorizontal() ? (float)x : (float)x + (float)width * 0.5f,
            slider.isHorizontal() ? (float)y + (float)height * 0.5f : (float)(height + y));

        Point<float> endPoint(slider.isHorizontal() ? (float)(width + x) : startPoint.x,
            slider.isHorizontal() ? startPoint.y : (float)y);

        Path backgroundTrack;
        backgroundTrack.startNewSubPath(startPoint);
        backgroundTrack.lineTo(endPoint);
        g.setColour(slider.findColour(Slider::backgroundColourId));
        g.strokePath(backgroundTrack, { trackWidth, PathStrokeType::curved, PathStrokeType::rounded });

        Path valueTrack;
        Point<float> minPoint, maxPoint, thumbPoint;

        if (isTwoVal || isThreeVal)
        {
            minPoint = { slider.isHorizontal() ? minSliderPos : (float)width * 0.5f,
                         slider.isHorizontal() ? (float)height * 0.5f : minSliderPos };

            if (isThreeVal)
                thumbPoint = { slider.isHorizontal() ? sliderPos : (float)width * 0.5f,
                               slider.isHorizontal() ? (float)height * 0.5f : sliderPos };

            maxPoint = { slider.isHorizontal() ? maxSliderPos : (float)width * 0.5f,
                         slider.isHorizontal() ? (float)height * 0.5f : maxSliderPos };
        }
        else
        {
            auto kx = slider.isHorizontal() ? sliderPos : ((float)x + (float)width * 0.5f);
            auto ky = slider.isHorizontal() ? ((float)y + (float)height * 0.5f) : sliderPos;

            minPoint = startPoint;
            maxPoint = { kx, ky };
        }

        auto thumbWidth = getSliderThumbRadius(slider);

        valueTrack.startNewSubPath(minPoint);
        valueTrack.lineTo(isThreeVal ? thumbPoint : maxPoint);
        g.setColour(slider.findColour(Slider::trackColourId));
        g.strokePath(valueTrack, { trackWidth, PathStrokeType::curved, PathStrokeType::rounded });

        if (!isTwoVal)
        {
            g.setColour(C_WHITE);
            g.fillRect(Rectangle<float>(static_cast<float> (thumbWidth), static_cast<float> (thumbWidth*2)).withCentre(isThreeVal ? thumbPoint : maxPoint));
        }

        if (isTwoVal || isThreeVal)
        {
            auto sr = jmin(trackWidth, (slider.isHorizontal() ? (float)height : (float)width) * 0.4f);
            auto pointerColour = Colours::red;// slider.findColour(Slider::thumbColourId);

            if (slider.isHorizontal())
            {
                /*drawPointer(g, minSliderPos - sr,
                    jmax(0.0f, (float)y + (float)height * 0.5f - trackWidth * 2.0f),
                    trackWidth * 2.0f, pointerColour, 2);*/

                /*drawPointer(g, maxSliderPos - trackWidth,
                    jmin((float)(y + height) - trackWidth * 2.0f, (float)y + (float)height * 0.5f),
                    trackWidth * 2.0f, pointerColour, 4);*/
            }
            else
            {
                drawPointer(g, jmax(0.0f, (float)x + (float)width * 0.5f - trackWidth * 2.0f),
                    minSliderPos - trackWidth,
                    trackWidth * 2.0f, pointerColour, 1);

                drawPointer(g, jmin((float)(x + width) - trackWidth * 2.0f, (float)x + (float)width * 0.5f), maxSliderPos - sr,
                    trackWidth * 2.0f, pointerColour, 3);
            }
        }
    }
    
}

void CustomLook::drawTickBox(Graphics& g, Component& component,
    float x, float y, float w, float h,
    const bool ticked,
    const bool isEnabled,
    const bool shouldDrawButtonAsHighlighted,
    const bool shouldDrawButtonAsDown)
{
    ignoreUnused(isEnabled, shouldDrawButtonAsHighlighted, shouldDrawButtonAsDown);
    Rectangle<float> tickBounds(x + (w * 0.25 / 2), y + (h * 0.25 / 2), w * 0.75, h * 0.75);

    g.setColour(C_VL_GRAY);
    g.drawEllipse(tickBounds, 2.5f);

    if (ticked)
    {
        g.setColour(component.findColour(ToggleButton::tickColourId));
        g.fillEllipse(tickBounds.reduced(2));
    }
}