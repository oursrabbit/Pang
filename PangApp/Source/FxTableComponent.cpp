#include "FxTableComponent.h"
#include "DatabaseHelper.h"

FxTable::FxTable()
{
    addAndMakeVisible(table);
    table.setColour(juce::ListBox::outlineColourId, juce::Colours::grey);      // [2]
    table.setOutlineThickness(1);
    table.getHeader().removeAllColumns();
    table.setModel(this);
}

FxTable::~FxTable()
{
}

void FxTable::paint (juce::Graphics&)
{

}

void FxTable::resized()
{
    table.setBounds(0, 0, getWidth(), getHeight());
}

bool FxTable::keyPressed(const juce::KeyPress& press)
{
    if (press == juce::KeyPress::upKey || press.getTextCharacter() == 'w')
    {
        auto preIndex = table.getSelectedRow() - 1;
        preIndex = preIndex < 0 ? 0 : preIndex;
        table.selectRow(preIndex, true, true);
        return true;
    }
    if (press == juce::KeyPress::downKey || press.getTextCharacter() == 's')
    {
        auto preIndex = table.getSelectedRow() + 1;
        preIndex = preIndex >= getNumRows() ? preIndex - 1 : preIndex;
        table.selectRow(preIndex, true, true);
        return true;
    }
    if (press == juce::KeyPress::leftKey || press.getTextCharacter() == 'a')
    {
        auto preIndex = table.getSelectedRow() - 5;
        preIndex = preIndex <= 0 ? 0 : preIndex;
        table.selectRow(preIndex, true, true);
        return true;
    }
    if (press == juce::KeyPress::rightKey || press.getTextCharacter() == 'd')
    {
        auto preIndex = table.getSelectedRow() + 5;
        preIndex = preIndex >= getNumRows() ? getNumRows() - 1 : preIndex;
        table.selectRow(preIndex, true, true);
        return true;
    }
    return false;
}

void FxTable::Update()
{
    if (DatabaseHelper::CurrentFxDB != nullptr)
    {
        table.deselectAllRows();
        table.getHeader().removeAllColumns();
        for each (auto header in DatabaseHelper::CurrentFxDB->DBSchema)
        {
            table.getHeader().addColumn(TRANS(header.HeaderName), header.ColumnIndex, 100);
        }
        table.autoSizeAllColumns();
        table.updateContent();
        table.repaint();
        repaint();
    }
}

int FxTable::getNumRows()
{
    return DatabaseHelper::CurrentFxDB == nullptr ? 0 : (int)DatabaseHelper::CurrentFxDB->FilteredFxs.size();
}

void FxTable::paintRowBackground(juce::Graphics& g, int rowNumber, int , int , bool rowIsSelected)
{
    auto alternateColour = getLookAndFeel().findColour(juce::ListBox::backgroundColourId)
        .interpolatedWith(getLookAndFeel().findColour(juce::ListBox::textColourId), 0.03f);
    if (rowIsSelected)
        g.fillAll(juce::Colours::lightblue);
    else if (rowNumber % 2)
        g.fillAll(alternateColour);
}

void FxTable::paintCell(juce::Graphics& g, int rowNumber, int columnId, int width, int height, bool rowIsSelected)
{
    if (DatabaseHelper::CurrentFxDB != nullptr)
    {
        g.setColour(rowIsSelected ? juce::Colours::darkblue : getLookAndFeel().findColour(juce::ListBox::textColourId));  // [5]

        auto fxIndex = rowNumber - 1;
        auto fx = DatabaseHelper::CurrentFxDB->Fxs[fxIndex];
        FxInfo* info = fx.FindInfoByColumnID(columnId);
        g.drawText(info->Value, 2, 0, width - 4, height, juce::Justification::centredLeft, true);

        g.setColour(getLookAndFeel().findColour(juce::ListBox::backgroundColourId));
        g.fillRect(width - 1, 0, 1, height);
    }
}

juce::Component* FxTable::refreshComponentForCell(int rowNumber, int columnId, bool /*isRowSelected*/,
    juce::Component* existingComponentToUpdate)
{
    auto* textLabel = static_cast<EditableTextCustomComponent*> (existingComponentToUpdate);

    if (textLabel == nullptr)
        textLabel = new EditableTextCustomComponent(*this);

    textLabel->setRowAndColumn(rowNumber, columnId);
    return textLabel;
}

void FxTable::selectedRowsChanged(int)
{
    auto selectedRow = table.getSelectedRow();
    DatabaseHelper::LoadFxFile(selectedRow);
    if (Listener != NULL)
        Listener->tableSelectedRowChanged();
}

juce::String FxTable::GetText(const int columnNumber, const int rowNumber)
{
    FxInfo* fx = DatabaseHelper::CurrentFxDB->FilteredFxs[rowNumber].FindInfoByColumnID(columnNumber);
    return fx == nullptr ? "" : fx->Value;
}

void FxTable::SetText(const int columnNumber, const int rowNumber, const juce::String& newText)
{
    auto fx = DatabaseHelper::CurrentFxDB->FilteredFxs[rowNumber];
    fx.SetValueByColumnID(columnNumber, newText);
}