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

    table.getHeader().removeAllColumns();
    for each (auto header in DatabaseHelper::databaseHeaderIndexSchema)
    {
        table.getHeader().addColumn(TRANS(header.second), header.first, 100);
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
    return DatabaseHelper::FilteredFxInfos.size();
}

void WaveMetadataTableListBoxModel::paintRowBackground(juce::Graphics& g, int rowNumber, int width, int height, bool rowIsSelected)
{
    g.setColour(juce::Colours::white);
    g.fillAll();
}

void WaveMetadataTableListBoxModel::paintCell(juce::Graphics& g, int rowNumber, int columnId, int width, int height, bool rowIsSelected)
{
    g.setColour(juce::Colours::black);
    auto FxInfo = DatabaseHelper::FilteredFxInfos[rowNumber];
    auto Info = FxInfo.find(columnId);
    g.drawText(Info->second, 2, 0, width, height, juce::Justification::centredLeft, true);
}

void WaveMetadataTableListBoxModel::selectedRowsChanged(int lastRowSelected)
{
    if (Listener != NULL)
        Listener->tableSelectedRowChanged(lastRowSelected);
}

