#pragma once

#include <JuceHeader.h>
#include "CreateDBWindow.h"

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent  : public juce::AudioAppComponent, public juce::Button::Listener
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


    // Í¨¹ý Listener ¼Ì³Ð
    virtual void buttonClicked(juce::Button* btn) override;

private:
    //==============================================================================
    // Your private member variables go here...
    juce::TextButton CreateDBButton;
    juce::TextButton CompDBButton;

    std::vector<std::unique_ptr<juce::DocumentWindow>> CreateDBComps;
    std::vector<std::unique_ptr<juce::DocumentWindow>> CompDBComps;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
