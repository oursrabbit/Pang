/*
  ==============================================================================

    FxTableModel.cpp
    Created: 12 Jan 2022 2:08:08pm
    Author:  YC

  ==============================================================================
*/

#include <JuceHeader.h>
#include "FxTableModel.h"

//==============================================================================
FxTableModel::FxTableModel()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
}

FxTableModel::FxTableModel(FxDB* newFxDB)
{
    this->newFxDB = newFxDB;

    table.reset(new juce::TableListBox("", this));
    addAndMakeVisible(table.get());
}

FxTableModel::~FxTableModel()
{
    table = nullptr;
}

void FxTableModel::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (juce::Colours::white);
    g.setFont (14.0f);
    g.drawText ("FxTableModel", getLocalBounds(),
                juce::Justification::centred, true);   // draw some placeholder text
}

void FxTableModel::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}

int FxTableModel::getNumRows()
{
    return 0;
}

void FxTableModel::paintRowBackground(juce::Graphics& g, int rowNumber, int width, int height, bool rowIsSelected)
{
}

void FxTableModel::paintCell(juce::Graphics& g, int rowNumber, int columnId, int width, int height, bool rowIsSelected)
{
}
