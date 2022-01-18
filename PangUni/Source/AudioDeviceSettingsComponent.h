/*
  ==============================================================================

    AudioDeviceSettingsComponent.h
    Created: 16 Jan 2022 1:07:45pm
    Author:  YC

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class AudioDeviceSettingsComponent  : public juce::Component, public juce::ChangeListener
{
public:
    AudioDeviceSettingsComponent();
    ~AudioDeviceSettingsComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    std::function<void()> OnValueChanged;
    std::unique_ptr<juce::AudioDeviceSelectorComponent> adsComp;

    juce::XmlElement* createStateXml();
    virtual void changeListenerCallback(juce::ChangeBroadcaster* source) override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AudioDeviceSettingsComponent)
};
