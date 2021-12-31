#include "FxInfo.h"

// juce table column index, start from 1, CANNOT BE 0
FxInfo::FxInfo(int index, juce::String name, juce::String value)
{
    ColumnIndex = index;
    HeaderName = name;
    Value = value;
}

bool FxInfo::ContainKeywords(juce::StringArray keywords)
{
    for(auto kw : keywords)
    {
        if (Value.containsIgnoreCase(kw))
            return true;
    }
    return false;
}