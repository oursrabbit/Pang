#pragma once
#include <JuceHeader.h>

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