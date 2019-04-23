/*
  ==============================================================================

    Metagnome.cpp
    Created: 22 Apr 2019 5:42:04pm
    Author:  accraze

  ==============================================================================
*/

#include "Metagnome.h"

void Metagnome::prepareToPlay(double sampleRate)
{
    mSampleRate = sampleRate;
}

void Metagnome::countSamples(int bufferSize)
{
    mTotalSamples+=bufferSize;
    DBG(mTotalSamples);
}

void Metagnome::reset()
{
    mTotalSamples = 0;
}
