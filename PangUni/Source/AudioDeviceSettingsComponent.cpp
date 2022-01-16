/*
  ==============================================================================

    AudioDeviceSettingsComponent.cpp
    Created: 16 Jan 2022 1:07:45pm
    Author:  YC

  ==============================================================================
*/

#include <JuceHeader.h>
#include "AudioDeviceSettingsComponent.h"

//==============================================================================
AudioDeviceSettingsComponent::AudioDeviceSettingsComponent()
{
    adm.reset(new juce::AudioDeviceManager());
    adm->initialiseWithDefaultDevices(0, 2);
    adsComp.reset(new juce::AudioDeviceSelectorComponent(*(adm.get()), 0, 0, 2, 2, true, false, true, false));
    addAndMakeVisible(adsComp.get());
    setSize(100, 100);
}

AudioDeviceSettingsComponent::~AudioDeviceSettingsComponent()
{
}

void AudioDeviceSettingsComponent::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (juce::Colours::white);
    g.setFont (14.0f);
    g.drawText ("AudioDeviceSettingsComponent", getLocalBounds(),
                juce::Justification::centred, true);   // draw some placeholder text
}

void AudioDeviceSettingsComponent::resized()
{
    adsComp->setBounds(10, 10, getWidth(), getHeight());

}
