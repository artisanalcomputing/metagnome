/*
  ==============================================================================

    Metagnome.h
    Created: 22 Apr 2019 5:42:04pm
    Author:  accraze

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

class Metagnome
{
public:
    void prepareToPlay (double sampleRate);
    void countSamples (int bufferSize);
    void reset();
    
private:
    int mTotalSamples { 0 };
    double mSampleRate { 0 };
    
};
