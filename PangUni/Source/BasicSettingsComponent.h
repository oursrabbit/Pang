#pragma once

#include <JuceHeader.h>
//==============================================================================
/*
*/
class BasicSettingsComponent : public juce::Component,
    public juce::Button::Listener,
    public juce::ComboBox::Listener,
    public juce::TextEditor::Listener
{
public:

    BasicSettingsComponent();
    ~BasicSettingsComponent() override;

    void paint(juce::Graphics&) override;
    void resized() override;

    std::function<void()> OnValueChanged;

    std::unique_ptr<juce::Label> languageLabel;
    int languageLabelWidth;
    std::unique_ptr<juce::ComboBox> languageComboBox;

    std::unique_ptr<juce::Label> appdataBasePathLabel;
    int appdataBasePathLabelWidth;
    std::unique_ptr<juce::TextEditor> appdataBasePathTextEditor;
    std::unique_ptr<juce::TextButton> openAppdataBasePathButton;

    std::unique_ptr<juce::ToggleButton> alwaysAutoTranslateToggleButton;
    std::unique_ptr<juce::Label> alwaysAutoTranslateLabel;

    std::unique_ptr<juce::FileChooser> chooser;

    void SetDefaultComponentValue();

    virtual void buttonClicked(juce::Button* button) override;
    virtual void textEditorTextChanged(juce::TextEditor& textEditor) override;
    virtual void comboBoxChanged(juce::ComboBox* comboBoxThatHasChanged) override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(BasicSettingsComponent)
};
