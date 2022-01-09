/*
  ==============================================================================

    DatabaseEditorTableMod.h
    Created: 8 Jan 2022 10:28:43am
    Author:  YC

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "../Source/Module/FxDB.h"
#include "../Source/Module/Fx.h"
#include "../Source/Module/Fx.h"
#include "DatabaseEditorFxInfoTableMod.h"

class DatabaseEditorFxTableMod : public juce::Component, public juce::TableListBoxModel
{
public:
    FxDB* newFxDB;
    DatabaseEditorFxInfoTableMod* fxInfoTable;
    juce::TableListBox fxTable{ {}, this };

    DatabaseEditorFxTableMod();
    ~DatabaseEditorFxTableMod() override;

    void paint(juce::Graphics&) override;
    void resized() override;
    
    // Button 
    void addFx();
    void deleteFx();

    virtual int getNumRows() override;
    virtual void paintRowBackground(juce::Graphics&, int rowNumber, int width, int height, bool rowIsSelected) override;
    virtual void paintCell(juce::Graphics&, int rowNumber, int columnId, int width, int height, bool rowIsSelected) override;
};