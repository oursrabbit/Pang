/*
  ==============================================================================

    BaiduAIHelper.cpp
    Created: 12 Dec 2021 11:24:34am
    Author:  YC

  ==============================================================================
*/

#include "BaiduAIHelper.h"
#include "BaiduAI.h"


juce::String BaiduAIHelper::GetAccess_Token()
{
    return get_access_token();
}

juce::String BaiduAIHelper::TextTrans(juce::String text)
{
    return textTrans(text);
}
