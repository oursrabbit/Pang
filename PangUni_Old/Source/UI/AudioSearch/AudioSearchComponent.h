#pragma once

#include <JuceHeader.h>
#include "FxTableComponent.h"
class AudioSearchComponentListener
{
public:
    virtual void selectedFileChanged() {}
    virtual ~AudioSearchComponentListener() {}
};

class AudioSearchComponent  : public juce::Component,
                              public juce::Button::Listener,
                              public juce::ComboBox::Listener,
                              public FxTableListener
{
public:
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
private:
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
    std::unique_ptr<juce::Label> fileMetadataLabel;
    juce::String metaDataString;
    std::unique_ptr<FxTable> fxListTable;

    long long int threadKey;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AudioSearchComponent)
};
