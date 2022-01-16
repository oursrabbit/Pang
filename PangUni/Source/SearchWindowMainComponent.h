/*
  ==============================================================================

    MainWindowMainComponent.h
    Created: 11 Jan 2022 5:49:34pm
    Author:  YC

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "SearchDataStruct.h"
#include "AudioSearchComponent.h"
#include "AudioExportComponent.h"

//==============================================================================
/*
*/
class SearchWindowMainComponent  : public juce::Component, public AudioSearchComponentListener
{
public:
    SearchDataStruct* newData;
    std::unique_ptr<AudioSearchComponent> audioSearchComp;
    std::unique_ptr<AudioExportComponent> audioExportComp;
    
    SearchWindowMainComponent();
    SearchWindowMainComponent(SearchDataStruct* newData);
    ~SearchWindowMainComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    bool keyPressed(const juce::KeyPress& press) override;

    virtual void selectedFileChanged() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SearchWindowMainComponent)
};
