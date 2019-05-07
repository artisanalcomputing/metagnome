/*
  ==============================================================================

    Metagnome.h
    Created: 22 Apr 2019 5:42:04pm
    Author:  accraze

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

class Metagnome : public HighResolutionTimer
{
public:
    Metagnome();
    void prepareToPlay (int samplesPerBlock, double sampleRate);
    void getNextAudioBlock(const AudioSourceChannelInfo& bufferToFill);
    void reset();
    
    void hiResTimerCallback() override;
    
private:
    int mTotalSamples { 0 };
    double mSampleRate { 0 };
    int mInterval { 0 };
    double mBpm { 60.0 };
    int mSamplesRemaining { 0 };
    
    AudioFormatManager mFormatManager;
    std::unique_ptr <AudioFormatReaderSource> pMetronomeSample {nullptr};
};
