/*
  ==============================================================================

    DatabaseEditorMainComponent.cpp
    Created: 11 Jan 2022 5:48:32pm
    Author:  YC

  ==============================================================================
*/

#include <JuceHeader.h>
#include "DatabaseEditorMainComponent.h"

//==============================================================================
DatabaseEditorMainComponent::DatabaseEditorMainComponent()
{
    setSize(1000, 800);
}

DatabaseEditorMainComponent::DatabaseEditorMainComponent(FxDB* newFxDB)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    this->newFxDB = newFxDB;

    autoCreateThumbnailCheckBox.reset(new juce::ToggleButton("autoCreateThumbnailCheckBox"));
    addAndMakeVisible(autoCreateThumbnailCheckBox.get());
    autoCreateThumbnailCheckBox->setButtonText(TRANS("Auto Create Thumbnail"));
    autoCreateThumbnailCheckBox->setToggleState(true, juce::NotificationType::dontSendNotification);
    autoCreateThumbnailCheckBox->addListener(this);

    fxInfosTable.reset(new FxInfoTableModel(newFxDB, this));
    addAndMakeVisible(fxInfosTable.get());
    fxInfosTable->setName("fxInfosTable");

    fxsTable.reset(new FxTableModel(newFxDB, this));
    addAndMakeVisible(fxsTable.get());
    fxsTable->setName("fxsTable");

    addInfoButton.reset(new juce::TextButton("addInfoButton"));
    addAndMakeVisible(addInfoButton.get());
    addInfoButton->setButtonText(TRANS("+"));
    addInfoButton->addListener(this);

    deleteInfoButton.reset(new juce::TextButton("deleteInfoButton"));
    addAndMakeVisible(deleteInfoButton.get());
    deleteInfoButton->setButtonText(TRANS("-"));
    deleteInfoButton->addListener(this);

    addFxButton.reset(new juce::TextButton("addFxButton"));
    addAndMakeVisible(addFxButton.get());
    addFxButton->setButtonText(TRANS("+"));
    addFxButton->addListener(this);

    deleteFxButton.reset(new juce::TextButton("deleteFxButton"));
    addAndMakeVisible(deleteFxButton.get());
    deleteFxButton->setButtonText(TRANS("-"));
    deleteFxButton->addListener(this);

    importInfoSchemaButton.reset(new juce::TextButton("importInfoSchemaButton"));
    addAndMakeVisible(importInfoSchemaButton.get());
    importInfoSchemaButton->setButtonText(TRANS("Import Schema From File"));
    importInfoSchemaButton->addListener(this);

    exportInfoSchemaButton.reset(new juce::TextButton("exportInfoSchemaButton"));
    addAndMakeVisible(exportInfoSchemaButton.get());
    exportInfoSchemaButton->setButtonText(TRANS("Export Schema to Disk"));
    exportInfoSchemaButton->addListener(this);

    importFxFromDBButton.reset(new juce::TextButton("importFxFromDBButton"));
    addAndMakeVisible(importFxFromDBButton.get());
    importFxFromDBButton->setButtonText(TRANS("Import Data From File"));
    importFxFromDBButton->addListener(this);

    exportFXDBButton.reset(new juce::TextButton("exportFXDBButton"));
    addAndMakeVisible(exportFXDBButton.get());
    exportFXDBButton->setButtonText(TRANS("Export Data to Disk"));
    exportFXDBButton->addListener(this);

    importFxFromFolderButton.reset(new juce::TextButton("importFxFromFolderButton"));
    addAndMakeVisible(importFxFromFolderButton.get());
    importFxFromFolderButton->setButtonText(TRANS("Import Data From Audio Folder"));
    importFxFromFolderButton->addListener(this);

    helpLabel.reset(new juce::Label("helpLabel", TRANS("* Copy Paste and Cut is enable")));
    addAndMakeVisible(helpLabel.get());
    helpLabel->setFont(juce::Font(15.00f, juce::Font::plain).withTypefaceStyle("Regular"));
    helpLabel->setJustificationType(juce::Justification::centredLeft);
    helpLabel->setEditable(false, false, false);
    helpLabel->setColour(juce::TextEditor::textColourId, juce::Colours::black);
    helpLabel->setColour(juce::TextEditor::backgroundColourId, juce::Colour(0x00000000));

    setSize(1000, 600);
}

