/*
  ==============================================================================

    FxInfoTableModel.cpp
    Created: 12 Jan 2022 2:08:44pm
    Author:  YC

  ==============================================================================
*/

#include <JuceHeader.h>
#include "FxInfoTableModel.h"

//==============================================================================
FxInfoTableModel::FxInfoTableModel()
{
}

FxInfoTableModel::FxInfoTableModel(FxDB* newFxDB)
{
    this->newFxDB = newFxDB;

    table.reset(new juce::TableListBox("", this));
    addAndMakeVisible(table.get());

    table->getHeader().removeAllColumns();
    table->getHeader().addColumn(TRANS("Fx Info"), 1, 400);
}

FxInfoTableModel::~FxInfoTableModel()
{
    table = nullptr;
}

void FxInfoTableModel::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background
}

void FxInfoTableModel::resized()
{
    table->setBounds(0, 0, getWidth(), getHeight());
}

int FxInfoTableModel::getNumRows()
{
    return newFxDB->DBSchema.size();
}

void FxInfoTableModel::paintRowBackground(juce::Graphics& g, int rowNumber, int width, int height, bool rowIsSelected)
{
    auto alternateColour = getLookAndFeel().findColour(juce::ListBox::backgroundColourId)
        .interpolatedWith(getLookAndFeel().findColour(juce::ListBox::textColourId), 0.03f);
    if (rowIsSelected)
        g.fillAll(juce::Colours::lightblue);
    else if (rowNumber % 2)
        g.fillAll(alternateColour);
}

void FxInfoTableModel::paintCell(juce::Graphics& g, int rowNumber, int columnId, int width, int height, bool rowIsSelected)
{}

juce::Component* FxInfoTableModel::refreshComponentForCell(int rowNumber, int columnId, bool, Component* existingComponentToUpdate)
{
    if (rowNumber < newFxDB->DBSchema.size())
    {
        auto* textLabel = static_cast<DoubleClickedEditableLabel*> (existingComponentToUpdate);
        if (textLabel == nullptr)
            textLabel = new DoubleClickedEditableLabel(rowNumber, columnId);
        textLabel->setText(TRANS(newFxDB->DBSchema[rowNumber]->HeaderName), juce::NotificationType::dontSendNotification);
        textLabel->addListener(this);
        return textLabel;
    }
    return existingComponentToUpdate;
}

void FxInfoTableModel::labelTextChanged(juce::Label* labelThatHasChanged)
{
    auto label = (DoubleClickedEditableLabel*)labelThatHasChanged;
    if (label != nullptr)
    {
        newFxDB->DBSchema[label->RowNumber]->HeaderName = label->getText();
    }
    table->updateContent();
}
