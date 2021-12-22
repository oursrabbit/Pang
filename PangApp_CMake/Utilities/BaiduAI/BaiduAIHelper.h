#pragma once
#include <JuceHeader.h>

class BaiduAIHelper
{
public:
    static juce::String GetAccess_Token();
    static juce::String TextTrans(juce::String text);
};