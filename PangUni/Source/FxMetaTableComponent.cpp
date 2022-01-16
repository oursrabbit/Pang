#include "FxMetaTableComponent.h"

FxMetaTableComponent::FxMetaTableComponent()
{

}

FxMetaTableComponent::FxMetaTableComponent(SearchDataStruct* newData)
{
    this->newData = newData;

    table.reset(new juce::TableListBox("", this));
    table->getHeader().addColumn("Meta", 1, 100);
    table->getHeader().addColumn("Value", 2, 100);
    addAndMakeVisible(table.get());
}

FxMetaTableComponent::~FxMetaTableComponent()
{
}

void FxMetaTableComponent::paint(juce::Graphics& g)
{
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));   // clear the background
}

void FxMetaTableComponent::resized()
{
    table->setBounds(0, 0, getWidth(), getHeight());
}

bool FxMetaTableComponent::keyPressed(const juce::KeyPress& press)
{
    return false;
}

void FxMetaTableComponent::UpdateNewFx()
{
    table->updateContent();
}

int FxMetaTableComponent::getNumRows()
{
    return this->newData->CurrentFxMetaData.size();
}

void FxMetaTableComponent::paintRowBackground(juce::Graphics& g, int rowNumber, int, int, bool rowIsSelected)
{
    auto alternateColour = getLookAndFeel().findColour(juce::ListBox::backgroundColourId)
        .interpolatedWith(getLookAndFeel().findColour(juce::ListBox::textColourId), 0.03f);
    if (rowIsSelected)
        g.fillAll(juce::Colours::lightblue);
    else if (rowNumber % 2)
        g.fillAll(alternateColour);
}

void FxMetaTableComponent::paintCell(juce::Graphics& g, int rowNumber, int columnId, int width, int height, bool rowIsSelected)
{
    if (rowNumber < this->newData->CurrentFxMetaData.size())
    {
        g.setColour(rowIsSelected ? juce::Colours::darkblue : getLookAndFeel().findColour(juce::ListBox::textColourId));  // [5]

        auto key = this->newData->CurrentFxMetaData.getAllKeys()[rowNumber];
        auto value = this->newData->CurrentFxMetaData[key];
        auto text = columnId == 1 ? key : value;
        g.drawText(text, 2, 0, width - 4, height, juce::Justification::centredLeft, true);

        g.setColour(getLookAndFeel().findColour(juce::ListBox::backgroundColourId));
        g.fillRect(width - 1, 0, 1, height);
    }
}

void FxMetaTableComponent::selectedRowsChanged(int lastRowSelected)
{

}