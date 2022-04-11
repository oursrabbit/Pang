/*
  ==============================================================================

    MainWindowMainComponent.cpp
    Created: 11 Jan 2022 5:49:34pm
    Author:  YC

  ==============================================================================
*/

#include <JuceHeader.h>
#include "AudioConvertorMainComponent.h"

//==============================================================================
AudioConvertorMainComponent::AudioConvertorMainComponent()
{
    desFileGroup.reset(new juce::GroupComponent("desFileGroup",
        TRANS("Output Settings")));
    addAndMakeVisible(desFileGroup.get());

    desFileGroup->setBounds(40, 120, 632, 296);

    samplerateComboBox.reset(new juce::ComboBox("samplerateComboBox"));
    addAndMakeVisible(samplerateComboBox.get());
    samplerateComboBox->setEditableText(false);
    samplerateComboBox->setJustificationType(juce::Justification::centredLeft);
    samplerateComboBox->setTextWhenNothingSelected(juce::String());
    samplerateComboBox->setTextWhenNoChoicesAvailable(TRANS("(no choices)"));
    samplerateComboBox->addItem(TRANS("96000"), 1);
    samplerateComboBox->addItem(TRANS("48000"), 2);
    samplerateComboBox->addItem(TRANS("44100"), 3);
    samplerateComboBox->addItem(TRANS("8000"), 4);
    samplerateComboBox->addListener(this);

    samplerateComboBox->setBounds(192, 160, 432, 24);

    bitDepthComboBox.reset(new juce::ComboBox("bitDepthComboBox"));
    addAndMakeVisible(bitDepthComboBox.get());
    bitDepthComboBox->setEditableText(false);
    bitDepthComboBox->setJustificationType(juce::Justification::centredLeft);
    bitDepthComboBox->setTextWhenNothingSelected(juce::String());
    bitDepthComboBox->setTextWhenNoChoicesAvailable(TRANS("(no choices)"));
    bitDepthComboBox->addItem(TRANS("32"), 1);
    bitDepthComboBox->addItem(TRANS("24"), 2);
    bitDepthComboBox->addItem(TRANS("16"), 3);
    bitDepthComboBox->addListener(this);

    bitDepthComboBox->setBounds(200, 208, 440, 24);

    outputTextEditor.reset(new juce::TextEditor("outputTextEditor"));
    addAndMakeVisible(outputTextEditor.get());
    outputTextEditor->setMultiLine(false);
    outputTextEditor->setReturnKeyStartsNewLine(false);
    outputTextEditor->setReadOnly(false);
    outputTextEditor->setScrollbarsShown(true);
    outputTextEditor->setCaretVisible(true);
    outputTextEditor->setPopupMenuEnabled(true);
    outputTextEditor->setText(juce::String());

    outputTextEditor->setBounds(216, 352, 232, 24);

    resampleComboBox.reset(new juce::ComboBox("resampleComboBox"));
    addAndMakeVisible(resampleComboBox.get());
    resampleComboBox->setEditableText(false);
    resampleComboBox->setJustificationType(juce::Justification::centredLeft);
    resampleComboBox->setTextWhenNothingSelected(juce::String());
    resampleComboBox->setTextWhenNoChoicesAvailable(TRANS("(no choices)"));
    resampleComboBox->addItem(TRANS("WindowedSincInterpolator"), 1);
    resampleComboBox->addItem(TRANS("LagrangeInterpolator"), 2);
    resampleComboBox->addItem(TRANS("CatmullRomInterpolator"), 3);
    resampleComboBox->addItem(TRANS("LinearInterpolator"), 4);
    resampleComboBox->addItem(TRANS("ZeroOrderHoldInterpolator"), 5);
    resampleComboBox->addListener(this);

    resampleComboBox->setBounds(224, 296, 400, 24);

    channelsComboBox.reset(new juce::ComboBox("channelsComboBox"));
    addAndMakeVisible(channelsComboBox.get());
    channelsComboBox->setEditableText(false);
    channelsComboBox->setJustificationType(juce::Justification::centredLeft);
    channelsComboBox->setTextWhenNothingSelected(juce::String());
    channelsComboBox->setTextWhenNoChoicesAvailable(TRANS("(no choices)"));
    channelsComboBox->addItem(TRANS("1"), 1);
    channelsComboBox->addItem(TRANS("2"), 2);
    channelsComboBox->addListener(this);

    channelsComboBox->setBounds(208, 256, 432, 24);

    sampleRateLabel.reset(new juce::Label("sampleRateLabel",
        TRANS("Sample Rate:")));
    addAndMakeVisible(sampleRateLabel.get());
    sampleRateLabel->setFont(juce::Font(15.00f, juce::Font::plain).withTypefaceStyle("Regular"));
    sampleRateLabel->setJustificationType(juce::Justification::centredLeft);
    sampleRateLabel->setEditable(false, false, false);
    sampleRateLabel->setColour(juce::TextEditor::textColourId, juce::Colours::black);
    sampleRateLabel->setColour(juce::TextEditor::backgroundColourId, juce::Colour(0x00000000));

    sampleRateLabel->setBounds(64, 160, 150, 24);

    bitDepthLabel.reset(new juce::Label("bitDepthLabel",
        TRANS("Bit Depth:")));
    addAndMakeVisible(bitDepthLabel.get());
    bitDepthLabel->setFont(juce::Font(15.00f, juce::Font::plain).withTypefaceStyle("Regular"));
    bitDepthLabel->setJustificationType(juce::Justification::centredLeft);
    bitDepthLabel->setEditable(false, false, false);
    bitDepthLabel->setColour(juce::TextEditor::textColourId, juce::Colours::black);
    bitDepthLabel->setColour(juce::TextEditor::backgroundColourId, juce::Colour(0x00000000));

    bitDepthLabel->setBounds(72, 208, 150, 24);

    channelsLabel.reset(new juce::Label("channelsLabel",
        TRANS("Channels:")));
    addAndMakeVisible(channelsLabel.get());
    channelsLabel->setFont(juce::Font(15.00f, juce::Font::plain).withTypefaceStyle("Regular"));
    channelsLabel->setJustificationType(juce::Justification::centredLeft);
    channelsLabel->setEditable(false, false, false);
    channelsLabel->setColour(juce::TextEditor::textColourId, juce::Colours::black);
    channelsLabel->setColour(juce::TextEditor::backgroundColourId, juce::Colour(0x00000000));

    channelsLabel->setBounds(72, 256, 150, 24);

    outputLabel.reset(new juce::Label("outputLabel",
        TRANS("Output Folder:")));
    addAndMakeVisible(outputLabel.get());
    outputLabel->setFont(juce::Font(15.00f, juce::Font::plain).withTypefaceStyle("Regular"));
    outputLabel->setJustificationType(juce::Justification::centredLeft);
    outputLabel->setEditable(false, false, false);
    outputLabel->setColour(juce::TextEditor::textColourId, juce::Colours::black);
    outputLabel->setColour(juce::TextEditor::backgroundColourId, juce::Colour(0x00000000));

    outputLabel->setBounds(72, 352, 150, 24);

    resampleLabel.reset(new juce::Label("resampleLabel",
        TRANS("Resample Type:")));
    addAndMakeVisible(resampleLabel.get());
    resampleLabel->setFont(juce::Font(15.00f, juce::Font::plain).withTypefaceStyle("Regular"));
    resampleLabel->setJustificationType(juce::Justification::centredLeft);
    resampleLabel->setEditable(false, false, false);
    resampleLabel->setColour(juce::TextEditor::textColourId, juce::Colours::black);
    resampleLabel->setColour(juce::TextEditor::backgroundColourId, juce::Colour(0x00000000));

    resampleLabel->setBounds(80, 296, 150, 24);

    outputButton.reset(new juce::TextButton("outputButton"));
    addAndMakeVisible(outputButton.get());
    outputButton->setButtonText(TRANS("..."));
    outputButton->addListener(this);

    outputButton->setBounds(488, 360, 150, 24);

    resFileLabel.reset(new juce::Label("resFileLabel",
        TRANS("Resource File:")));
    addAndMakeVisible(resFileLabel.get());
    resFileLabel->setFont(juce::Font(15.00f, juce::Font::plain).withTypefaceStyle("Regular"));
    resFileLabel->setJustificationType(juce::Justification::centredLeft);
    resFileLabel->setEditable(false, false, false);
    resFileLabel->setColour(juce::TextEditor::textColourId, juce::Colours::black);
    resFileLabel->setColour(juce::TextEditor::backgroundColourId, juce::Colour(0x00000000));

    resFileLabel->setBounds(32, 48, 150, 24);

    openResFileButton.reset(new juce::TextButton("openResFileButton"));
    addAndMakeVisible(openResFileButton.get());
    openResFileButton->setButtonText(TRANS("..."));
    openResFileButton->addListener(this);

    openResFileButton->setBounds(624, 48, 40, 24);

    resTextEditor.reset(new juce::TextEditor("resTextEditor"));
    addAndMakeVisible(resTextEditor.get());
    resTextEditor->setMultiLine(false);
    resTextEditor->setReturnKeyStartsNewLine(false);
    resTextEditor->setReadOnly(false);
    resTextEditor->setScrollbarsShown(true);
    resTextEditor->setCaretVisible(true);
    resTextEditor->setPopupMenuEnabled(true);
    resTextEditor->setText(juce::String());

    resTextEditor->setBounds(168, 48, 232, 24);
    
    convertButton.reset(new juce::TextButton("convertButton"));
    addAndMakeVisible(convertButton.get());
    convertButton->setButtonText(TRANS("Convert"));
    convertButton->addListener(this);

    setSize(600, 8 + 30 + 8 + 10 + 8 + 248);
}

