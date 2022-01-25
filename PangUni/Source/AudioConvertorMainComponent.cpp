/*
  ==============================================================================

    MainWindowMainComponent.cpp
    Created: 11 Jan 2022 5:49:34pm
    Author:  YC

  ==============================================================================
*/

#include <JuceHeader.h>
#include "AudioConvertorMainComponent.h"

//==============================================================================
AudioConvertorMainComponent::AudioConvertorMainComponent()
{
    setSize(1000, 600);
}

AudioConvertorMainComponent::~AudioConvertorMainComponent()
{

}

void AudioConvertorMainComponent::paint(juce::Graphics& g)
{
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));   // clear the background
}

void AudioConvertorMainComponent::resized()
{

}