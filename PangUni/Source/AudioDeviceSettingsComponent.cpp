/*
  ==============================================================================

    AudioDeviceSettingsComponent.cpp
    Created: 16 Jan 2022 1:07:45pm
    Author:  YC

  ==============================================================================
*/

#include <JuceHeader.h>
#include "AudioDeviceSettingsComponent.h"
#include "SystemHelper.h"

//==============================================================================
AudioDeviceSettingsComponent::AudioDeviceSettingsComponent()
{
    adsComp.reset(new juce::AudioDeviceSelectorComponent(*(SystemHelper::Helper->audioDeviceManager.get()), 0, 0, 2, 2, true, false, true, false));
    SystemHelper::Helper->audioDeviceManager->addChangeListener(this);
    addAndMakeVisible(adsComp.get());
    setSize(100, 100);
}

AudioDeviceSettingsComponent::~AudioDeviceSettingsComponent()
{
}

void AudioDeviceSettingsComponent::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background
}

void AudioDeviceSettingsComponent::resized()
{
    adsComp->setBounds(10, 10, getWidth(), getHeight());
}

void AudioDeviceSettingsComponent::changeListenerCallback(juce::ChangeBroadcaster* source)
{
    if (source == SystemHelper::Helper->audioDeviceManager.get())
    {
        OnValueChanged();
    }
}
