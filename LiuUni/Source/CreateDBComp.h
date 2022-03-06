/*
  ==============================================================================

    CreateDBComp.h
    Created: 6 Mar 2022 7:53:34pm
    Author:  YC

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "CreateDBSourceListBoxModel.h"

//==============================================================================
/*
*/
class CreateDBComp  : public juce::Component, public juce::Button::Listener
{
public:
    CreateDBComp();
    ~CreateDBComp() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:

    juce::Label suffixLabel;
    juce::TextEditor suffixTextEditor;
    juce::TextButton addSourceButton;
    juce::TextButton deleteSourceButton;
    CreateDBSourceListBoxModel sourceListBox;
    juce::TextButton outputPathButton;
    juce::TextEditor outputPathTextEditor;
    juce::TextButton createButton;

    std::unique_ptr<juce::FileChooser> chooser;

    // Í¨¹ý Listener ¼Ì³Ð
    virtual void buttonClicked(juce::Button* btn) override;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CreateDBComp)
};
