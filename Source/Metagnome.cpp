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
    mInterval = 60.0 / mBpm * mSampleRate;
    HighResolutionTimer::startTimer(60.0);
}

void Metagnome::countSamples(int bufferSize)
{
    mTotalSamples+=bufferSize;
    mSamplesRemaining = mTotalSamples % mInterval;
    
    DBG("Samples Remaining: " << mSamplesRemaining);
    DBG("Beat Interval: " << mInterval);
    
    // look at upcoming buffer before sample resets.
    if ((mSamplesRemaining + bufferSize) >= mInterval) {
        DBG("CLICK!!!");
        DBG("Total Samples: " << mTotalSamples);
    }
}

void Metagnome::reset()
{
    mTotalSamples = 0;
}

void Metagnome::hiResTimerCallback()
{
    mInterval = 60.0 / mBpm * mSampleRate;
}
