#include "TranslateHelper.h"
#include "SystemSettingsHelper.h"

juce::StringArray TranslateHelper::GetAllLanguage()
{
    auto languages = juce::StringArray();
    languages.add(Language_English);
    languages.add(Language_Chinese);
	return languages;
}

juce::File TranslateHelper::GetTransFileByLanguage(juce::String language)
{
    juce::File file;

    if (language == Language_Chinese)
        file = juce::File(SystemSettingsHelper::GetAppDataBasePath()).getChildFile("TRANS").getChildFile("zh.txt");

    return file;
}

juce::String TranslateHelper::GetLanguageByID(int id)
{
    switch (id)
    {
    case LanguageID_Chinese:
        return Language_Chinese;
    default:
        return Language_English;
    }
}

int TranslateHelper::GetIDByLanguage(juce::String language)
{
    if (language == Language_Chinese)
        return LanguageID_Chinese;
    return LanguageID_English;
}
