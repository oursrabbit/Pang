#include "FxTableComponent.h"

FxTable::FxTable()
{

}

FxTable::FxTable(SearchDataStruct* newData)
{
    this->newData = newData;

    table.reset(new juce::TableListBox("", this));
    addAndMakeVisible(table.get());
}

FxTable::~FxTable()
{
}

void FxTable::paint (juce::Graphics& g)
{
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));   // clear the background
}

void FxTable::resized()
{
    table->setBounds(0, 0, getWidth(), getHeight());
}

bool FxTable::keyPressed(const juce::KeyPress& press)
{
    return false;
}

void FxTable::UpdateNewFx()
{
    if (this->newData->CurrentFxDB != nullptr)
    {
        table->deselectAllRows();
        table->getHeader().removeAllColumns();
        for(auto header : this->newData->CurrentFxDB->DBSchema)
        {
            table->getHeader().addColumn(TRANS(header->HeaderName), header->ColumnIndex, 100);
        }
        table->updateContent();
    }
}

int FxTable::getNumRows()
{
    if (this->newData->CurrentFxDB == nullptr)
        return 0;
    else
        return this->newData->CurrentFxDB->FilteredFxs.size();
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
    if (this->newData->CurrentFxDB != nullptr && rowNumber < this->newData->CurrentFxDB->FilteredFxs.size())
    {
        g.setColour(rowIsSelected ? juce::Colours::darkblue : getLookAndFeel().findColour(juce::ListBox::textColourId));  // [5]

        auto fx = this->newData->CurrentFxDB->FilteredFxs[rowNumber];
        FxInfo* info = fx->GetInfoValueByColumnID(columnId);
        auto text = info->Value;
        if (info->HeaderName == "FileName")
            text = juce::File::createFileWithoutCheckingPath(text).getFileName();
        g.drawText(text, 2, 0, width - 4, height, juce::Justification::centredLeft, true);

        g.setColour(getLookAndFeel().findColour(juce::ListBox::backgroundColourId));
        g.fillRect(width - 1, 0, 1, height);
    }
}

void FxTable::selectedRowsChanged(int lastRowSelected)
{
    if (lastRowSelected != -1 && lastRowSelected < this->newData->CurrentFxDB->FilteredFxs.size())
    {
        this->newData->CurrentFx = this->newData->CurrentFxDB->FilteredFxs[lastRowSelected];
        if (Listener != NULL)
            Listener->tableSelectedRowChanged();
    }
}