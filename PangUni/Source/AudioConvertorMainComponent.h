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
class AudioConvertorMainComponent : public juce::Component,
    public juce::ComboBox::Listener,
    public juce::Button::Listener
{
public:
    AudioConvertorMainComponent();
    ~AudioConvertorMainComponent() override;

    void paint(juce::Graphics&) override;
    void resized() override;
    void comboBoxChanged(juce::ComboBox* comboBoxThatHasChanged) override;
    void buttonClicked(juce::Button* buttonThatWasClicked) override;

    std::unique_ptr<juce::GroupComponent> desFileGroup;
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
    std::unique_ptr<juce::Label> resFileLabel;
    std::unique_ptr<juce::TextButton> openResFileButton;
    std::unique_ptr<juce::TextEditor> resTextEditor;
    std::unique_ptr<juce::TextButton> convertButton;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AudioConvertorMainComponent)
};
