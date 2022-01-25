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
class SpotSettingsComponent  : public juce::Component, public juce::ComboBox::Listener,public juce::Button::Listener, public juce::TextEditor::Listener
{
public:
    std::function<void()> OnValueChanged;

    SpotSettingsComponent();
    ~SpotSettingsComponent() override;

    void SetValue();

    void saveToPXML();

    void paint (juce::Graphics&) override;
    void resized() override;
    void comboBoxChanged(juce::ComboBox* comboBoxThatHasChanged) override;
    void buttonClicked(juce::Button* buttonThatWasClicked) override;
    virtual void textEditorTextChanged(juce::TextEditor& textEditor) override;


    std::unique_ptr<juce::FileChooser> chooser;

    std::unique_ptr<juce::ComboBox> samplerateComboBox;
    std::unique_ptr<juce::ComboBox> bitDepthComboBox;
    std::unique_ptr<juce::TextEditor> outputTextEditor;
    std::unique_ptr<juce::ComboBox> resampleComboBox;
    std::unique_ptr<juce::ComboBox> channelsComboBox;
    std::unique_ptr<juce::Label> sampleRateLabel;
    std::unique_ptr<juce::Label> bitDepthLabel;
    std::unique_ptr<juce::Label> channelsLabel;
    std::unique_ptr<juce::Label> outputLabel;
    std::unique_ptr<juce::Label> resampleLabel;
    std::unique_ptr<juce::TextButton> outputButton;
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SpotSettingsComponent)
};
