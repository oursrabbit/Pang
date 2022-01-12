/*
  ==============================================================================

    MainWindowMainComponent.h
    Created: 11 Jan 2022 5:49:34pm
    Author:  YC

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class SearchWindowMainComponent  : public juce::Component
{
public:
    SearchWindowMainComponent();
    ~SearchWindowMainComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SearchWindowMainComponent)
};
