#pragma once

#include <JuceHeader.h>
#include "FxTableComponent.h"
#include "FxMetaTableComponent.h"
#include "SearchDataStruct.h"

class AudioSearchComponentListener
{
public:
    virtual void selectedFileChanged() = 0;
    virtual ~AudioSearchComponentListener() {}
};

class AudioSearchComponent  : public juce::Component,
                              public juce::Button::Listener,
                              public juce::ComboBox::Listener,
                              public FxTableListener
{
public:
    AudioSearchComponent(SearchDataStruct* newData);
    AudioSearchComponent();
    ~AudioSearchComponent() override;

    AudioSearchComponentListener* Listener = nullptr;

    void paint (juce::Graphics&) override;
    void resized() override;
    void LoadDatabase();
    bool keyPressed(const juce::KeyPress& press) override;
    void buttonClicked(juce::Button* buttonThatWasClicked) override;
    void comboBoxChanged(juce::ComboBox* comboBoxThatHasChanged) override;
    void tableSelectedRowChanged() override;
    void handleCommandMessage(int commandId) override;

    SearchDataStruct* newData;
    std::unique_ptr<juce::Label> keywordsLabel;
    std::unique_ptr<juce::TextEditor> keywordsTextEditor;
    std::unique_ptr<juce::TextButton> searchButton;
    std::unique_ptr<juce::TextButton> resetKeywordsButton;
    std::unique_ptr<juce::Label> autoTranslateLabel;
    std::unique_ptr<juce::ToggleButton> autoTranslateButton;
    int autoTranslateLabelWidth;
    std::unique_ptr<juce::Label> currentDatabaseLabel;
    int currentDatabaseLabelWidth;
    std::unique_ptr<juce::ComboBox> databaseComboBox;
    std::unique_ptr<FxMetaTableComponent> fileMetadataTable;
    std::unique_ptr<class FxTable> fxListTable;

    long long int threadKey;
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AudioSearchComponent)
};
