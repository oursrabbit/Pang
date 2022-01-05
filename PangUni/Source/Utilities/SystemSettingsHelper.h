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
    static juce::String FilePathClear(juce::String path);

    // Get Settings
    static juce::String GetAppDataBasePath();
    static bool GetAutoTranslate();
    static juce::String GetLanguage();
    static juce::uint64 GetSpotSampleRate();
    static juce::uint32 GetSpotDepth();

    // Set Settings
    static void SetAppDataBasePath(juce::String basePath);
    static void SetAutoTranslate(bool autoTrans);
    static void SetLanguage(juce::String language);
    static void SetSpotSampleRate(juce::uint64 rate);
    static void SetSpotDepth(juce::uint32 depth);
};