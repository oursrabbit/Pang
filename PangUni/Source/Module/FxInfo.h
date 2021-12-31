#pragma once
#include <JuceHeader.h>

class FxInfo
{
public:
    // Juce Table Column, Column ID start from 1, CANNOT BE 0
    int ColumnIndex;
    // Juce Table Header String, alse be XML Node Name
    juce::String HeaderName;
    // XML Node String, in Node String
    juce::String Value;

    // juce table column index, start from 1, CANNOT BE 0
    FxInfo(int index, juce::String name = "", juce::String value = "");
    bool ContainKeywords(juce::StringArray keywords);
};