DatabaseEditorMainComponent::~DatabaseEditorMainComponent()
{
    autoCreateThumbnailCheckBox = nullptr;
    fxInfosTable = nullptr;
    fxsTable = nullptr;
    addInfoButton = nullptr;
    deleteInfoButton = nullptr;
    addFxButton = nullptr;
    deleteFxButton = nullptr;
    importInfoSchemaButton = nullptr;
    exportInfoSchemaButton = nullptr;
    importFxFromDBButton = nullptr;
    exportFXDBButton = nullptr;
    importFxFromFolderButton = nullptr;
    helpLabel = nullptr;
}

void DatabaseEditorMainComponent::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background
}

void DatabaseEditorMainComponent::resized()
{
    addInfoButton->setBounds(10, 10, 30, 30);
    deleteInfoButton->setBounds(50, 10, 30, 30);
    addFxButton->setBounds(420, 10, 30, 30);
    deleteFxButton->setBounds(460, 10, 30, 30);

    fxInfosTable->setBounds(10, 50, 200, getHeight() - 40 * 5 - 20);
    fxsTable->setBounds(220, 50, getWidth() - 230, getHeight() - 40 * 5 - 20);

    importInfoSchemaButton->setBounds(10, getHeight() - 40 * 4, 200, 30);
    exportInfoSchemaButton->setBounds(10, getHeight() - 40 * 3, 200, 30);

    importFxFromFolderButton->setBounds(220, getHeight() - 40 * 4, 200, 30);
    importFxFromDBButton->setBounds(220, getHeight() - 40 * 3, 200, 30);
    exportFXDBButton->setBounds(220, getHeight() - 40 * 2, 200, 30);

    autoCreateThumbnailCheckBox->setBounds(450, getHeight() - 40 * 2, 250, 30);

    helpLabel->setBounds(10, getHeight() - 30, getWidth(), 30);
}

void DatabaseEditorMainComponent::buttonClicked(juce::Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == autoCreateThumbnailCheckBox.get())
    {
        //[UserButtonCode_autoCreateThumbnailCheckBox] -- add your button handler code here..
        //[/UserButtonCode_autoCreateThumbnailCheckBox]
    }
    else if (buttonThatWasClicked == addInfoButton.get())
    {
        fxInfosTable->AddNewFxInfoDB();
        fxInfosTable->UpdateNewFxDB();
        fxsTable->UpdateNewFxDB();
    }
    else if (buttonThatWasClicked == deleteInfoButton.get())
    {
        fxInfosTable->DeleteNewFxInfoDB();
        fxInfosTable->UpdateNewFxDB();
        fxsTable->UpdateNewFxDB();
    }
    else if (buttonThatWasClicked == addFxButton.get())
    {
        //[UserButtonCode_addFxButton] -- add your button handler code here..
        //[/UserButtonCode_addFxButton]
    }
    else if (buttonThatWasClicked == deleteFxButton.get())
    {
        //[UserButtonCode_deleteFxButton] -- add your button handler code here..
        //[/UserButtonCode_deleteFxButton]
    }
    else if (buttonThatWasClicked == importInfoSchemaButton.get())
    {
        //[UserButtonCode_importInfoSchemaButton] -- add your button handler code here..
        //[/UserButtonCode_importInfoSchemaButton]
    }
    else if (buttonThatWasClicked == exportInfoSchemaButton.get())
    {
        //[UserButtonCode_exportInfoSchemaButton] -- add your button handler code here..
        //[/UserButtonCode_exportInfoSchemaButton]
    }
    else if (buttonThatWasClicked == importFxFromDBButton.get())
    {
        //[UserButtonCode_importFxFromDBButton] -- add your button handler code here..
        //[/UserButtonCode_importFxFromDBButton]
    }
    else if (buttonThatWasClicked == exportFXDBButton.get())
    {
        //[UserButtonCode_exportFXDBButton] -- add your button handler code here..
        //[/UserButtonCode_exportFXDBButton]
    }
    else if (buttonThatWasClicked == importFxFromFolderButton.get())
    {
        //[UserButtonCode_importFxFromFolderButton] -- add your button handler code here..
        //[/UserButtonCode_importFxFromFolderButton]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}

void DatabaseEditorMainComponent::labelTextChanged(juce::Label* labelThatHasChanged)
{
    auto label = (DoubleClickedEditableLabel*)labelThatHasChanged;
    if (label != nullptr && label->OwnerType == OwnerTypeEnum::FxInfoTable && fxInfosTable->CheckNewFxInfoDB(label->getText()))
    {
        newFxDB->DBSchema[label->RowNumber]->HeaderName = label->getText();
    }
    fxInfosTable->UpdateNewFxDB();
    fxsTable->UpdateNewFxDB();
}