AudioConvertorMainComponent::~AudioConvertorMainComponent()
{
    desFileGroup = nullptr;
    samplerateComboBox = nullptr;
    bitDepthComboBox = nullptr;
    outputTextEditor = nullptr;
    resampleComboBox = nullptr;
    channelsComboBox = nullptr;
    sampleRateLabel = nullptr;
    bitDepthLabel = nullptr;
    channelsLabel = nullptr;
    outputLabel = nullptr;
    resampleLabel = nullptr;
    outputButton = nullptr;
    resFileLabel = nullptr;
    openResFileButton = nullptr;
    resTextEditor = nullptr;
    convertButton = nullptr;
}

void AudioConvertorMainComponent::paint(juce::Graphics& g)
{
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));   // clear the background
}

void AudioConvertorMainComponent::resized()
{
    resFileLabel->setBounds(8, 8, 100, 30);
    resTextEditor->setBounds(8 + 100 + 8, 8, getWidth() - 8 - 100 - 8 - 8 - 40 - 8, 30);
    openResFileButton->setBounds(getWidth() - 8 - 40, 8, 40, 30);

    desFileGroup->setBounds(8, 8 + 30 + 8, getWidth() - 8 - 8, 220);

    sampleRateLabel->setBounds(16, 8 + 30 + 8 + 10 + 8, 100, 30);
    samplerateComboBox->setBounds(16 + 100 + 8, 8 + 30 + 8 + 10 + 8, getWidth() - 8 - 8 - 100 - 8 - 8 - 8, 30);
    bitDepthLabel->setBounds(16, 8 + 30 + 8 + 10 + 8 + 30 + 8, 100, 30);
    bitDepthComboBox->setBounds(16 + 100 + 8, 8 + 30 + 8 + 10 + 8 + 30 + 8, getWidth() - 8 - 8 - 100 - 8 - 8 - 8, 30);
    channelsLabel->setBounds(16, 8 + 30 + 8 + 10 + 8 + 30 + 8 + 30 + 8, 100, 30);
    channelsComboBox->setBounds(16 + 100 + 8, 8 + 30 + 8 + 10 + 8 + 30 + 8 + 30 + 8, getWidth() - 8 - 8 - 100 - 8 - 8 - 8, 30);
    resampleLabel->setBounds(16, 8 + 30 + 8 + 10 + 8 + 30 + 8 + 30 + 8 + 30 + 8, 100, 30);
    resampleComboBox->setBounds(16 + 100 + 8, 8 + 30 + 8 + 10 + 8 + 30 + 8 + 30 + 8 + 30 + 8, getWidth() - 8 - 8 - 100 - 8 - 8 - 8, 30);
    outputLabel->setBounds(16, 8 + 30 + 8 + 10 + 8 + 30 + 8 + 30 + 8 + 30 + 8 + 30 + 8, 100, 24);
    outputTextEditor->setBounds(16 + 100 + 8, 8 + 30 + 8 + 10 + 8 + 30 + 8 + 30 + 8 + 30 + 8 + 30 + 8, getWidth() - 8 - 8 - 100 - 8 - 8 - 8 - 40 - 8, 30);
    outputButton->setBounds(getWidth() - 8 - 40 - 8, 8 + 30 + 8 + 10 + 8 + 30 + 8 + 30 + 8 + 30 + 8 + 30 + 8, 40, 30);

    convertButton->setBounds(getWidth() - 8 - 100, getHeight() - 8 - 30, 100, 30);
}

void AudioConvertorMainComponent::comboBoxChanged(juce::ComboBox* comboBoxThatHasChanged)
{
    if (comboBoxThatHasChanged == samplerateComboBox.get())
    {

    }
    else if (comboBoxThatHasChanged == bitDepthComboBox.get())
    {

    }
    else if (comboBoxThatHasChanged == resampleComboBox.get())
    {

    }
    else if (comboBoxThatHasChanged == channelsComboBox.get())
    {

    }
}

void AudioConvertorMainComponent::buttonClicked(juce::Button* buttonThatWasClicked)
{
    if (buttonThatWasClicked == outputButton.get())
    {
    }
    else if (buttonThatWasClicked == openResFileButton.get())
    {
    }
    else if (buttonThatWasClicked == convertButton.get())
    {
    }
}