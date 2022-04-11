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
#include "RIFFTableComponent.h"

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
    void buttonClicked(juce::Button* buttonThatWasClicked) override;

    std::unique_ptr<juce::Label> resFileLabel;
    std::unique_ptr<juce::TextButton> openResFileButton;
    std::unique_ptr<juce::TextEditor> resTextEditor;
    std::unique_ptr<RIFFTableComponent> riffInfoTable;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(RIFFEditorMainComponent)
};
