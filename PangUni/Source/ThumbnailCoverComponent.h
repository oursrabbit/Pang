#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class ThumbnailCoverComponent : public juce::Component
{
public:
    ThumbnailCoverComponent();
    ~ThumbnailCoverComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ThumbnailCoverComponent)
};
