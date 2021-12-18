#pragma once

#include <JuceHeader.h>
#include "FxTable.h"

//==============================================================================
/**/

class AudioSearchComponentListener
{
public:
    virtual void selectedFileChanged() {};
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
    void buttonClicked(juce::Button* buttonThatWasClicked) override;
    void comboBoxChanged(juce::ComboBox* comboBoxThatHasChanged) override;
    void tableSelectedRowChanged() override;
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
    std::unique_ptr<FxTable> fxListTable;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AudioSearchComponent)
};
