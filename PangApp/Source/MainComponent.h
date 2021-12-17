#pragma once

#include <JuceHeader.h>
#include "AudioSearchComponent.h"
#include "AudioExportComponent.h"
#include "PangMenuComponent.h"

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent  : public juce::AudioAppComponent
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent() override;

    //==============================================================================
    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;

    //==============================================================================
    void paint (juce::Graphics& g) override;
    void resized() override;

private:
    //==============================================================================
    // Your private member variables go here...

    std::unique_ptr<AudioSearchComponent> audioSearchComp;
    std::unique_ptr<AudioExportComponent> audioExportComp;
    std::unique_ptr<PangMenuComponent> pangMenuComp;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
