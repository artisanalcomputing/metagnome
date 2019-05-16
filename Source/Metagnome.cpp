/*
  ==============================================================================

    Metagnome.cpp
    Created: 22 Apr 2019 5:42:04pm
    Author:  accraze

  ==============================================================================
*/

#include "Metagnome.h"

Metagnome::Metagnome()
{
    mFormatManager.registerBasicFormats();
    
    File myFile { File::getSpecialLocation(File::SpecialLocationType::userDesktopDirectory) };
    auto mySamples = myFile.findChildFiles(File::TypesOfFileToFind::findFiles, true, "9744__horn__typewriter.wav");
    
    jassert(mySamples[0].exists());
    
    auto formatReader = mFormatManager.createReaderFor(mySamples[0]);
    
    pMetronomeSample.reset(new AudioFormatReaderSource(formatReader, true));
    mInterval = 60.0 / mBpm * mSampleRate;
    
//    if (mySamples[0].exists())
//    {
//        //load file
//    }
//    else {
//        //warning
//    }
}

void Metagnome::prepareToPlay(int samplesPerBlock, double sampleRate)
{
    mSampleRate = sampleRate;
    mInterval = 60.0 / mBpm * mSampleRate;
    
    if (pMetronomeSample != nullptr) {
        pMetronomeSample->prepareToPlay(samplesPerBlock, sampleRate);
    }
}

void Metagnome::getNextAudioBlock(const AudioSourceChannelInfo& bufferToFill)
{
    const auto bufferSize = bufferToFill.numSamples;
    
    mTotalSamples+=bufferSize;
    mSamplesRemaining = mTotalSamples % mInterval;
    
    
    // look at upcoming buffer before sample resets.
    if ((mSamplesRemaining + bufferSize) >= mInterval) {
        const auto timeToStartPlaying = mInterval - mSamplesRemaining;
        pMetronomeSample->setNextReadPosition(0);
        
        for (auto sample = 0; sample < bufferSize; sample++) {
            if (sample == timeToStartPlaying){
                pMetronomeSample->getNextAudioBlock(bufferToFill);
            }
            
        }
    }
    
    if (pMetronomeSample->getNextReadPosition() !=0)
    {
        pMetronomeSample->getNextAudioBlock(bufferToFill);
    }
}

void Metagnome::reset()
{
    mTotalSamples = 0;
}

void Metagnome::releaseResources()
{
    pMetronomeSample->releaseResources();
}
