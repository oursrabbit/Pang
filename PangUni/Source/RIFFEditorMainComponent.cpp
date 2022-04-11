/*
  ==============================================================================

    MainWindowMainComponent.cpp
    Created: 11 Jan 2022 5:49:34pm
    Author:  YC

  ==============================================================================
*/

#include <JuceHeader.h>
#include "RIFFEditorMainComponent.h"

//==============================================================================
RIFFEditorMainComponent::RIFFEditorMainComponent()
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    resFileLabel.reset(new juce::Label("resFileLabel",
        TRANS("Resource File:")));
    addAndMakeVisible(resFileLabel.get());
    resFileLabel->setFont(juce::Font(15.00f, juce::Font::plain).withTypefaceStyle("Regular"));
    resFileLabel->setJustificationType(juce::Justification::centredLeft);
    resFileLabel->setEditable(false, false, false);
    resFileLabel->setColour(juce::TextEditor::textColourId, juce::Colours::black);
    resFileLabel->setColour(juce::TextEditor::backgroundColourId, juce::Colour(0x00000000));

    resFileLabel->setBounds(24, 16, 100, 24);

    openResFileButton.reset(new juce::TextButton("openResFileButton"));
    addAndMakeVisible(openResFileButton.get());
    openResFileButton->setButtonText(TRANS("..."));
    openResFileButton->addListener(this);

    openResFileButton->setBounds(504, 16, 40, 24);

    resTextEditor.reset(new juce::TextEditor("resTextEditor"));
    addAndMakeVisible(resTextEditor.get());
    resTextEditor->setMultiLine(false);
    resTextEditor->setReturnKeyStartsNewLine(false);
    resTextEditor->setReadOnly(false);
    resTextEditor->setScrollbarsShown(true);
    resTextEditor->setCaretVisible(true);
    resTextEditor->setPopupMenuEnabled(true);
    resTextEditor->setText(juce::String());

    resTextEditor->setBounds(144, 16, 328, 24);

    riffInfoTable.reset(new RIFFTableComponent());
    addAndMakeVisible(riffInfoTable.get());
    riffInfoTable->setBounds(32, 64, 512, 472);

    setSize(600, 400);
}

RIFFEditorMainComponent::~RIFFEditorMainComponent()
{
    resFileLabel = nullptr;
    openResFileButton = nullptr;
    resTextEditor = nullptr;
    riffInfoTable = nullptr;
}

void RIFFEditorMainComponent::paint(juce::Graphics& g)
{
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));   // clear the background
}

void RIFFEditorMainComponent::resized()
{
    resFileLabel->setBounds(8, 8, 100, 30);
    resTextEditor->setBounds(8 + 100 + 8, 8, getWidth() - 8 - 100 - 8 - 8 - 40 - 8, 30);
    openResFileButton->setBounds(getWidth() - 8 - 40, 8, 40, 30);

    riffInfoTable->setBounds(8, 8 + 30 + 8, getWidth() - 8 - 8, getHeight() - 8 - 30 - 8 - 8);
}

void RIFFEditorMainComponent::buttonClicked(juce::Button* buttonThatWasClicked)
{
    if (buttonThatWasClicked == openResFileButton.get())
    {
    }
}
