/*
  ==============================================================================

    DatabaseEditorFxInfoTable.cpp
    Created: 9 Jan 2022 1:56:21pm
    Author:  YC

  ==============================================================================
*/

#include <JuceHeader.h>
#include "DatabaseEditorFxInfoTableMod.h"

//==============================================================================
DatabaseEditorFxInfoTableMod::DatabaseEditorFxInfoTableMod()
{
    addAndMakeVisible(fxInfoTable);

    fxInfoTable.getHeader().addColumn(TRANS("FxInfos"), 1, 200);
}

DatabaseEditorFxInfoTableMod::~DatabaseEditorFxInfoTableMod()
{
}

void DatabaseEditorFxInfoTableMod::paint(juce::Graphics& g)
{

}

void DatabaseEditorFxInfoTableMod::resized()
{
    fxInfoTable.setBounds(0, 0, getWidth(), getHeight());
}

int DatabaseEditorFxInfoTableMod::getNumRows()
{
    return newFxDB->DBSchema.size();
}

void DatabaseEditorFxInfoTableMod::paintRowBackground(juce::Graphics& g, int rowNumber, int width, int height, bool rowIsSelected)
{
    if (rowIsSelected)
        g.fillAll(juce::Colours::green);
    else
        g.fillAll(rowNumber % 2 == 0 ? juce::Colours::yellow : juce::Colours::red);
}

void DatabaseEditorFxInfoTableMod::paintCell(juce::Graphics& g, int rowNumber, int columnId, int width, int height, bool rowIsSelected)
{
    if (rowNumber < newFxDB->DBSchema.size())
    {
        g.setColour(juce::Colours::blue);
        g.drawText(newFxDB->DBSchema[rowNumber]->HeaderName
            , juce::Rectangle<float>(width, height)
            , juce::Justification::centred
            , true);
    }
}

void DatabaseEditorFxInfoTableMod::addFxInfo()
{
}

void DatabaseEditorFxInfoTableMod::deleteFxInfo()
{
}