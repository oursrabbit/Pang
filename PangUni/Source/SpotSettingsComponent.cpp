/*
  ==============================================================================

    SpotSettingsComponent.cpp
    Created: 14 Jan 2022 8:59:43pm
    Author:  YC

  ==============================================================================
*/

#include <JuceHeader.h>
#include "SpotSettingsComponent.h"
#include "SystemHelper.h"

//==============================================================================
SpotSettingsComponent::SpotSettingsComponent()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    OnValueChanged = []() {};
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

    bitDepthComboBox->setBounds(240, 64, 150, 24);

    outputTextEditor.reset(new juce::TextEditor("outputTextEditor"));
    addAndMakeVisible(outputTextEditor.get());
    outputTextEditor->setMultiLine(false);
    outputTextEditor->setReturnKeyStartsNewLine(false);
    outputTextEditor->setReadOnly(false);
    outputTextEditor->setScrollbarsShown(true);
    outputTextEditor->setCaretVisible(true);
    outputTextEditor->setPopupMenuEnabled(true);
    outputTextEditor->setText(juce::String());

    outputTextEditor->setBounds(216, 192, 150, 24);

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

    resampleComboBox->setBounds(240, 272, 150, 24);

    channelsComboBox.reset(new juce::ComboBox("channelsComboBox"));
    addAndMakeVisible(channelsComboBox.get());
    channelsComboBox->setEditableText(false);
    channelsComboBox->setJustificationType(juce::Justification::centredLeft);
    channelsComboBox->setTextWhenNothingSelected(juce::String());
    channelsComboBox->setTextWhenNoChoicesAvailable(TRANS("(no choices)"));
    channelsComboBox->addItem(TRANS("1"), 1);
    channelsComboBox->addItem(TRANS("2"), 2);
    channelsComboBox->addListener(this);

    sampleRateLabel.reset(new juce::Label("sampleRateLabel",
        TRANS("Sample Rate:")));
    addAndMakeVisible(sampleRateLabel.get());
    sampleRateLabel->setFont(juce::Font(15.00f, juce::Font::plain).withTypefaceStyle("Regular"));
    sampleRateLabel->setJustificationType(juce::Justification::centredLeft);
    sampleRateLabel->setEditable(false, false, false);
    sampleRateLabel->setColour(juce::TextEditor::textColourId, juce::Colours::black);
    sampleRateLabel->setColour(juce::TextEditor::backgroundColourId, juce::Colour(0x00000000));

    bitDepthLabel.reset(new juce::Label("bitDepthLabel",
        TRANS("Bit Depth:")));
    addAndMakeVisible(bitDepthLabel.get());
    bitDepthLabel->setFont(juce::Font(15.00f, juce::Font::plain).withTypefaceStyle("Regular"));
    bitDepthLabel->setJustificationType(juce::Justification::centredLeft);
    bitDepthLabel->setEditable(false, false, false);
    bitDepthLabel->setColour(juce::TextEditor::textColourId, juce::Colours::black);
    bitDepthLabel->setColour(juce::TextEditor::backgroundColourId, juce::Colour(0x00000000));

    channelsLabel.reset(new juce::Label("channelsLabel",
        TRANS("Channels:")));
    addAndMakeVisible(channelsLabel.get());
    channelsLabel->setFont(juce::Font(15.00f, juce::Font::plain).withTypefaceStyle("Regular"));
    channelsLabel->setJustificationType(juce::Justification::centredLeft);
    channelsLabel->setEditable(false, false, false);
    channelsLabel->setColour(juce::TextEditor::textColourId, juce::Colours::black);
    channelsLabel->setColour(juce::TextEditor::backgroundColourId, juce::Colour(0x00000000));

    outputLabel.reset(new juce::Label("outputLabel",
        TRANS("Output Folder:")));
    addAndMakeVisible(outputLabel.get());
    outputLabel->setFont(juce::Font(15.00f, juce::Font::plain).withTypefaceStyle("Regular"));
    outputLabel->setJustificationType(juce::Justification::centredLeft);
    outputLabel->setEditable(false, false, false);
    outputLabel->setColour(juce::TextEditor::textColourId, juce::Colours::black);
    outputLabel->setColour(juce::TextEditor::backgroundColourId, juce::Colour(0x00000000));

    resampleLabel.reset(new juce::Label("resampleLabel",
        TRANS("Resample Type:")));
    addAndMakeVisible(resampleLabel.get());
    resampleLabel->setFont(juce::Font(15.00f, juce::Font::plain).withTypefaceStyle("Regular"));
    resampleLabel->setJustificationType(juce::Justification::centredLeft);
    resampleLabel->setEditable(false, false, false);
    resampleLabel->setColour(juce::TextEditor::textColourId, juce::Colours::black);
    resampleLabel->setColour(juce::TextEditor::backgroundColourId, juce::Colour(0x00000000));

    outputButton.reset(new juce::TextButton("outputButton"));
    addAndMakeVisible(outputButton.get());
    outputButton->setButtonText(TRANS("..."));
    outputButton->addListener(this);

    SetValue();
}

