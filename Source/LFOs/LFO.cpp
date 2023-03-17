#include "LFO.h"


LFO::LFO() 
{
}

LFO::~LFO() 
{
    for (Knob* knob : knobPntrs)
    {
        if (knob != nullptr)
        {
            // SOMEWHERE IS ERROR IN KNOB
            knob = nullptr;
        }
    }
    
}

void LFO::updateKnobs(double value)
{
     for (Knob* knob : knobPntrs)
     {
         if (knob != nullptr)
         {
             knob->setLfoValue(value);
         }
     }
}


void LFO::addKnobToListeners(Knob* knobPntrIn) 
{ 
    knobPntrs.add(knobPntrIn);
}

void LFO::removeKnobFromListeners(Knob* knobPntrIn)
{
    int index = -666;

    for (int i = 0; i < knobPntrs.size(); i++)
    {
        if (knobPntrs[i] == knobPntrIn)
        {
            index = i;
        }
    }

    if (index != -666)
    {
        knobPntrs.remove(index, false);
    }
}

bool LFO::knobPntrsEmpty()
{
    //DBG("current size is" << knobPntrs.size());
    return knobPntrs.isEmpty();
}
