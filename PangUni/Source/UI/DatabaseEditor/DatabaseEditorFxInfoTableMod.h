/*
  ==============================================================================

    DatabaseEditorFxInfoTable.h
    Created: 9 Jan 2022 1:56:21pm
    Author:  YC

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "../Source/Module/FxDB.h"
#include "../Source/Module/Fx.h"
#include "../Source/Module/Fx.h"
#include "DatabaseEditorFxTableMod.h"
//==============================================================================
/*
*/
class DatabaseEditorFxInfoTableMod  : public juce::Component, public juce::TableListBoxModel
{
public:
    FxDB* newFxDB;
    DatabaseEditorFxTableMod* fxTable;
    juce::TableListBox fxInfoTable{ {}, this };

    DatabaseEditorFxInfoTableMod();
    ~DatabaseEditorFxInfoTableMod() override;

    void paint(juce::Graphics&) override;
    void resized() override;

    // Button 
    void addFxInfo();
    void deleteFxInfo();

    virtual int getNumRows() override;
    virtual void paintRowBackground(juce::Graphics&, int rowNumber, int width, int height, bool rowIsSelected) override;
    virtual void paintCell(juce::Graphics&, int rowNumber, int columnId, int width, int height, bool rowIsSelected) override;
};
