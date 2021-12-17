/*
  ==============================================================================

    PangMenuComponent.h
    Created: 8 Dec 2021 1:39:49pm
    Author:  庞兴庆

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "DatabaseHelper.h"
#include "ApplicationSettingComponent.h"

//==============================================================================
/*
*/
class PangMenuComponent  : public juce::Component,
                           public juce::MenuBarModel
{
public:
    PangMenuComponent();
    ~PangMenuComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    std::unique_ptr<juce::MenuBarComponent> menuBarComp;

    void OpenSystemSettingsWindow();

    virtual juce::StringArray getMenuBarNames() override;
    virtual juce::PopupMenu getMenuForIndex(int topLevelMenuIndex, const juce::String& menuName) override;
    virtual void menuItemSelected(int menuItemID, int topLevelMenuIndex) override;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PangMenuComponent)
};
