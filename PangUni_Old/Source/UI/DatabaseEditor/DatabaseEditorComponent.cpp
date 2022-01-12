#include "DatabaseEditorComponent.h"

//==============================================================================
DatabaseEditorComponent::DatabaseEditorComponent()
{
    addAndMakeVisible(fxTable);
    fxTable.fxInfoTable = &fxInfoTable;
    fxTable.newFxDB = &newFxDB;
    addAndMakeVisible(fxInfoTable);
    fxInfoTable.fxTable = &fxTable;
    fxInfoTable.newFxDB = &newFxDB;

    addFxButton.setButtonText("+");
    addFxButtonWidth = juce::LookAndFeel::getDefaultLookAndFeel().getTextButtonWidthToFitText(addFxButton, 30);
    addFxButton.addListener(this);
    addAndMakeVisible(addFxButton);

    deleteFxButton.setButtonText("-");
    deleteFxButtonWidth = juce::LookAndFeel::getDefaultLookAndFeel().getTextButtonWidthToFitText(deleteFxButton, 30);
    deleteFxButton.addListener(this);
    addAndMakeVisible(deleteFxButton);

    addCustomInfoButton.setButtonText("+");
    addCustomInfoButtonWidth = juce::LookAndFeel::getDefaultLookAndFeel().getTextButtonWidthToFitText(addCustomInfoButton, 30);
    addCustomInfoButton.addListener(this);
    addAndMakeVisible(addCustomInfoButton);

    deleteCustomInfoButton.setButtonText("-");
    deleteCustomInfoButtonWidth = juce::LookAndFeel::getDefaultLookAndFeel().getTextButtonWidthToFitText(deleteCustomInfoButton, 30);
    deleteCustomInfoButton.addListener(this);
    addAndMakeVisible(deleteCustomInfoButton);

    openDBButton.setButtonText(TRANS("Open Fxs Database"));
    openDBButtonWidth = juce::LookAndFeel::getDefaultLookAndFeel().getTextButtonWidthToFitText(openDBButton, 30);
    openDBButton.addListener(this);
    addAndMakeVisible(openDBButton);

    openDBFolderButton.setButtonText(TRANS("Open Fxs Folder"));
    openDBFolderButtonWidth = juce::LookAndFeel::getDefaultLookAndFeel().getTextButtonWidthToFitText(openDBFolderButton, 30);
    openDBFolderButton.addListener(this);
    addAndMakeVisible(openDBFolderButton);

    saveDBButton.setButtonText(TRANS("Export Fxs Database"));
    saveDBButtonWidth = juce::LookAndFeel::getDefaultLookAndFeel().getTextButtonWidthToFitText(saveDBButton, 30);
    saveDBButton.addListener(this);
    addAndMakeVisible(saveDBButton);

    setSize(600, 400);
}

DatabaseEditorComponent::~DatabaseEditorComponent()
{
}

//==============================================================================
void DatabaseEditorComponent::paint (juce::Graphics&)
{
}

void DatabaseEditorComponent::resized()
{
    fxInfoTable.setBounds(0, 40, 200, getHeight() - 80);
    fxTable.setBounds(210, 40, getWidth() - 210, getHeight() - 80);

    addCustomInfoButton.setBounds(0, 0, addCustomInfoButtonWidth, 30);
    deleteCustomInfoButton.setBounds(addFxButtonWidth + 10, 0, deleteCustomInfoButtonWidth, 30);

    addFxButton.setBounds(210, 0, addFxButtonWidth, 30);
    deleteFxButton.setBounds(210 + addFxButtonWidth + 10, 0, deleteFxButtonWidth, 30);
    

    openDBButton.setBounds(getWidth() - openDBButtonWidth, getHeight() - 30, openDBButtonWidth, 30);
    openDBFolderButton.setBounds(getWidth() - openDBButtonWidth - 10 - openDBFolderButtonWidth, getHeight() - 30, openDBFolderButtonWidth, 30);
    saveDBButton.setBounds(getWidth() - openDBButtonWidth - 10 - openDBFolderButtonWidth - 10 - saveDBButtonWidth, getHeight() - 30, saveDBButtonWidth, 30);
}

void DatabaseEditorComponent::buttonClicked(juce::Button* btn)
{
    if (btn == &addFxButton)
    {
        fxTable.addFx();
    }
    else if (btn == &deleteFxButton)
    {
        fxTable.deleteFx();
    }
    else if (btn == &addCustomInfoButton)
    {
        fxInfoTable.addFxInfo();
    }
    else if (btn == &deleteCustomInfoButton)
    {
        fxInfoTable.deleteFxInfo();
    }
    else if (btn == &saveDBButton)
    {
        //table.exportFxDB();
    }
    else if (btn == &openDBFolderButton)
    {
        //table.openFxDBFolder();
    }
    else if (btn == &openDBButton)
    {
        //table.openFxDB();
    }
}
