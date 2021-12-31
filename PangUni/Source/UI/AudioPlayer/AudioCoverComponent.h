#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class AudioCoverComponent  : public juce::Component
{
public:
    AudioCoverComponent();
    ~AudioCoverComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AudioCoverComponent)
};
