/*
  ==============================================================================

    AudioSearchComponent.h
    Created: 8 Dec 2021 11:11:53am
    Author:  庞兴庆

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "WaveMetadataTableListBoxModel.h"
#include "DatabaseHelper.h"
#include "BaiduAIHelper.h"

//==============================================================================
/**/

class AudioSearchComponentListener
{
public:
    virtual void selectedFileChanged(int lastRowSelected) {};
};

class AudioSearchComponent  : public juce::Component,
                              public juce::Button::Listener,
                              public juce::ComboBox::Listener,
                              public WaveMetadataTableListBoxModelListener
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
    void tableSelectedRowChanged(int) override;
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
    std::unique_ptr<WaveMetadataTableListBoxModel> fileListTable;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AudioSearchComponent)
};
