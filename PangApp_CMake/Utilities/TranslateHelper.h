#pragma once
#include <JuceHeader.h>

#define LanguageID_English 1
#define Language_English "English"

#define LanguageID_Chinese 2
#define Language_Chinese "Chinese"

#define Language_English_TransFifle ""
#define Language_Chinese_TransFifle "\\TRANS\\zh.txt"

class TranslateHelper
{
public:
    static juce::StringArray GetAllLanguage();
    static juce::File GetTransFileByLanguage(juce::String language);
    static juce::String GetLanguageByID(int id);
    static int GetIDByLanguage(juce::String language);
};