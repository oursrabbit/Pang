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
    addAndMakeVisible(listbox);
}

CreateDBSourceListBoxModel::~CreateDBSourceListBoxModel()
{
}

int CreateDBSourceListBoxModel::getNumRows()
{
    return SourcePaths.size();
}

void CreateDBSourceListBoxModel::paintListBoxItem(int rowNumber, juce::Graphics& g, int width, int height, bool rowIsSelected)
{
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