SpotSettingsComponent::~SpotSettingsComponent()
{
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

    chooser = nullptr;
}

void SpotSettingsComponent::SetValue()
{
    switch (SystemHelper::Helper->systemSettingsHelper->GetSpotSampleRate())
    {
    case 96000:
        samplerateComboBox->setSelectedId(1, juce::NotificationType::dontSendNotification);
        break;
    case 48000:
        samplerateComboBox->setSelectedId(2, juce::NotificationType::dontSendNotification);
        break;
    case 44100:
        samplerateComboBox->setSelectedId(3, juce::NotificationType::dontSendNotification);
        break;
    default:
        samplerateComboBox->setSelectedId(4, juce::NotificationType::dontSendNotification);
        break;
    }

    switch (SystemHelper::Helper->systemSettingsHelper->GetSpotDepth())
    {
    case 32:
        bitDepthComboBox->setSelectedId(1, juce::NotificationType::dontSendNotification);
        break;
    case 24:
        bitDepthComboBox->setSelectedId(2, juce::NotificationType::dontSendNotification);
        break;
    default:
        bitDepthComboBox->setSelectedId(3, juce::NotificationType::dontSendNotification);
        break;
    }

    switch (SystemHelper::Helper->systemSettingsHelper->GetSpotChannels())
    {
    case 1:
        channelsComboBox->setSelectedId(1, juce::NotificationType::dontSendNotification);
        break;
    default:
        channelsComboBox->setSelectedId(2, juce::NotificationType::dontSendNotification);
        break;
    }

    outputTextEditor->setText(SystemHelper::Helper->systemSettingsHelper->GetSpotOutputFolder());

    auto resampleType = SystemHelper::Helper->systemSettingsHelper->GetSpotResampleType();

    if (resampleType == "WindowedSincInterpolator")
    {
        resampleComboBox->setSelectedId(1);
    }
    else if (resampleType == "LagrangeInterpolator")
    {
        resampleComboBox->setSelectedId(2);
    }
    else if (resampleType == "CatmullRomInterpolator")
    {
        resampleComboBox->setSelectedId(3);
    }
    else if (resampleType == "LinearInterpolator")
    {
        resampleComboBox->setSelectedId(4);
    }
    else  // if(resampleType == "ZeroOrderHoldInterpolator")
    {
        resampleComboBox->setSelectedId(5);
    }
}

void SpotSettingsComponent::saveToPXML()
{
    switch (samplerateComboBox->getSelectedId())
    {
    case 1:
        SystemHelper::Helper->systemSettingsHelper->SetSpotSampleRate(96000);
        break;
    case 2:
        SystemHelper::Helper->systemSettingsHelper->SetSpotSampleRate(48000);
        break;
    case 3:
        SystemHelper::Helper->systemSettingsHelper->SetSpotSampleRate(44100);
        break;
    default:
        SystemHelper::Helper->systemSettingsHelper->SetSpotSampleRate(8000);
        break;
    }

    switch (bitDepthComboBox->getSelectedId())
    {
    case 1:
        SystemHelper::Helper->systemSettingsHelper->SetSpotDepth(32);
        break;
    case 2:
        SystemHelper::Helper->systemSettingsHelper->SetSpotDepth(24);
        break;
    default:
        SystemHelper::Helper->systemSettingsHelper->SetSpotDepth(16);
        break;
    }

    switch (channelsComboBox->getSelectedId())
    {
    case 1:
        SystemHelper::Helper->systemSettingsHelper->SetSpotChannels(1);
        break;
    default:
        SystemHelper::Helper->systemSettingsHelper->SetSpotChannels(2);
        break;
    }

    SystemHelper::Helper->systemSettingsHelper->SetSpotOutputFolder(outputTextEditor->getText());

    if (resampleComboBox->getSelectedId() == 1)
    {
        SystemHelper::Helper->systemSettingsHelper->SetSpotResampleType("WindowedSincInterpolator");
    }
    else if (resampleComboBox->getSelectedId() == 2)
    {
        SystemHelper::Helper->systemSettingsHelper->SetSpotResampleType("LagrangeInterpolator");
    }
    else if (resampleComboBox->getSelectedId() == 3)
    {
        SystemHelper::Helper->systemSettingsHelper->SetSpotResampleType("CatmullRomInterpolator");
    }
    else if (resampleComboBox->getSelectedId() == 4)
    {
        SystemHelper::Helper->systemSettingsHelper->SetSpotResampleType("LinearInterpolator");
    }
    else  // if(resampleType == "ZeroOrderHoldInterpolator")
    {
        SystemHelper::Helper->systemSettingsHelper->SetSpotResampleType("ZeroOrderHoldInterpolator");
    }
}

