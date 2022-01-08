#include "DatabaseEditorComponent.h"

//==============================================================================
DatabaseEditorComponent::DatabaseEditorComponent()
{
    addAndMakeVisible(table);

    addFxButton.setButtonText(TRANS("Add Fx"));
    addFxButtonWidth = juce::LookAndFeel::getDefaultLookAndFeel().getTextButtonWidthToFitText(addFxButton, 30);
    addFxButton.addListener(this);
    addAndMakeVisible(addFxButton);

    deleteFxButton.setButtonText(TRANS("Delete Selected Fx"));
    deleteFxButtonWidth = juce::LookAndFeel::getDefaultLookAndFeel().getTextButtonWidthToFitText(deleteFxButton, 30);
    deleteFxButton.addListener(this);
    addAndMakeVisible(deleteFxButton);

    addCustomInfoButton.setButtonText(TRANS("Add Custom Info"));
    addCustomInfoButtonWidth = juce::LookAndFeel::getDefaultLookAndFeel().getTextButtonWidthToFitText(addCustomInfoButton, 30);
    addCustomInfoButton.addListener(this);
    addAndMakeVisible(addCustomInfoButton);

    deleteCustomInfoButton.setButtonText(TRANS("Delete Custom Info"));
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
    table.setBounds(0, 40, getWidth(), getHeight() - 80);

    addFxButton.setBounds(0, 0, addFxButtonWidth, 30);
    deleteFxButton.setBounds(addFxButtonWidth + 10, 0, deleteFxButtonWidth, 30);
    addCustomInfoButton.setBounds(addFxButtonWidth + 10 + deleteFxButtonWidth + 10, 0, addCustomInfoButtonWidth, 30);
    deleteCustomInfoButton.setBounds(addFxButtonWidth + 10 + deleteFxButtonWidth + 10 + addCustomInfoButtonWidth + 10, 0, deleteCustomInfoButtonWidth, 30);

    openDBButton.setBounds(getWidth() - openDBButtonWidth, getHeight() - 30, openDBButtonWidth, 30);
    openDBFolderButton.setBounds(getWidth() - openDBButtonWidth - 10 - openDBFolderButtonWidth, getHeight() - 30, openDBFolderButtonWidth, 30);
    saveDBButton.setBounds(getWidth() - openDBButtonWidth - 10 - openDBFolderButtonWidth - 10 - saveDBButtonWidth, getHeight() - 30, saveDBButtonWidth, 30);
}

void DatabaseEditorComponent::buttonClicked(juce::Button* btn)
{
    if (btn == &addFxButton)
    {
        table.addFx();
    }
    else if (btn == &deleteFxButton)
    {
        table.deleteFx();
    }
    else if (btn == &addCustomInfoButton)
    {
        table.addFxInfo();
    }
    else if (btn == &deleteCustomInfoButton)
    {
        table.deleteFxInfo();
    }
}
