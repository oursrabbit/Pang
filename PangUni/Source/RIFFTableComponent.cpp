#include "RIFFTableComponent.h"

RIFFTableComponent::RIFFTableComponent()
{
    table.reset(new juce::TableListBox("", this));
    table->getHeader().addColumn("RIFF Tag", 1, 200);
    table->getHeader().addColumn("Value", 2, 200);
    addAndMakeVisible(table.get());
}

RIFFTableComponent::~RIFFTableComponent()
{
}

void RIFFTableComponent::paint(juce::Graphics& g)
{
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));   // clear the background
}

void RIFFTableComponent::resized()
{
    table->setBounds(0, 0, getWidth(), getHeight());
}

bool RIFFTableComponent::keyPressed(const juce::KeyPress& press)
{
    return false;
}

void RIFFTableComponent::UpdateNewFx()
{
    table->updateContent();
}

int RIFFTableComponent::getNumRows()
{
    return 0;
}

void RIFFTableComponent::paintRowBackground(juce::Graphics& g, int rowNumber, int, int, bool rowIsSelected)
{
    auto alternateColour = getLookAndFeel().findColour(juce::ListBox::backgroundColourId)
        .interpolatedWith(getLookAndFeel().findColour(juce::ListBox::textColourId), 0.03f);
    if (rowIsSelected)
        g.fillAll(juce::Colours::lightblue);
    else if (rowNumber % 2)
        g.fillAll(alternateColour);
}

void RIFFTableComponent::paintCell(juce::Graphics& g, int rowNumber, int columnId, int width, int height, bool rowIsSelected)
{
    //if (rowNumber < this->newData->CurrentFxMetaData.size())
    //{
    //    g.setColour(rowIsSelected ? juce::Colours::darkblue : getLookAndFeel().findColour(juce::ListBox::textColourId));  // [5]

    //    auto key = this->newData->CurrentFxMetaData.getAllKeys()[rowNumber];
    //    auto value = this->newData->CurrentFxMetaData[key];
    //    auto text = columnId == 1 ? key : value;
    //    g.drawText(text, 2, 0, width - 4, height, juce::Justification::centredLeft, true);

    //    g.setColour(getLookAndFeel().findColour(juce::ListBox::backgroundColourId));
    //    g.fillRect(width - 1, 0, 1, height);
    //}
}

void RIFFTableComponent::selectedRowsChanged(int lastRowSelected)
{

}