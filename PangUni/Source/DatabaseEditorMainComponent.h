/*
  ==============================================================================

    DatabaseEditorMainComponent.h
    Created: 11 Jan 2022 5:48:32pm
    Author:  YC

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "FxTableModel.h"
#include "FxInfoTableModel.h"
//==============================================================================
/*
*/
class DatabaseEditorMainComponent  : public juce::Component, public juce::Button::Listener
{
public:
    DatabaseEditorMainComponent();
    DatabaseEditorMainComponent(FxDB* newFxDB);
    ~DatabaseEditorMainComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    void buttonClicked(juce::Button* buttonThatWasClicked) override;

    FxDB* newFxDB;

    std::unique_ptr<juce::ToggleButton> autoCreateThumbnailCheckBox;
    std::unique_ptr<FxInfoTableModel> fxInfosTable;
    std::unique_ptr<FxTableModel> fxsTable;
    std::unique_ptr<juce::TextButton> addInfoButton;
    std::unique_ptr<juce::TextButton> deleteInfoButton;
    std::unique_ptr<juce::TextButton> addFxButton;
    std::unique_ptr<juce::TextButton> deleteFxButton;
    std::unique_ptr<juce::TextButton> importInfoSchemaButton;
    std::unique_ptr<juce::TextButton> exportInfoSchemaButton;
    std::unique_ptr<juce::TextButton> importFxFromDBButton;
    std::unique_ptr<juce::TextButton> exportFXDBButton;
    std::unique_ptr<juce::TextButton> importFxFromFolderButton;
    std::unique_ptr<juce::Label> helpLabel;
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DatabaseEditorMainComponent)
};
