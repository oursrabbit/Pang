#pragma once
#include <JuceHeader.h>
#include "SystemSettingsHelper.h"

enum LanguageEnum
{
    English,
    Chinese
};

LanguageEnum GetLanguageEnumFirst()
{
    return LanguageEnum::English;
}

LanguageEnum GetLanguageEnumLast()
{
    return LanguageEnum::Chinese;
}

juce::String GetLanguageEnumString(LanguageEnum value)
{
    switch (value)
    {
    case LanguageEnum::English:
        return TRANS("English");
    case LanguageEnum::Chinese:
        return TRANS("Chinese");
    default:
        return "";
    }
}

LanguageEnum GetLanguageEnum(juce::String value)
{
    if (value == "Chinese")
        return LanguageEnum::Chinese;
    else
        return LanguageEnum::English;
}

juce::File GetLanguageFontFile(LanguageEnum value)
{
    switch (value)
    {
    case English:
        return juce::File();
    case Chinese:
        return juce::File(SystemSettingsHelper::GetAppDataBasePath()).getChildFile("TRANS").getChildFile("zh.ttf");
        break;
    default:
        return juce::File();
    }
}

juce::File GetLanguageFontFile(juce::String value)
{
    return GetLanguageFontFile(GetLanguageEnum(value));
}