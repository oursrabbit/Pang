/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 6.1.2

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library.
  Copyright (c) 2020 - Raw Material Software Limited.

  ==============================================================================
*/

//[Headers] You can add your own extra header files here...
//[/Headers]

#include "WaveMetadataTableListBoxModel.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
WaveMetadataTableListBoxModel::WaveMetadataTableListBoxModel()
{
    addAndMakeVisible(table);
    table.setColour(juce::ListBox::outlineColourId, juce::Colours::grey);      // [2]
    table.setOutlineThickness(1);
    table.getHeader().removeAllColumns();
    for each (auto header in FxDB::DBSchema)
    {
        table.getHeader().addColumn(TRANS(header.HeaderName), header.ColumnIndex, 100);
    }
    table.autoSizeAllColumns();
    table.setModel(this);
}

WaveMetadataTableListBoxModel::~WaveMetadataTableListBoxModel()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]



    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void WaveMetadataTableListBoxModel::paint (juce::Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    //g.fillAll (juce::Colour (0xff323e44));

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void WaveMetadataTableListBoxModel::resized()
{
    table.setBounds(0, 0, getWidth(), getHeight());
}

void WaveMetadataTableListBoxModel::Update()
{
    repaint();
    table.updateContent();
    table.repaint();
}

int WaveMetadataTableListBoxModel::getNumRows()
{
    return DatabaseHelper::CurrentFxDB == nullptr ? 0 : DatabaseHelper::CurrentFxDB->FilteredFxs.size();
}

void WaveMetadataTableListBoxModel::paintRowBackground(juce::Graphics& g, int rowNumber, int width, int height, bool rowIsSelected)
{
    auto alternateColour = getLookAndFeel().findColour(juce::ListBox::backgroundColourId)
        .interpolatedWith(getLookAndFeel().findColour(juce::ListBox::textColourId), 0.03f);
    if (rowIsSelected)
        g.fillAll(juce::Colours::lightblue);
    else if (rowNumber % 2)
        g.fillAll(alternateColour);
}

void WaveMetadataTableListBoxModel::paintCell(juce::Graphics& g, int rowNumber, int columnId, int width, int height, bool rowIsSelected)
{
    if (DatabaseHelper::CurrentFxDB != nullptr)
    {
        g.setColour(rowIsSelected ? juce::Colours::darkblue : getLookAndFeel().findColour(juce::ListBox::textColourId));  // [5]

        auto fx = DatabaseHelper::CurrentFxDB->Fxs[rowNumber];
        FxInfoHeader* info = fx.FindInfoByColumnID(columnId);
        g.drawText(info->Value, 2, 0, width - 4, height, juce::Justification::centredLeft, true);

        g.setColour(getLookAndFeel().findColour(juce::ListBox::backgroundColourId));
        g.fillRect(width - 1, 0, 1, height);
    }
}

juce::Component* WaveMetadataTableListBoxModel::refreshComponentForCell(int rowNumber, int columnId, bool /*isRowSelected*/,
    juce::Component* existingComponentToUpdate)
{
    auto* textLabel = static_cast<EditableTextCustomComponent*> (existingComponentToUpdate);

    if (textLabel == nullptr)
        textLabel = new EditableTextCustomComponent(*this);

    textLabel->setRowAndColumn(rowNumber, columnId);
    return textLabel;
}

void WaveMetadataTableListBoxModel::selectedRowsChanged(int lastRowSelected)
{
   // if (Listener != NULL)
       // Listener->tableSelectedRowChanged(lastRowSelected);
}

