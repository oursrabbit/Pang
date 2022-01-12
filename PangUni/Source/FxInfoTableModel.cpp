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

FxInfoTableModel::FxInfoTableModel(FxDB* newFxDB, juce::Label::Listener* labeListener)
{
    this->newFxDB = newFxDB;
    this->labeListener = labeListener;

    table.reset(new juce::TableListBox("", this));
    addAndMakeVisible(table.get());

    table->getHeader().removeAllColumns();
    table->getHeader().addColumn(TRANS("Fx Info"), 1, 200);
}

FxInfoTableModel::~FxInfoTableModel()
{
    table = nullptr;
}

void FxInfoTableModel::AddNewFxInfoDB()
{
    newFxDB->DBSchema.push_back(new FxInfo(
        newFxDB->DBSchema.size() + 1,
        "New FxInfo " + juce::String(newFxDB->DBSchema.size() + 1),
        ""));
}

void FxInfoTableModel::DeleteNewFxInfoDB()
{
    if (table->getSelectedRow() != -1 && table->getSelectedRow() != 0 && table->getSelectedRow() != 1)
    {
        auto itr = newFxDB->DBSchema.begin() + table->getSelectedRow();
        newFxDB->DBSchema.erase(itr);
    }
}

bool FxInfoTableModel::CheckNewFxInfoDB(juce::String newName)
{
    for (auto itr = newFxDB->DBSchema.begin(); itr != newFxDB->DBSchema.end(); itr++)
    {
        if (newName == (*itr)->HeaderName)
            return false;
    }
    return true;
}

void FxInfoTableModel::UpdateNewFxDB()
{
    table->updateContent();
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
{

}

juce::Component* FxInfoTableModel::refreshComponentForCell(int rowNumber, int columnId, bool, Component* existingComponentToUpdate)
{
    if (rowNumber < newFxDB->DBSchema.size())
    {
        auto* textLabel = static_cast<DoubleClickedEditableLabel*> (existingComponentToUpdate);
        if (textLabel == nullptr)
        {
            bool canEdit = (rowNumber == 0 || rowNumber == 1 ? false : true);
            textLabel = new DoubleClickedEditableLabel(canEdit, rowNumber, columnId, OwnerTypeEnum::FxInfoTable, [this](int rowNumber) {
                table->selectRowsBasedOnModifierKeys(rowNumber, juce::ModifierKeys::noModifiers, false);
                });
        }
        textLabel->setText(TRANS(newFxDB->DBSchema[rowNumber]->HeaderName), juce::NotificationType::dontSendNotification);
        textLabel->addListener(this->labeListener);

        return textLabel;
    }
    return existingComponentToUpdate;
}
