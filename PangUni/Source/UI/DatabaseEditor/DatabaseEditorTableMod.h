/*
  ==============================================================================

    DatabaseEditorTableMod.h
    Created: 8 Jan 2022 10:28:43am
    Author:  YC

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "
#include "Module/Fx.h"
#include "Module/FxInfo.h"

class DatabaseEditorTableMod : public juce::Component, public juce::TableListBoxModel
{
public:
    FxDB newDB;
    juce::TableListBox table{ {}, this };


    DatabaseEditorTableMod();
    ~DatabaseEditorTableMod() override;

    void paint(juce::Graphics&) override;
    void resized() override;

    void clearTable();
    
    // Button 
    void addFx();
    void deleteFx();
    void addFxInfo();
    void deleteFxInfo();

    void openFxDB();
    void openFxDBFolder();
    void exportFxDB();

    // Í¨¹ý TableListBoxModel ¼Ì³Ð
    virtual int getNumRows() override;
    virtual void paintRowBackground(juce::Graphics&, int rowNumber, int width, int height, bool rowIsSelected) override;
    virtual void paintCell(juce::Graphics&, int rowNumber, int columnId, int width, int height, bool rowIsSelected) override;
};