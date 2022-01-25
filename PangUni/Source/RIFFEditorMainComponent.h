/*
  ==============================================================================

    MainWindowMainComponent.h
    Created: 11 Jan 2022 5:49:34pm
    Author:  YC

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "WAVFormatPangEx.h"

//==============================================================================
/*
*/
class RIFFEditorMainComponent : public juce::Component, public juce::Button::Listener
{
public:
    RIFFEditorMainComponent();
    ~RIFFEditorMainComponent() override;

    void paint(juce::Graphics&) override;
    void resized() override;

    virtual void buttonClicked(juce::Button*) override;

    std::unique_ptr<juce::TextButton> openFileButton;
    std::unique_ptr<juce::FileChooser> chooser;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(RIFFEditorMainComponent)
};