void SpotSettingsComponent::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background
}

void SpotSettingsComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    sampleRateLabel->setBounds(10, 10, 150, 30);
    bitDepthLabel->setBounds(10, 10 + 40 * 1, 150, 30);
    channelsLabel->setBounds(10, 10 + 40 * 2, 150, 30);
    outputLabel->setBounds(10, 10 + 40 * 3, 150, 30);
    resampleLabel->setBounds(10, 10 + 40 * 4, 150, 30);

    samplerateComboBox->setBounds(170, 10 + 40 * 0, getWidth() - 180, 30);
    bitDepthComboBox->setBounds(170, 10 + 40 * 1, getWidth() - 180, 30);
    channelsComboBox->setBounds(170, 10 + 40 * 2, getWidth() - 180, 30);
    outputTextEditor->setBounds(170, 10 + 40 * 3, getWidth() - 290, 30);
    resampleComboBox->setBounds(170, 10 + 40 * 4, getWidth() - 180, 30);

    outputButton->setBounds(getWidth() - 110, 10 + 40 * 3, 100, 30);
}

void SpotSettingsComponent::comboBoxChanged(juce::ComboBox* comboBoxThatHasChanged)
{
    //[UsercomboBoxChanged_Pre]
    //[/UsercomboBoxChanged_Pre]

    if (comboBoxThatHasChanged == samplerateComboBox.get())
    {
        //[UserComboBoxCode_samplerateComboBox] -- add your combo box handling code here..
        //[/UserComboBoxCode_samplerateComboBox]
    }
    else if (comboBoxThatHasChanged == bitDepthComboBox.get())
    {
        //[UserComboBoxCode_bitDepthComboBox] -- add your combo box handling code here..
        //[/UserComboBoxCode_bitDepthComboBox]
    }
    else if (comboBoxThatHasChanged == resampleComboBox.get())
    {
        //[UserComboBoxCode_resampleComboBox] -- add your combo box handling code here..
        //[/UserComboBoxCode_resampleComboBox]
    }
    else if (comboBoxThatHasChanged == channelsComboBox.get())
    {
        //[UserComboBoxCode_channelsComboBox] -- add your combo box handling code here..
        //[/UserComboBoxCode_channelsComboBox]
    }

    //[UsercomboBoxChanged_Post]
    //[/UsercomboBoxChanged_Post]
    OnValueChanged();
}

void SpotSettingsComponent::buttonClicked(juce::Button* buttonThatWasClicked)
{
    if (buttonThatWasClicked == outputButton.get())
    {
        chooser = std::make_unique<juce::FileChooser>(TRANS("Open"));
        auto chooserFlags = juce::FileBrowserComponent::canSelectDirectories | juce::FileBrowserComponent::useTreeView;
        chooser->launchAsync(chooserFlags, [this](const juce::FileChooser& fc)
            {
                auto file = fc.getResult();
                if (file != juce::File{} && file.isDirectory())
                {
                    outputTextEditor->setText(file.getFullPathName());
                }
            });
    }
}

void SpotSettingsComponent::textEditorTextChanged(juce::TextEditor& textEditor)
{
    OnValueChanged();
}
