#pragma once

#include <JuceHeader.h>

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
    void OpenDatabaseEditorWindow();

    virtual juce::StringArray getMenuBarNames() override;
    virtual juce::PopupMenu getMenuForIndex(int topLevelMenuIndex, const juce::String& menuName) override;
    virtual void menuItemSelected(int menuItemID, int topLevelMenuIndex) override;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PangMenuComponent)
};
