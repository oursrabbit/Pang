#include "LanguageHelper.h"

LanguageHelper::LanguageHelper()
{
}

LanguageHelper::~LanguageHelper()
{
}

juce::String LanguageHelper::GetLanguageEnumString(int value)
{
	switch (value)
	{
	case LanguageHelper::English:
		return "English";
	case LanguageHelper::Chinese:
		return "Chinese";
	default:
		return "English";
	}
}

juce::String LanguageHelper::GetLanguageEnumString(LanguageEnum value)
{
	switch (value)
	{
	case LanguageHelper::English:
		return "English";
	case LanguageHelper::Chinese:
		return "Chinese";
	default:
		return "English";
	}
}

LanguageHelper::LanguageEnum LanguageHelper::GetLanguageEnum(juce::String value)
{
	if (value == "Chinese")
		return LanguageEnum::Chinese;
	else
		return LanguageEnum::English;
}

juce::File LanguageHelper::GetTransFileByLanguage(juce::File appDataPath, juce::String language)
{
	return GetTransFileByLanguage(appDataPath, GetLanguageEnum(language));
}

juce::File LanguageHelper::GetTransFileByLanguage(juce::File appDataPath, int languageID)
{
	return GetTransFileByLanguage(appDataPath, (LanguageEnum)languageID);
}

juce::File LanguageHelper::GetTransFileByLanguage(juce::File appDataPath, LanguageEnum language)
{
	juce::File file;
	if (language == LanguageEnum::Chinese)
	{
		juce::LocalisedStrings::setCurrentMappings(new juce::LocalisedStrings(transFile, false));
	}
	return file;
}
