/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    // Make sure you set the size of the component after
    // you add any child components.
    mPlayButton.setRadioGroupId(1);
    mPlayButton.setToggleState(false, NotificationType::dontSendNotification);
    mPlayButton.onClick = [this](){ play(); };
    addAndMakeVisible(mPlayButton);
    
    mStopButton.setRadioGroupId(1);
    mStopButton.setToggleState(true, NotificationType::dontSendNotification);
    mStopButton.onClick = [this](){ stop(); };
    addAndMakeVisible(mStopButton);
    
    setSize (200, 200);

    // Some platforms require permissions to open input channels so request that here
    if (RuntimePermissions::isRequired (RuntimePermissions::recordAudio)
        && ! RuntimePermissions::isGranted (RuntimePermissions::recordAudio))
    {
        RuntimePermissions::request (RuntimePermissions::recordAudio,
                                     [&] (bool granted) { if (granted)  setAudioChannels (2, 2); });
    }
    else
    {
        // Specify the number of input and output channels that we want to open
        setAudioChannels (2, 2);
    }
}

MainComponent::~MainComponent()
{
    // This shuts down the audio device and clears the audio source.
    shutdownAudio();
}

void MainComponent::play()
{
    mPlayState = PlayState::Playing;
}

void MainComponent::stop()
{
    mPlayState = PlayState::Stopped;
    mMetagnome.reset();
}

//==============================================================================
void MainComponent::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{
    mMetagnome.prepareToPlay(samplesPerBlockExpected, sampleRate);
}

void MainComponent::getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill)
{
    bufferToFill.clearActiveBufferRegion();
    
//    auto buffer = bufferToFill.numSamples;
    
    if(mPlayState == PlayState::Playing)
    {
        mMetagnome.getNextAudioBlock(bufferToFill);
    } 
}

void MainComponent::releaseResources()
{
    // This will be called when the audio device stops, or when it is being
    // restarted due to a setting change.

    // For more details, see the help for AudioProcessor::releaseResources()
    mMetagnome.releaseResources();
}

//==============================================================================
void MainComponent::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    // You can add your drawing code here!
}

void MainComponent::resized()
{
    Rectangle<int> bounds = getLocalBounds();
    
    FlexBox flexBox;
    flexBox.items.add(FlexItem(100, 100, mPlayButton));
    flexBox.items.add(FlexItem(100, 100, mStopButton));
    flexBox.performLayout(bounds);
}
