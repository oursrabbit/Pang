/*
  ==============================================================================

    CreateDBSourceListBoxModel.cpp
    Created: 6 Mar 2022 8:13:34pm
    Author:  YC

  ==============================================================================
*/

#include "CreateDBSourceListBoxModel.h"

CreateDBSourceListBoxModel::CreateDBSourceListBoxModel()
{
    listbox.setModel(this);
    addAndMakeVisible(listbox);
}

CreateDBSourceListBoxModel::~CreateDBSourceListBoxModel()
{
}

void CreateDBSourceListBoxModel::updateList(juce::String fullPath, bool isAdd)
{
    if (isAdd)
        SourcePaths.addIfNotAlreadyThere(fullPath);
    else if(listbox.getSelectedRow() != -1)
    {
        SourcePaths.remove(listbox.getSelectedRow());
    }
    listbox.updateContent();
}

int CreateDBSourceListBoxModel::getNumRows()
{
    return SourcePaths.size();
}

void CreateDBSourceListBoxModel::paintListBoxItem(int rowNumber, juce::Graphics& g, int width, int height, bool rowIsSelected)
{
    auto alternateColour = getLookAndFeel().findColour(juce::ListBox::backgroundColourId)
        .interpolatedWith(getLookAndFeel().findColour(juce::ListBox::textColourId), 0.03f);
    if (rowIsSelected)
        g.fillAll(juce::Colours::lightblue);
    else if (rowNumber % 2)
        g.fillAll(alternateColour);

    if (rowNumber < SourcePaths.size())
    {
        g.setColour(juce::Colours::white);
        g.drawText(SourcePaths[rowNumber], 4, 0, width, height, juce::Justification::centred);
    }
}

void CreateDBSourceListBoxModel::paint(juce::Graphics& g)
{
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));   // clear the background
}

void CreateDBSourceListBoxModel::resized()
{
    listbox.setBounds(0, 0, getWidth(), getHeight());
}
