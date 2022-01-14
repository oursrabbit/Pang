/*
  ==============================================================================

    ApplicationSettingComponent.cpp
    Created: 10 Dec 2021 10:43:17am
    Author:  YC

  ==============================================================================
*/

#include <JuceHeader.h>
#include "SystemSettingsComponent.h"


//==============================================================================
SystemSettingsComponent::SystemSettingsComponent()
{
    basicSettingsComp.reset(new BasicSettingsComponent());
    basicSettingsComp->OnValueChanged = [this]() {saveButton->setEnabled(true); };

    spotSettingComp.reset(new SpotSettingsComponent());
    spotSettingComp->OnValueChanged = [this]() {saveButton->setEnabled(true); };

    tabsComp.reset(new juce::TabbedComponent(juce::TabbedButtonBar::Orientation::TabsAtTop));
    addAndMakeVisible(tabsComp.get());

    auto bkc = getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId);
    tabsComp->addTab("Basic", bkc, basicSettingsComp.get(), false, -1);
    tabsComp->addTab("Spot", bkc, spotSettingComp.get(), false, -1);

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

    setSize(1000, 600);
}

SystemSettingsComponent::~SystemSettingsComponent()
{
    saveButton = nullptr;
    cancelButton = nullptr;
    closeButton = nullptr;

    spotSettingComp = nullptr;
    basicSettingsComp = nullptr;
    tabsComp = nullptr;
}

void SystemSettingsComponent::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background
}

void SystemSettingsComponent::resized()
{
    tabsComp->setBounds(0, 0, getWidth(), getHeight() - 50);
    closeButton->setBounds(getWidth() - 110 * 1, getHeight() - 40, 100, 30);
    cancelButton->setBounds(getWidth() - 110 * 2, getHeight() - 40, 100, 30);
    saveButton->setBounds(getWidth() - 110 * 3, getHeight() - 40, 100, 30);
}

void SystemSettingsComponent::buttonClicked(juce::Button* button)
{
    if (button == saveButton.get())
    {
        //SystemSettingsHelper::SetLanguage(TranslateHelper::GetLanguageByID(languageComboBox->getSelectedId()));
        //SystemSettingsHelper::SetAppDataBasePath(appdataBasePathTextEditor->getText());
        //SystemSettingsHelper::SetAutoTranslate(alwaysAutoTranslateToggleButton->getToggleState());
        saveButton->setEnabled(false);
        juce::AlertWindow::showMessageBoxAsync(juce::MessageBoxIconType::InfoIcon
            , TRANS("Message"), TRANS("Restart applicaiton to reload settings."));
    }
    else if (button == cancelButton.get() || button == closeButton.get())
    {
        getParentComponent()->setVisible(false);
    }
}