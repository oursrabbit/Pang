#include <JuceHeader.h>
#include "AudioCoverComponent.h"

//==============================================================================
AudioCoverComponent::AudioCoverComponent()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

}

AudioCoverComponent::~AudioCoverComponent()
{
}

void AudioCoverComponent::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll(juce::Colour(juce::uint8(255), 0, 0, 0.2f));   // clear the background
}

void AudioCoverComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}