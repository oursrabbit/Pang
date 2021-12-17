/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "AudioSearchComponent.h"
#include "AudioExportComponent.h"

//==============================================================================
/**
*/
class PangAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    PangAudioProcessorEditor (PangAudioProcessor&);
    ~PangAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    PangAudioProcessor& audioProcessor;

    std::unique_ptr<AudioSearchComponent> audioSearchComp;
    std::unique_ptr<AudioExportComponent> audioExportComp;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PangAudioProcessorEditor)
};
