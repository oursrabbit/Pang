#include "AudioSearchComponent.h"
#include "BaiduAIHelper.h"
#include "SystemSettingsHelper.h"
#include "DatabaseHelper.h"

//==============================================================================
AudioSearchComponent::AudioSearchComponent()
{
    keywordsLabel.reset(new juce::Label("keywordsLabel", TRANS("Input Key Words:(Separate by escape)")));
    addAndMakeVisible(keywordsLabel.get());

    keywordsTextEditor.reset(new juce::TextEditor("keywordsTextEditor"));
    addAndMakeVisible(keywordsTextEditor.get());

    searchButton.reset(new juce::TextButton("searchButton"));
    addAndMakeVisible(searchButton.get());
    searchButton->setButtonText(TRANS("Search"));
    searchButton->addListener(this);

    resetKeywordsButton.reset(new juce::TextButton("resetKeywordsButton"));
    addAndMakeVisible(resetKeywordsButton.get());
    resetKeywordsButton->setButtonText(TRANS("Reset"));
    resetKeywordsButton->addListener(this);

    autoTranslateLabel.reset(new juce::Label("autoTranslateLabel", TRANS("Auto-Translate")));
    autoTranslateButton.reset(new juce::ToggleButton(""));
    if (BaiduAIHelper::GetAccess_Token() != "")
    {
        addAndMakeVisible(autoTranslateLabel.get());
        autoTranslateLabelWidth = juce::LookAndFeel::getDefaultLookAndFeel().getLabelFont(*autoTranslateLabel.get()).getStringWidth(TRANS("Auto-Translate"));

        addAndMakeVisible(autoTranslateButton.get());
        autoTranslateButton->addListener(this);
        autoTranslateButton->setToggleState(SystemSettingsHelper::GetAutoTranslate(), juce::NotificationType::dontSendNotification);
    }
    else
        autoTranslateButton->setToggleState(false, juce::NotificationType::dontSendNotification);

    currentDatabaseLabel.reset(new juce::Label("currentDatabaseLabel", TRANS("Current Database:")));
    addAndMakeVisible(currentDatabaseLabel.get());
    currentDatabaseLabelWidth = juce::LookAndFeel::getDefaultLookAndFeel().getLabelFont(*currentDatabaseLabel.get()).getStringWidth(TRANS("Current Database:"));

    databaseComboBox.reset(new juce::ComboBox("databaseComboBox"));
    addAndMakeVisible(databaseComboBox.get());
    databaseComboBox->setTextWhenNoChoicesAvailable(TRANS("(No choices)"));
    databaseComboBox->addListener(this);

    fileMetadataLabel.reset(new juce::Label("fileMetadataLabel", TRANS("fileMetadataLabel")));
    addAndMakeVisible(fileMetadataLabel.get());

    fxListTable.reset(new FxTable());
    addAndMakeVisible(fxListTable.get());
    fxListTable->Listener = this;

    setSize(900, 600);

    LoadDatabase();
}

AudioSearchComponent::~AudioSearchComponent()
{
    keywordsLabel = nullptr;
    keywordsTextEditor = nullptr;
    searchButton = nullptr;
    resetKeywordsButton = nullptr;
    currentDatabaseLabel = nullptr;
    databaseComboBox = nullptr;
    fileMetadataLabel = nullptr;
    fxListTable = nullptr;

    autoTranslateLabel = nullptr;
    autoTranslateButton = nullptr;
}

void AudioSearchComponent::paint (juce::Graphics& g)
{
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
}

void AudioSearchComponent::resized()
{
    //Layout
    //Label         Button Button   Label Combobox
    //TextEditor                    MetaLabel
    //TableList                     MetaLabel
    //Player

    // Fixed Size
    // Fixed Position
    keywordsLabel->setBounds(0, 0, 200, 30);
    // - WidthOfComboBox
    databaseComboBox->setBounds(getWidth() - 310 + currentDatabaseLabelWidth, 0, 310 - currentDatabaseLabelWidth, 30);
    //- WidthOfComboBox - 10 - WidthOfLabel 
    currentDatabaseLabel->setBounds(getWidth() - 310, 0, currentDatabaseLabelWidth, 30);
    //- WidthOfComboBox - 10 - WidthOfLabel - 10 - WidthOfButton
    resetKeywordsButton->setBounds(getWidth() - 200 - 10 - 100 - 10 - 100, 0, 100, 30);
    //- WidthOfComboBox - 10 - WidthOfLabel - 10 - WidthOfButton - 10 - WidthOfButton
    searchButton->setBounds(getWidth() - 200 - 10 - 100 - 10 - 100 - 10 - 100, 0, 100, 30);
    autoTranslateLabel->setBounds(getWidth() - 200 - 10 - 100 - 10 - 100 - 10 - 100 - 10 - autoTranslateLabelWidth, 0, autoTranslateLabelWidth, 30);
    autoTranslateButton->setBounds(getWidth() - 200 - 10 - 100 - 10 - 100 - 10 - 100 - 10 - autoTranslateLabelWidth - 25, 0, 25, 30);
    //- WidthOfComboBox - 10 - WidthOfLabel
    fileMetadataLabel->setBounds(getWidth() - 200 - 10 - 100, 30 + 10, 200 + 10 + 100, getHeight()- 30 - 10);
    // Auto Resize
    //- WidthOfComboBox - 10 - WidthOfLabel - 10
    keywordsTextEditor->setBounds(0, 30 + 10, getWidth() - 200 - 10 - 100 - 10, 30);
    fxListTable->setBounds(0, 30 + 10 + 30 + 10, getWidth() - 200 - 10 - 100 - 10, getHeight() - 30 - 10 - 30 - 10);
}

