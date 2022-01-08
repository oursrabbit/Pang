/*
  ==============================================================================

    DatabaseEditorTableMod.cpp
    Created: 8 Jan 2022 10:28:43am
    Author:  YC

  ==============================================================================
*/

#include "DatabaseEditorTableMod.h"

DatabaseEditorTableMod::DatabaseEditorTableMod()
    :newDB(juce::File(), 1)
{
    addAndMakeVisible(table);

    clearTable();
}

DatabaseEditorTableMod::~DatabaseEditorTableMod()
{
}

void DatabaseEditorTableMod::paint(juce::Graphics& g)
{

}

void DatabaseEditorTableMod::resized()
{
    table.setBounds(0, 0, getWidth(), getHeight());
}

void DatabaseEditorTableMod::clearTable()
{
    newDB = FxDB(juce::File(), 1);
    table.getHeader().removeAllColumns();
    table.getHeader().addColumn("FileName", 1, 100);
    table.getHeader().addColumn("Description", 2, 100);
}

int DatabaseEditorTableMod::getNumRows()
{
    return newDB.Fxs.size();
}

void DatabaseEditorTableMod::paintRowBackground(juce::Graphics& g, int rowNumber, int width, int height, bool rowIsSelected)
{
    g.fillAll(rowNumber % 2 == 0 ? juce::Colours::yellow : juce::Colours::red);
}

void DatabaseEditorTableMod::paintCell(juce::Graphics&, int rowNumber, int columnId, int width, int height, bool rowIsSelected)
{
}

void DatabaseEditorTableMod::addFx()
{
    Fx newFx = Fx("",)
}

void DatabaseEditorTableMod::deleteFx()
{
}

void DatabaseEditorTableMod::addFxInfo()
{
}

void DatabaseEditorTableMod::deleteFxInfo()
{
}
