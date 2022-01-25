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
    return { TRANS("System"), TRANS("Database"), TRANS("Windows"), TRANS("Tools"), TRANS("?Help") };
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
    else if (menuName == TRANS("Tools"))
    {
        juce::StringArray daw;
        SystemHelper::Helper->spotHelper->GetDAWName(daw);
        menu.addItem(401, TRANS("Spot to ProTools"), daw.contains("ProTools"), SystemHelper::Helper->userPerposeSpotDAW == "ProTools");
        menu.addItem(402, TRANS("Spot to Cubase"), daw.contains("Cubase"), SystemHelper::Helper->userPerposeSpotDAW == "Cubase");
        menu.addItem(403, TRANS("Spot to wWise"), daw.contains("wWise"), SystemHelper::Helper->userPerposeSpotDAW == "wWise");
        menu.addSeparator();
        menu.addItem(404, TRANS("Audio Convertor"), false);
        menu.addItem(405, TRANS("RIFF Editor"), false);
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
    case 401: // Tools/Spot/ProTools
        SystemHelper::Helper->userPerposeSpotDAW = "ProTools";
        break;
    case 402: // Tools/Spot/Cubase
        SystemHelper::Helper->userPerposeSpotDAW = "Cubase";
        break;
    case 403: // Tools/Spot/wWise
        SystemHelper::Helper->userPerposeSpotDAW = "wWise";
        break;
    case 404: // Tools/Audio Convertor
        break;
    case 405: // Tools/RIFF Editor
        break;
    default:
        break;
    }
}
