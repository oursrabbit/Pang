/*
  ==============================================================================

    ApplicationSettingComponent.cpp
    Created: 10 Dec 2021 10:43:17am
    Author:  YC

  ==============================================================================
*/

#include <JuceHeader.h>
#include "BasicSettingsComponent.h"
//#include "../../Utilities/DatabaseHelper.h"
//#include "../../Utilities/BaiduAI/BaiduAIHelper.h"
//#include "../../Utilities/SystemSettingsHelper.h"
//#include "../../Utilities/TranslateHelper.h"

//==============================================================================
BasicSettingsComponent::BasicSettingsComponent()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

    OnValueChanged = []() {};

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

    openAppdataBasePathButton.reset(new juce::TextButton("..."));
    addAndMakeVisible(openAppdataBasePathButton.get());
    openAppdataBasePathButton->setButtonText("...");
    openAppdataBasePathButton->addListener(this);

    alwaysAutoTranslateToggleButton.reset(new juce::ToggleButton(""));
    alwaysAutoTranslateLabel.reset(new juce::Label("alwaysAutoTranslateLabel", TRANS("Always auto-translate keywords to chinese. (By Baidu AI)")));
    //if (BaiduAIHelper::GetAccess_Token() != "")
    //{
    //    addAndMakeVisible(alwaysAutoTranslateToggleButton.get());
    //    alwaysAutoTranslateToggleButton->addListener(this);
    //    addAndMakeVisible(alwaysAutoTranslateLabel.get());
    //}

    setSize(1000, 600);

    SetDefaultComponentValue();
}

BasicSettingsComponent::~BasicSettingsComponent()
{
    languageLabel = nullptr;
    languageComboBox = nullptr;
    appdataBasePathLabel = nullptr;
    appdataBasePathTextEditor = nullptr;
    openAppdataBasePathButton = nullptr;
    alwaysAutoTranslateToggleButton = nullptr;
    alwaysAutoTranslateLabel = nullptr;
}

void BasicSettingsComponent::paint(juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));   // clear the background
}

void BasicSettingsComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    languageLabel->setBounds(10, 10, languageLabelWidth, 30);
    languageComboBox->setBounds(10 + languageLabelWidth + 10, 10, getWidth() - 10 - languageLabelWidth - 10 - 10, 30);
    appdataBasePathLabel->setBounds(10, 10 + 30 + 10, appdataBasePathLabelWidth, 30);
    appdataBasePathTextEditor->setBounds(10 + appdataBasePathLabelWidth + 10, 10 + 30 + 10, getWidth() - 10 - appdataBasePathLabelWidth - 10 - 10 - 60, 30);
    openAppdataBasePathButton->setBounds(getWidth() - 60, 10 + 30 + 10, 50, 30);
    alwaysAutoTranslateToggleButton->setBounds(10, 10 + 30 + 10 + 30 + 10, 25, 30);
    alwaysAutoTranslateLabel->setBounds(10 + 25, 10 + 30 + 10 + 30 + 10, getWidth() - 10 - 25 - 10 - 10, 30);
}
void BasicSettingsComponent::SetDefaultComponentValue()
{
    //languageComboBox->clear(juce::NotificationType::dontSendNotification);
    //for(auto language : TranslateHelper::GetAllLanguage())
    //{
    //    languageComboBox->addItem(TRANS(language), TranslateHelper::GetIDByLanguage(language));
    //}
    //languageComboBox->setSelectedId(TranslateHelper::GetIDByLanguage(SystemSettingsHelper::GetLanguage()), juce::NotificationType::dontSendNotification);
    //
    //appdataBasePathTextEditor->setText(SystemSettingsHelper::GetAppDataBasePath(), false);
    //alwaysAutoTranslateToggleButton->setToggleState(SystemSettingsHelper::GetAutoTranslate(), juce::NotificationType::dontSendNotification);
}

void BasicSettingsComponent::buttonClicked(juce::Button* button)
{
    if (button == openAppdataBasePathButton.get())
    {
        chooser = std::make_unique<juce::FileChooser>(TRANS("Open"));
        auto chooserFlags = juce::FileBrowserComponent::canSelectDirectories | juce::FileBrowserComponent::useTreeView;
        chooser->launchAsync(chooserFlags, [this](const juce::FileChooser& fc)
            {
                auto file = fc.getResult();
                if (file != juce::File{} && file.isDirectory())
                {
                    appdataBasePathTextEditor->setText(file.getFullPathName());
                }
            });
    }
}

void BasicSettingsComponent::comboBoxChanged(juce::ComboBox*)
{
    OnValueChanged();
}

void BasicSettingsComponent::textEditorTextChanged(juce::TextEditor&)
{
    OnValueChanged();
}
