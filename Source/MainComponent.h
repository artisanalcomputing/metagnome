/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "Metagnome.h"

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent   : public AudioAppComponent
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent();

    //==============================================================================
    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;
    
    void play();
    void stop();

    //==============================================================================
    void paint (Graphics& g) override;
    void resized() override;
    
    enum class PlayState
    {
      Playing,
        Stopped
    };

private:
    TextButton mPlayButton { "Play" };
    TextButton mStopButton { "Stop" };
    
    PlayState mPlayState { PlayState::Stopped };
    
    Metagnome mMetagnome;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
