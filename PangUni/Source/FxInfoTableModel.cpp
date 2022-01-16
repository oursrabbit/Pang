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

FxInfoTableModel::FxInfoTableModel(DatabaseEditorDataStruct* newData, juce::Label::Listener* labeListener)
{
    this->newData = newData;
    this->labeListener = labeListener;
    newFxInfoId = 3;

    table.reset(new juce::TableListBox("", this));
    addAndMakeVisible(table.get());

    table->getHeader().removeAllColumns();
    table->getHeader().addColumn(TRANS("Fx Info"), 1, 200, 30, -1, table->getHeader().notSortable, -1);
}

FxInfoTableModel::~FxInfoTableModel()
{
    table = nullptr;
}

void FxInfoTableModel::AddNewFxInfo()
{
    newData->newFxDB->DBSchema.push_back(new FxInfo(newFxInfoId, "NewFxInfo" + juce::String(newFxInfoId++), ""));
}

void FxInfoTableModel::DeleteNewFxInfoDB()
{
    if (table->getSelectedRow() != -1 && table->getSelectedRow() != 0 && table->getSelectedRow() != 1)
    {
        auto itr = newData->newFxDB->DBSchema.begin() + table->getSelectedRow();
        newData->newFxDB->DBSchema.erase(itr);
    }
}

bool FxInfoTableModel::CheckNewFxInfoDB(juce::String newName)
{
    for (auto itr = newData->newFxDB->DBSchema.begin(); itr != newData->newFxDB->DBSchema.end(); itr++)
    {
        if (newName == (*itr)->HeaderName)
            return false;
    }
    juce::XmlElement temp("TEMP");
    return temp.isValidXmlName(newName);
}

void FxInfoTableModel::UpdateNewFxDB()
{
    newFxInfoId += this->newData->newFxDB->DBSchema.size();
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
    return newData->newFxDB->DBSchema.size();
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
    if (rowNumber < newData->newFxDB->DBSchema.size())
    {
        auto* textLabel = static_cast<DoubleClickedEditableLabel*> (existingComponentToUpdate);
        if (textLabel == nullptr)
        {
            bool canEdit = (rowNumber == 0 || rowNumber == 1 ? false : true);
            textLabel = new DoubleClickedEditableLabel(canEdit, rowNumber, columnId, OwnerTypeEnum::FxInfoTable, [this](int rowNumber, int columnID) {
                table->selectRowsBasedOnModifierKeys(rowNumber, juce::ModifierKeys::noModifiers, false);
                });
            textLabel->addListener(this->labeListener);
        }
        textLabel->RowNumber = rowNumber;
        textLabel->ColumnID = columnId;
        textLabel->setText(newData->newFxDB->DBSchema[rowNumber]->HeaderName, juce::NotificationType::dontSendNotification);
        return textLabel;
    }
    return existingComponentToUpdate;
}
