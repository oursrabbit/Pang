/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
PangAudioProcessorEditor::PangAudioProcessorEditor (PangAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.

    audioSearchComp.reset(new AudioSearchComponent());
    addAndMakeVisible(audioSearchComp.get());

    audioExportComp.reset(new AudioExportComponent());
    addAndMakeVisible(audioExportComp.get());

    setSize(800, 600);
    setResizable(true, true);
}

PangAudioProcessorEditor::~PangAudioProcessorEditor()
{
    audioSearchComp = nullptr;
    audioExportComp = nullptr;
}

//==============================================================================
void PangAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
}

void PangAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    audioExportComp->setBounds(10, 24 + 8 + getHeight() - AudioExportComponent::FIXHEIGHT, getWidth() - 20, AudioExportComponent::FIXHEIGHT);
    audioSearchComp->setBounds(10, 24 + 8, getWidth() - 20, getHeight() - AudioExportComponent::FIXHEIGHT - 10);
}
