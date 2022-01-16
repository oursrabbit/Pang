/*
  ==============================================================================

    MainComponent.h
    Created: 12 Jan 2022 12:51:19pm
    Author:  YC

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PangMenuComponent.h"
#include "SearchWindowMainComponent.h"
#include "SearchDataStruct.h"

//==============================================================================
/*
*/
class MainComponent  : public juce::Component
{
public:
    MainComponent();
    ~MainComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    SearchDataStruct* newData;
    std::unique_ptr<PangMenuComponent> menu;
    std::unique_ptr<SearchWindowMainComponent> mainComp;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
