#pragma once
#include <JuceHeader.h>

class LanguageHelper
{
public:

    int LanguageEnumSize = 2;
    enum LanguageEnum
    {
        English = 1,        // ID:1, "English"
        Chinese = 2         // ID:2, "Chinese"
    };

    LanguageHelper();
    ~LanguageHelper();

    juce::String GetLanguageEnumString(int value);
    juce::String GetLanguageEnumString(LanguageEnum value);
    LanguageEnum GetLanguageEnum(juce::String value);

    juce::File GetTransFileByLanguage(juce::File appDataPath, juce::String language);
    juce::File GetTransFileByLanguage(juce::File appDataPath, int languageID);
    juce::File GetTransFileByLanguage(juce::File appDataPath, LanguageEnum language);
};