void AudioSearchComponent::LoadDatabase()
{
    databaseComboBox->clear();
    for (int i = 0; i < DatabaseHelper::DatabaseFiles.size(); i++)
    {
        databaseComboBox->addItem(DatabaseHelper::DatabaseFiles[i].DatabaseFile.getFileNameWithoutExtension(), DatabaseHelper::DatabaseFiles[i].ComboboxItemID);
    }
    databaseComboBox->setSelectedId(databaseComboBox->getNumItems() == 0 ? 0 : 1, juce::NotificationType::sendNotification);
}

void AudioSearchComponent::buttonClicked(juce::Button* buttonThatWasClicked)
{
    if (buttonThatWasClicked == searchButton.get())
    {
        if (DatabaseHelper::CurrentFxDB != nullptr)
        {
            if (autoTranslateButton->getToggleState())
                keywordsTextEditor->setText(BaiduAIHelper::TextTrans(keywordsTextEditor->getText()));
            auto text = keywordsTextEditor->getText();
            juce::StringArray keyWords;
            keyWords.addTokens(text, true);
            DatabaseHelper::CurrentFxDB->SetFilter(keyWords);
            fxListTable->Update();
        }
    }
    else if (buttonThatWasClicked == resetKeywordsButton.get())
    {
        if (DatabaseHelper::CurrentFxDB != nullptr)
        {
            DatabaseHelper::CurrentFxDB->ResetFilter();
            fxListTable->Update();
        }
    }
    else if (buttonThatWasClicked == autoTranslateButton.get())
    {
    }
}

void AudioSearchComponent::comboBoxChanged(juce::ComboBox* comboBoxThatHasChanged)
{
    if (comboBoxThatHasChanged == databaseComboBox.get())
    {
        DatabaseHelper::LoadFxDatabase(databaseComboBox->getSelectedId());
        fxListTable->Update();
    }
}

void AudioSearchComponent::tableSelectedRowChanged()
{
    if (DatabaseHelper::CurrentFx != nullptr && DatabaseHelper::CurrentFx->AudioFile.existsAsFile() && DatabaseHelper::CurrentFx->AudioFile.getFileExtension() == ".wav" && DatabaseHelper::CurrentFxFileReader != nullptr)
    {
        juce::String metaDataString = "There are more meta data except below:";
        metaDataString += "\n" + juce::String(juce::WavAudioFormat::bwavDescription) + ": " + DatabaseHelper::CurrentFxFileReader->metadataValues[juce::WavAudioFormat::bwavDescription];
        metaDataString += "\n" + juce::String(juce::WavAudioFormat::bwavOriginator) + ": " + DatabaseHelper::CurrentFxFileReader->metadataValues[juce::WavAudioFormat::bwavOriginator];
        metaDataString += "\n" + juce::String(juce::WavAudioFormat::bwavOriginatorRef) + ": " + DatabaseHelper::CurrentFxFileReader->metadataValues[juce::WavAudioFormat::bwavOriginatorRef];
        metaDataString += "\n" + juce::String(juce::WavAudioFormat::bwavOriginationDate) + ": " + DatabaseHelper::CurrentFxFileReader->metadataValues[juce::WavAudioFormat::bwavOriginationDate];
        metaDataString += "\n" + juce::String(juce::WavAudioFormat::bwavOriginationTime) + ": " + DatabaseHelper::CurrentFxFileReader->metadataValues[juce::WavAudioFormat::bwavOriginationTime];
        metaDataString += "\n" + juce::String(juce::WavAudioFormat::bwavTimeReference) + ": " + DatabaseHelper::CurrentFxFileReader->metadataValues[juce::WavAudioFormat::bwavTimeReference];
        metaDataString += "\n" + juce::String(juce::WavAudioFormat::bwavCodingHistory) + ": " + DatabaseHelper::CurrentFxFileReader->metadataValues[juce::WavAudioFormat::bwavCodingHistory];
        fileMetadataLabel->setText(metaDataString, juce::NotificationType::dontSendNotification);
    }
    else
    {
        fileMetadataLabel->setText("Open Failed", juce::NotificationType::dontSendNotification);
    }
    if (Listener != nullptr)
    { 
        Listener->selectedFileChanged();
    }
}