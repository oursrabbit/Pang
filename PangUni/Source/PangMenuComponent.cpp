#include <JuceHeader.h>
#include "PangMenuComponent.h"
#include "SystemHelper.h"

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
    return { TRANS("System"), TRANS("Database"), TRANS("Windows"), TRANS("Spot Tool"), TRANS("Help") };
}

juce::PopupMenu PangMenuComponent::getMenuForIndex(int, const juce::String& menuName)
{
    juce::PopupMenu menu;
    if (menuName == TRANS("System"))
    {
        menu.addItem(101, TRANS("Open System Settings Window"));
    }
    else if (menuName == TRANS("Database"))
    {
        menu.addItem(201, TRANS("New Database Editor Window"));
    }
    else if (menuName == TRANS("Windows"))
    {
        menu.addItem(301, TRANS("New Search Window"));
    }
    return menu;
}

void PangMenuComponent::menuItemSelected(int menuItemID, int)
{
    switch (menuItemID)
    {
    case 101: // System/System Settings...
        SystemHelper::Helper->OpenSystemSettingsWindow();
        break;
    case 201: // Database/Edit Database
        SystemHelper::Helper->OpenDatabaseEditorWindow();
        break;
    case 301: // Windows/New Search Window
        SystemHelper::Helper->OpenMainWindow();
        break;
    default:
        break;
    }
}
