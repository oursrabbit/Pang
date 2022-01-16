/*
  ==============================================================================

    MainWindowMainComponent.cpp
    Created: 11 Jan 2022 5:49:34pm
    Author:  YC

  ==============================================================================
*/

#include <JuceHeader.h>
#include "SearchWindowMainComponent.h"

//==============================================================================
SearchWindowMainComponent::SearchWindowMainComponent(SearchDataStruct* newData)
{
    this->newData = newData;

    audioSearchComp.reset(new AudioSearchComponent(newData));
    audioSearchComp->Listener = this;
    addAndMakeVisible(audioSearchComp.get());

    audioExportComp.reset(new AudioExportComponent(newData));
    addAndMakeVisible(audioExportComp.get());

    setSize(1000, 600);
}

SearchWindowMainComponent::SearchWindowMainComponent()
{
}

SearchWindowMainComponent::~SearchWindowMainComponent()
{
    audioSearchComp = nullptr;
}

void SearchWindowMainComponent::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background
}

void SearchWindowMainComponent::resized()
{
    audioSearchComp->setBounds(10, 10, getWidth() - 20, getHeight() - 260);
    audioExportComp->setBounds(10, getHeight() - 250, getWidth() - 20, 240);
}

bool SearchWindowMainComponent::keyPressed(const juce::KeyPress& press)
{
    auto table = audioSearchComp->fxListTable->table.get();
    if (press == juce::KeyPress::upKey || press.getTextCharacter() == 'w')
    {
        auto preIndex = table->getSelectedRow() - 1;
        preIndex = preIndex < 0 ? 0 : preIndex;
        table->selectRow(preIndex, true, true);
        table->scrollToEnsureRowIsOnscreen(preIndex);
        return true;
    }
    if (press == juce::KeyPress::downKey || press.getTextCharacter() == 's')
    {
        auto preIndex = table->getSelectedRow() + 1;
        preIndex = preIndex >= audioSearchComp->fxListTable->getNumRows() ? preIndex - 1 : preIndex;
        table->selectRow(preIndex, true, true);
        table->scrollToEnsureRowIsOnscreen(preIndex);
        return true;
    }
    if (press == juce::KeyPress::leftKey || press.getTextCharacter() == 'a')
    {
        auto preIndex = table->getSelectedRow() - 5;
        preIndex = preIndex <= 0 ? 0 : preIndex;
        table->selectRow(preIndex, true, true);
        table->scrollToEnsureRowIsOnscreen(preIndex);
        return true;
    }
    if (press == juce::KeyPress::rightKey || press.getTextCharacter() == 'd')
    {
        auto preIndex = table->getSelectedRow() + 5;
        preIndex = preIndex >= audioSearchComp->fxListTable->getNumRows() ? audioSearchComp->fxListTable->getNumRows() - 1 : preIndex;
        table->selectRow(preIndex, true, true);
        table->scrollToEnsureRowIsOnscreen(preIndex);
        return true;
    }
    return false;
}

void SearchWindowMainComponent::selectedFileChanged()
{
    if (this->newData->CurrentFx != nullptr)
    {
        audioExportComp->UpdataNewFx();
    }
}
