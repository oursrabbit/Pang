/*
  ==============================================================================

    FxTableModel.h
    Created: 12 Jan 2022 2:08:08pm
    Author:  YC

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "FxDB.h"
#include "CustomTableCells.h"

//==============================================================================
/*
*/
class FxTableModel  : public juce::Component, public juce::TableListBoxModel
{
public:
    FxDB* newFxDB;
    juce::Label::Listener* labeListener;
    std::unique_ptr<juce::TableListBox> table;

    FxTableModel();
    FxTableModel(FxDB* newFxDB, juce::Label::Listener* labeListener);
    ~FxTableModel() override;
    void AddNewFx();
    void DeleteNewFx();
    void UpdateNewFxDB();

    void paint (juce::Graphics&) override;
    void resized() override;

    virtual int getNumRows() override;
    virtual void paintRowBackground(juce::Graphics& g, int rowNumber, int width, int height, bool rowIsSelected) override;
    virtual void paintCell(juce::Graphics& g, int rowNumber, int columnId, int width, int height, bool rowIsSelected) override;
    virtual Component* refreshComponentForCell(int rowNumber, int columnId, bool /*isRowSelected*/, Component* existingComponentToUpdate) override;
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FxTableModel)
};
