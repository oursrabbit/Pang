/*
  ==============================================================================

    ApplicationSettingComponent.cpp
    Created: 10 Dec 2021 10:43:17am
    Author:  YC

  ==============================================================================
*/

#include <JuceHeader.h>
#include "ApplicationSettingComponent.h"
#include "BaiduAIHelper.h"
#include "SystemSettingsHelper.h"
#include "TranslateHelper.h"

//==============================================================================
ApplicationSettingComponent::ApplicationSettingComponent()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

    saveButton.reset(new juce::TextButton("Save Button"));
    saveButton->setButtonText(TRANS("Save"));
    saveButton->setEnabled(false);
    saveButton->addListener(this);
    addAndMakeVisible(saveButton.get());

    cancelButton.reset(new juce::TextButton("Cancel Button"));
    cancelButton->setButtonText(TRANS("Cancel"));
    cancelButton->addListener(this);
    addAndMakeVisible(cancelButton.get());

    closeButton.reset(new juce::TextButton("Close Button"));
    closeButton->setButtonText(TRANS("Close"));
    closeButton->addListener(this);
    addAndMakeVisible(closeButton.get());

    languageLabel.reset(new juce::Label("Language Label", TRANS("Language:")));
    addAndMakeVisible(languageLabel.get());
    languageLabelWidth = juce::LookAndFeel::getDefaultLookAndFeel().getLabelFont(*languageLabel.get()).getStringWidth(TRANS("Language:"));

    languageComboBox.reset(new juce::ComboBox());
    addAndMakeVisible(languageComboBox.get());
    languageComboBox->addListener(this);

    appdataBasePathLabel.reset(new juce::Label("AppData Label", TRANS("Application Database:")));
    addAndMakeVisible(appdataBasePathLabel.get());
    appdataBasePathLabelWidth = juce::LookAndFeel::getDefaultLookAndFeel().getLabelFont(*appdataBasePathLabel.get()).getStringWidth(TRANS("Applicaion Database:"));

    appdataBasePathTextEditor.reset(new juce::TextEditor("AppData TextEditor"));
    addAndMakeVisible(appdataBasePathTextEditor.get());
    appdataBasePathTextEditor->addListener(this);

    alwaysAutoTranslateToggleButton.reset(new juce::ToggleButton(""));
    alwaysAutoTranslateLabel.reset(new juce::Label("alwaysAutoTranslateLabel", TRANS("Always auto-translate keywords to chinese. (By Baidu AI)")));
    if (BaiduAIHelper::GetAccess_Token() != "")
    {
        addAndMakeVisible(alwaysAutoTranslateToggleButton.get());
        alwaysAutoTranslateToggleButton->addListener(this);
        addAndMakeVisible(alwaysAutoTranslateLabel.get());
    }

    setSize(400, 400);

    SetDefaultComponentValue();
}

ApplicationSettingComponent::~ApplicationSettingComponent()
{
    saveButton = nullptr;
    cancelButton = nullptr;
    closeButton = nullptr;

    languageLabel = nullptr;
    languageComboBox = nullptr;
    appdataBasePathLabel = nullptr;
    appdataBasePathTextEditor = nullptr;

    alwaysAutoTranslateToggleButton = nullptr;
    alwaysAutoTranslateLabel = nullptr;
}

void ApplicationSettingComponent::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background
}

void ApplicationSettingComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    languageLabel->setBounds(10, 10, languageLabelWidth, 30);
    languageComboBox->setBounds(10 + languageLabelWidth + 10, 10, getWidth() - 10 - languageLabelWidth - 10 - 10, 30);
    appdataBasePathLabel->setBounds(10, 10 + 30 + 10, appdataBasePathLabelWidth, 30);
    appdataBasePathTextEditor->setBounds(10 + appdataBasePathLabelWidth + 10, 10 + 30 + 10, getWidth() - 10 - appdataBasePathLabelWidth - 10 - 10, 30);
    alwaysAutoTranslateToggleButton->setBounds(10, 10 + 30 + 10 + 30 + 10, 25, 30);
    alwaysAutoTranslateLabel->setBounds(10 + 25, 10 + 30 + 10 + 30 + 10, getWidth() - 10 - 25 - 10 - 10, 30);
    closeButton->setBounds(getWidth() - 10 - 100, getHeight() - 10 - 30, 100, 30);
    cancelButton->setBounds(getWidth() - 10 - 100 - 10 - 100, getHeight() - 10 - 30, 100, 30);
    saveButton->setBounds(getWidth() - 10 - 100 - 10 - 100 - 10 - 100, getHeight() - 10 - 30, 100, 30);
}
void ApplicationSettingComponent::SetDefaultComponentValue()
{
    languageComboBox->clear(juce::NotificationType::dontSendNotification);
    for(auto language : TranslateHelper::GetAllLanguage())
    {
        languageComboBox->addItem(TRANS(language), TranslateHelper::GetIDByLanguage(language));
    }
    languageComboBox->setSelectedId(TranslateHelper::GetIDByLanguage(SystemSettingsHelper::GetLanguage()), juce::NotificationType::dontSendNotification);
    appdataBasePathTextEditor->setText(SystemSettingsHelper::GetAppDataBasePath(), false);
    alwaysAutoTranslateToggleButton->setToggleState(SystemSettingsHelper::GetAutoTranslate(), juce::NotificationType::dontSendNotification);
}

void ApplicationSettingComponent::buttonClicked(juce::Button* button)
{
    if (button == saveButton.get())
    {
        SystemSettingsHelper::SetLanguage(TranslateHelper::GetLanguageByID(languageComboBox->getSelectedId()));
        SystemSettingsHelper::SetAppDataBasePath(appdataBasePathTextEditor->getText());
        SystemSettingsHelper::SetAutoTranslate(alwaysAutoTranslateToggleButton->getToggleState());
        saveButton->setEnabled(false);
        juce::AlertWindow::showMessageBoxAsync(juce::MessageBoxIconType::InfoIcon
            , TRANS("Message"), TRANS("Restart applicaiton to reload settings."));
    }
    else if (button == cancelButton.get() || button == closeButton.get())
    {
        findParentComponentOfClass<juce::DialogWindow>()->exitModalState(0);
    }
    else if (button == alwaysAutoTranslateToggleButton.get())
    {
        saveButton->setEnabled(true);
    }
}

void ApplicationSettingComponent::comboBoxChanged(juce::ComboBox*)
{
    saveButton->setEnabled(true);
}

void ApplicationSettingComponent::textEditorTextChanged(juce::TextEditor&)
{
    saveButton->setEnabled(true);
}
