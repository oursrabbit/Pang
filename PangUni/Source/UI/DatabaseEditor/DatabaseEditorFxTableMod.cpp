/*
  ==============================================================================

    DatabaseEditorTableMod.cpp
    Created: 8 Jan 2022 10:28:43am
    Author:  YC

  ==============================================================================
*/

#include "DatabaseEditorFxTableMod.h"

DatabaseEditorFxTableMod::DatabaseEditorFxTableMod()
{
    addAndMakeVisible(fxTable);

    for (auto header : newFxDB->DBSchema)
    {
        fxTable.getHeader().addColumn(header->HeaderName, header->ColumnIndex, 100);
    }
}

DatabaseEditorFxTableMod::~DatabaseEditorFxTableMod()
{
}

void DatabaseEditorFxTableMod::paint(juce::Graphics& g)
{

}

void DatabaseEditorFxTableMod::resized()
{
    fxTable.setBounds(0, 0, getWidth(), getHeight());
}

int DatabaseEditorFxTableMod::getNumRows()
{
    return newFxDB->Fxs.size();
}

void DatabaseEditorFxTableMod::paintRowBackground(juce::Graphics& g, int rowNumber, int width, int height, bool rowIsSelected)
{
    if (rowIsSelected)
        g.fillAll(juce::Colours::green);
    else
        g.fillAll(rowNumber % 2 == 0 ? juce::Colours::yellow : juce::Colours::red);
}

void DatabaseEditorFxTableMod::paintCell(juce::Graphics& g, int rowNumber, int columnId, int width, int height, bool rowIsSelected)
{
    if (rowNumber < newFxDB->Fxs.size())
    {
        g.setColour(juce::Colours::blue);
        g.drawText(newFxDB->Fxs[rowNumber]->GetInfoValueByColumnID(columnId)->Value
            , juce::Rectangle<float>(width, height)
            , juce::Justification::centred
            , true);
    }
}

void DatabaseEditorFxTableMod::addFx()
{
    newFxDB->Fxs.push_back(new Fx());
    fxTable.updateContent();
}

void DatabaseEditorFxTableMod::deleteFx()
{
    auto rowNumber = fxTable.getSelectedRow();
    if (rowNumber != -1 && rowNumber < newFxDB->Fxs.size())
    {
        auto itr = newFxDB->Fxs.begin() + rowNumber;
        newFxDB->Fxs.erase(itr);
        fxTable.updateContent();
    }
}
