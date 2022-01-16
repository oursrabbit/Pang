#pragma once
#include <JuceHeader.h>

class BaiduAIHelper
{
public:
	juce::String GetAccess_Token();
	juce::String TextTrans(juce::String text);
};