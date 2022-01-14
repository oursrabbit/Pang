#pragma once

#include <JuceHeader.h>
#include "BasicSettingsComponent.h"
#include "SpotSettingsComponent.h"

class SystemSettingsComponent : public juce::Component,public juce::Button::Listener
{
public:
    SystemSettingsComponent();
    ~SystemSettingsComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    std::unique_ptr<juce::TabbedComponent> tabsComp;
    std::unique_ptr<BasicSettingsComponent> basicSettingsComp;
    std::unique_ptr<SpotSettingsComponent> spotSettingComp;
    std::unique_ptr<juce::TextButton> saveButton;
    std::unique_ptr<juce::TextButton> cancelButton;
    std::unique_ptr<juce::TextButton> closeButton;

    virtual void buttonClicked(juce::Button* button) override;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SystemSettingsComponent)
};
