#pragma once
#include <JuceHeader.h>

#define SettingsKey juce::String

#define SettingsKey_Language "Language"
#define SettingsKey_AppDataBasePath "AppDataBasePath"
#define SettingsKey_AutoTranslate "AutoTranslate"

class SystemSettingsHelper
{
public:
    static std::unique_ptr<juce::ApplicationProperties> AppProperties;
    static juce::ApplicationProperties* GetApplicationSettings();
    static void Clear();
    // Get Settings
    static juce::String GetAppDataBasePath();
    static bool GetAutoTranslate();
    static juce::String GetLanguage();

    // Set Settings
    static void SetAppDataBasePath(juce::String basePath);
    static void SetAutoTranslate(bool autoTrans);
    static void SetLanguage(juce::String language);
};