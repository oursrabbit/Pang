#include "TranslateHelper.h"

juce::StringArray TranslateHelper::GetAllLanguage()
{
    auto languages = juce::StringArray();
    languages.add(Language_English);
    languages.add(Language_Chinese);
	return languages;
}

juce::File TranslateHelper::GetTransFileByLanguage(juce::File appDataPath, juce::String language)
{
    juce::File file;

    if (language == Language_Chinese)
    {
        file = appDataPath.getChildFile("TRANS").getChildFile("zh.txt");
#ifdef WIN32
        juce::LookAndFeel_V4::getDefaultLookAndFeel().setDefaultSansSerifTypefaceName("STKaiti");
#else
        juce::LookAndFeel_V4::getDefaultLookAndFeel().setDefaultSansSerifTypefaceName("Kai");
#endif // 
    }

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