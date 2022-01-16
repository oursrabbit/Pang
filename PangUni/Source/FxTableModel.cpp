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

FxTableModel::FxTableModel(DatabaseEditorDataStruct* newData, juce::Label::Listener* labeListener)
{
    this->newData = newData;
    this->labeListener = labeListener;

    table.reset(new juce::TableListBox("", this));
    addAndMakeVisible(table.get());

    UpdateNewFxDB();
}

FxTableModel::~FxTableModel()
{
    table = nullptr;
}

void FxTableModel::AddNewFx()
{
    Fx* newFx = new Fx();
    newFx->SetInfoValueByColumnID(1, "Absolute Path for New Fx");
    newData->newFxDB->Fxs.push_back(newFx);
}

void FxTableModel::DeleteNewFx()
{
    if (table->getSelectedRow() != -1 && table->getSelectedRow() < newData->newFxDB->Fxs.size())
    {
        auto itr = newData->newFxDB->Fxs.begin() + table->getSelectedRow();
        newData->newFxDB->Fxs.erase(itr);
    }
}

void FxTableModel::UpdateNewFxDB()
{
    table->getHeader().removeAllColumns();
    for (auto itr = newData->newFxDB->DBSchema.begin(); itr != newData->newFxDB->DBSchema.end(); itr++)
    {
        table->getHeader().addColumn((*itr)->HeaderName, (*itr)->ColumnIndex, 100);
    }
    table->updateContent();
}

void FxTableModel::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background
}

void FxTableModel::resized()
{
    table->setBounds(0, 0, getWidth(), getHeight());
}

int FxTableModel::getNumRows()
{
    return newData->newFxDB->Fxs.size();
}

void FxTableModel::paintRowBackground(juce::Graphics& g, int rowNumber, int width, int height, bool rowIsSelected)
{
    auto alternateColour = getLookAndFeel().findColour(juce::ListBox::backgroundColourId)
        .interpolatedWith(getLookAndFeel().findColour(juce::ListBox::textColourId), 0.03f);
    if (rowIsSelected)
        g.fillAll(juce::Colours::lightblue);
    else if (rowNumber % 2)
        g.fillAll(alternateColour);
}

void FxTableModel::paintCell(juce::Graphics& g, int rowNumber, int columnId, int width, int height, bool rowIsSelected)
{

}

juce::Component* FxTableModel::refreshComponentForCell(int rowNumber, int columnId, bool isRowSelected, Component* existingComponentToUpdate)
{
    if (rowNumber < newData->newFxDB->Fxs.size())
    {
        auto info = newData->newFxDB->Fxs[rowNumber]->GetInfoValueByColumnID(columnId);
        auto text = info == nullptr ? "" : info->Value;

        auto* textLabel = static_cast<DoubleClickedEditableLabel*> (existingComponentToUpdate);
        if (textLabel == nullptr)
        {
            textLabel = new DoubleClickedEditableLabel(true, rowNumber, columnId, OwnerTypeEnum::FxTable, [this](int rowNumber, int columnID) {
                table->selectRowsBasedOnModifierKeys(rowNumber, juce::ModifierKeys::noModifiers, false);
                //cellClicked(rowNumber, columnID);
                });
            textLabel->addListener(this->labeListener);
        }
        textLabel->RowNumber = rowNumber;
        textLabel->ColumnID = columnId;
        textLabel->setText(text, juce::NotificationType::dontSendNotification);
        
        return textLabel;
    }
    return existingComponentToUpdate;
}

void FxTableModel::cellClicked(int rowNumber, int columnId, juce::MouseEvent& event)
{

}
