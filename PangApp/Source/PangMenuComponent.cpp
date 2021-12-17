/*
  ==============================================================================

    PangMenuComponent.cpp
    Created: 8 Dec 2021 1:39:49pm
    Author:  庞兴庆

  ==============================================================================
*/

#include <JuceHeader.h>
#include "PangMenuComponent.h"

//==============================================================================
PangMenuComponent::PangMenuComponent()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    menuBarComp.reset(new juce::MenuBarComponent(this));
    addAndMakeVisible(menuBarComp.get());

    setSize(100, 100);
}

PangMenuComponent::~PangMenuComponent()
{
    menuBarComp = nullptr;
}

void PangMenuComponent::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background
}

void PangMenuComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    menuBarComp->setBounds(0, 0, getWidth(), getHeight());
}

juce::StringArray PangMenuComponent::getMenuBarNames()
{
    return { TRANS("System") };
}

juce::PopupMenu PangMenuComponent::getMenuForIndex(int topLevelMenuIndex, const juce::String& menuName)
{
    juce::PopupMenu menu;
    if (menuName == TRANS("System"))
    {
        menu.addItem(101, TRANS("System Settings..."));
    }
    return menu;
}

void PangMenuComponent::menuItemSelected(int menuItemID, int topLevelMenuIndex)
{
    switch (menuItemID)
    {
    case 101:
        OpenSystemSettingsWindow();
    default:
        break;
    }
}

void PangMenuComponent::OpenSystemSettingsWindow()
{
    juce::DialogWindow::LaunchOptions options;
    options.dialogTitle = TRANS("System Settings");
    options.content = juce::OptionalScopedPointer<juce::Component>(new ApplicationSettingComponent(), true);
    auto settingWindow = options.launchAsync();
}
