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

    importFxFromExcelButton.reset(new juce::TextButton("importFxFromExcelButton"));
    addAndMakeVisible(importFxFromExcelButton.get());
    importFxFromExcelButton->setButtonText(TRANS("Import Data From Excel TXT"));
    importFxFromExcelButton->addListener(this);

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

    //helpLabel.reset(new juce::Label("helpLabel", TRANS("* Copy Paste and Cut is enable")));
    //addAndMakeVisible(helpLabel.get());
    //helpLabel->setFont(juce::Font(15.00f, juce::Font::plain).withTypefaceStyle("Regular"));
    //helpLabel->setJustificationType(juce::Justification::centredLeft);
    //helpLabel->setEditable(false, false, false);
    //helpLabel->setColour(juce::TextEditor::textColourId, juce::Colours::black);
    //helpLabel->setColour(juce::TextEditor::backgroundColourId, juce::Colour(0x00000000));

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
    importFxFromExcelButton = nullptr;
    exportFxToExcelButton = nullptr;
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
    addFxButton->setBounds(220, 10, 30, 30);
    deleteFxButton->setBounds(260, 10, 30, 30);

    fxInfosTable->setBounds(10, 50, 200, getHeight() - 40 - 20);
    fxsTable->setBounds(220, 50, getWidth() - 230, getHeight() - 40 * 5 - 20);

    importFxFromExcelButton->setBounds(220, getHeight() - 40 * 4, 200, 30);
    importFxFromFolderButton->setBounds(220, getHeight() - 40 * 3, 200, 30);
    importFxFromDBButton->setBounds(220, getHeight() - 40 * 2, 200, 30);
    exportFXDBButton->setBounds(220, getHeight() - 40 * 1, 200, 30);

    autoCreateThumbnailCheckBox->setBounds(450, getHeight() - 40 * 1, 250, 30);

    // helpLabel->setBounds(10, getHeight() - 30, getWidth(), 30);
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
        fxInfosTable->AddNewFxInfo();
        fxInfosTable->UpdateNewFxDB(newFxDB);
        fxsTable->UpdateNewFxDB(newFxDB);
    }
    else if (buttonThatWasClicked == deleteInfoButton.get())
    {
        fxInfosTable->DeleteNewFxInfoDB();
        fxInfosTable->UpdateNewFxDB(newFxDB);
        fxsTable->UpdateNewFxDB(newFxDB);
    }
    else if (buttonThatWasClicked == addFxButton.get())
    {
        fxsTable->AddNewFx();
        fxsTable->UpdateNewFxDB(newFxDB);
    }
    else if (buttonThatWasClicked == deleteFxButton.get())
    {
        fxsTable->DeleteNewFx();
        fxsTable->UpdateNewFxDB(newFxDB);
    }
    else if (buttonThatWasClicked == importFxFromExcelButton.get())
    {
        chooser = std::make_unique<juce::FileChooser>(TRANS("Open"), juce::File{}, "*.txt");
        auto chooserFlags = juce::FileBrowserComponent::openMode;
        chooser->launchAsync(chooserFlags, [this](const juce::FileChooser& fc)
            {
                auto file = fc.getResult();
                if (file != juce::File{})
                {
                    newFxDB = new FxDB(file, 1, true);
                    fxInfosTable->UpdateNewFxDB(newFxDB);
                    fxsTable->UpdateNewFxDB(newFxDB);
                }
            });
    }
    else if (buttonThatWasClicked == importFxFromDBButton.get())
    {
        chooser = std::make_unique<juce::FileChooser>(TRANS("Open"), juce::File{}, "*.pxml");
        auto chooserFlags = juce::FileBrowserComponent::openMode;
        chooser->launchAsync(chooserFlags, [this](const juce::FileChooser& fc)
            {
                auto file = fc.getResult();
                if (file != juce::File{})
                {
                    newFxDB = new FxDB(file, 1);
                    fxInfosTable->UpdateNewFxDB(newFxDB);
                    fxsTable->UpdateNewFxDB(newFxDB);
                }
            });
    }
    else if (buttonThatWasClicked == importFxFromFolderButton.get())
    {
        chooser = std::make_unique<juce::FileChooser>(TRANS("Open"));
        auto chooserFlags = juce::FileBrowserComponent::canSelectDirectories | juce::FileBrowserComponent::useTreeView;
        chooser->launchAsync(chooserFlags, [this](const juce::FileChooser& fc)
            {
                auto file = fc.getResult();
                if (file != juce::File{} && file.isDirectory())
                {
                    auto audioFiles = file.findChildFiles(file.findFiles, true, "*.wav");
                    for (auto af : audioFiles)
                    {
                        newFxDB->Fxs.push_back(new Fx(af.getFullPathName(), ""));
                    }
                    fxsTable->UpdateNewFxDB(newFxDB);
                }
            });
    }
    else if (buttonThatWasClicked == exportFXDBButton.get())
    {
        chooser = std::make_unique<juce::FileChooser>(TRANS("Save"), juce::File{}, "*.pxml");
        auto chooserFlags = juce::FileBrowserComponent::saveMode;
        chooser->launchAsync(chooserFlags, [this](const juce::FileChooser& fc)
            {
                auto file = fc.getResult();
                if (file != juce::File{})
                {
                    newFxDB->Serialization(file);
                }
            });
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}

void DatabaseEditorMainComponent::labelTextChanged(juce::Label* labelThatHasChanged)
{
    auto label = (DoubleClickedEditableLabel*)labelThatHasChanged;
    if (label != nullptr && label->OwnerType == OwnerTypeEnum::FxInfoTable && fxInfosTable->CheckNewFxInfoDB(label->getText()))
    {
        // New Fx Info
        newFxDB->DBSchema[label->RowNumber]->HeaderName = label->getText();
    }
    else if (label != nullptr && label->OwnerType == OwnerTypeEnum::FxTable)
    {
        // New Fx
        auto fx = newFxDB->Fxs[label->RowNumber];
        auto info = fx->GetInfoValueByColumnID(label->ColumnID);
        if (info == nullptr)
        {
            auto newInfo = std::find_if(newFxDB->DBSchema.begin(), newFxDB->DBSchema.end(), [&](FxInfo* t) { return t->ColumnIndex == label->ColumnID; });
            info = new FxInfo((*newInfo)->ColumnIndex, (*newInfo)->HeaderName, "");
            fx->Infos.push_back(info);
        }
        info->Value = label->getText();
    }
    fxInfosTable->UpdateNewFxDB(newFxDB);
    fxsTable->UpdateNewFxDB(newFxDB);
}