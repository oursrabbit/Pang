/*
  ==============================================================================

    FxInfoTableModel.h
    Created: 12 Jan 2022 2:08:44pm
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
class FxInfoTableModel  : public juce::Component, public juce::TableListBoxModel, public juce::Label::Listener
{
public:
    FxDB* newFxDB;
    std::unique_ptr<juce::TableListBox> table;

    FxInfoTableModel();
    FxInfoTableModel(FxDB* newFxDB);
    ~FxInfoTableModel() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    virtual int getNumRows() override;
    virtual void paintRowBackground(juce::Graphics& g, int rowNumber, int width, int height, bool rowIsSelected) override;
    virtual void paintCell(juce::Graphics& g, int rowNumber, int columnId, int width, int height, bool rowIsSelected) override;
    virtual Component* refreshComponentForCell(int rowNumber, int columnId, bool /*isRowSelected*/, Component* existingComponentToUpdate) override;

    virtual void labelTextChanged(juce::Label* labelThatHasChanged) override;
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FxInfoTableModel)
};
