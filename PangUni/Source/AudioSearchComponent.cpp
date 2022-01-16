#include "AudioSearchComponent.h"
#include "SystemHelper.h"

//==============================================================================
AudioSearchComponent::AudioSearchComponent(SearchDataStruct* newData)
{
    this->newData = newData;
    threadKey = 0;

    keywordsLabel.reset(new juce::Label("keywordsLabel", TRANS("Input Key Words:(space means 'OR')")));
    addAndMakeVisible(keywordsLabel.get());

    keywordsTextEditor.reset(new juce::TextEditor("keywordsTextEditor"));
    keywordsTextEditor->setTooltip(TRANS("Input Key Words:(space means 'OR')"));
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
    if (SystemHelper::Helper->baiduAIHelper->GetAccess_Token() != "")
    {
        addAndMakeVisible(autoTranslateLabel.get());
        autoTranslateLabelWidth = juce::LookAndFeel::getDefaultLookAndFeel().getLabelFont(*autoTranslateLabel.get()).getStringWidth(TRANS("Auto-Translate"));

        addAndMakeVisible(autoTranslateButton.get());
        autoTranslateButton->addListener(this);
        autoTranslateButton->setToggleState(SystemHelper::Helper->systemSettingsHelper->GetAutoTranslate(), juce::NotificationType::dontSendNotification);
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

    fileMetadataTable.reset(new FxMetaTableComponent(newData));
    addAndMakeVisible(fileMetadataTable.get());
    //fileMetadataTable->Listener = this;

    fxListTable.reset(new class FxTable(newData));
    addAndMakeVisible(fxListTable.get());
    fxListTable->Listener = this;

    setSize(900, 600);

    LoadDatabase();
}

AudioSearchComponent::AudioSearchComponent()
{}

AudioSearchComponent::~AudioSearchComponent()
{
    keywordsLabel = nullptr;
    keywordsTextEditor = nullptr;
    searchButton = nullptr;
    resetKeywordsButton = nullptr;
    currentDatabaseLabel = nullptr;
    databaseComboBox = nullptr;
    fileMetadataTable = nullptr;
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
    //         Button Button   Label Combobox
    //TextEditor                    MetaLabel
    //Label                         MetaLabel
    //TableList                     MetaLabel
    //Player

    keywordsLabel->setBounds(0, 0, 300, 30);
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
    fileMetadataTable->setBounds(getWidth() - 200 - 10 - 100, 30 + 10, 200 + 10 + 100, getHeight()- 30 - 10);
    // Auto Resize
    //- WidthOfComboBox - 10 - WidthOfLabel - 10
    keywordsTextEditor->setBounds(0, 30 + 10, getWidth() - 200 - 10 - 100 - 10, 30);
    fxListTable->setBounds(0, 30 + 10 + 30 + 10, getWidth() - 200 - 10 - 100 - 10, getHeight() - 30 - 10 - 30 - 10);
}

void AudioSearchComponent::LoadDatabase()
{
    databaseComboBox->clear();
    for (unsigned long i = 0; i < this->newData->AllFxDBs.size(); i++)
    {
        databaseComboBox->addItem(this->newData->AllFxDBs[i]->DatabaseFile.getFileNameWithoutExtension(), this->newData->AllFxDBs[i]->ComboboxItemID);
    }
    databaseComboBox->setSelectedId(databaseComboBox->getNumItems() == 0 ? 0 : 1, juce::NotificationType::sendNotification);
}

bool AudioSearchComponent::keyPressed(const juce::KeyPress& press)
{
    return fxListTable->keyPressed(press);
}

void AudioSearchComponent::buttonClicked(juce::Button* buttonThatWasClicked)
{
    if (buttonThatWasClicked == searchButton.get())
    {
        if (this->newData->CurrentFxDB != nullptr)
        {
            if (autoTranslateButton->getToggleState())
                keywordsTextEditor->setText(SystemHelper::Helper->baiduAIHelper->TextTrans(keywordsTextEditor->getText()));
            auto text = keywordsTextEditor->getText();
            juce::StringArray keyWords;
            keyWords.addTokens(text, true);
            this->newData->CurrentFxDB->FindFxByKeywords(keyWords);
            fxListTable->UpdateNewFx();
        }
    }
    else if (buttonThatWasClicked == resetKeywordsButton.get())
    {
        if (this->newData->CurrentFxDB != nullptr)
        {
            this->newData->CurrentFxDB->ResetFilteredFxs();
            fxListTable->UpdateNewFx();
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
        this->newData->CurrentFxDB = this->newData->AllFxDBs[comboBoxThatHasChanged->getSelectedId() - 1];
        fxListTable->UpdateNewFx();
    }
}

void AudioSearchComponent::tableSelectedRowChanged()
{
    long long int currentThreadKey = threadKey++;
    this->newData->CurrentFxMetaData.clear();
    this->newData->CurrentFxMetaData.set("Openning...", "");
    this->fileMetadataTable->UpdateNewFx();
    if (this->newData->CurrentFx != nullptr && this->newData->CurrentFx->GetAudioFile().existsAsFile())
    {
        this->newData->CurrentFxMetaData.clear();
        juce::Thread::launch([this, currentThreadKey]() {
            juce::AudioFormatManager manager;
            manager.registerBasicFormats();
            auto reader = manager.createReaderFor(this->newData->CurrentFx->GetAudioFile());
            if (reader != nullptr)
            {
                this->newData->CurrentFxMetaData = reader->metadataValues;
            }
            else
            {
                this->newData->CurrentFxMetaData.set("Open Failed", "");
            }
            delete reader;
            reader = nullptr;
            const juce::MessageManagerLock mmLock;
            if (currentThreadKey + 1 == threadKey)
                postCommandMessage(1234);
            });
    }
    else
    {
        this->newData->CurrentFxMetaData.clear();
        this->newData->CurrentFxMetaData.set("Open Failed", "");
        this->fileMetadataTable->UpdateNewFx();
    }
    if (Listener != nullptr)
    {
        Listener->selectedFileChanged();
    }
}

void AudioSearchComponent::handleCommandMessage(int commandId) {
    switch (commandId) {
        case 1234:
        {
            this->fileMetadataTable->UpdateNewFx();
            return;
        }
        default:
        {
            Component::handleCommandMessage(commandId);
            return;
        }
    }
}
