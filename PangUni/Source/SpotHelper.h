#pragma once
#include <JuceHeader.h>

class SpotHelper
{
public:
    SpotHelper();
    ~SpotHelper();

    void GetDAWName(juce::StringArray &daw);
    int SpotToProTools(juce::File audioFile, juce::int64 startSample, juce::int64 endSample);
};