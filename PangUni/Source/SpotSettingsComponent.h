/*
  ==============================================================================

    SpotSettingsComponent.h
    Created: 14 Jan 2022 8:59:43pm
    Author:  YC

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class SpotSettingsComponent  : public juce::Component
{
public:
    std::function<void()> OnValueChanged;

    SpotSettingsComponent();
    ~SpotSettingsComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SpotSettingsComponent)
};
