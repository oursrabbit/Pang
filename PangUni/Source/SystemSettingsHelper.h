#pragma once
#include <JuceHeader.h>

#define SettingsKey juce::String

#define SettingsKey_Basic_Language "Language"
#define SettingsKey_Basic_AppDataBasePath "AppDataBasePath"
#define SettingsKey_Basic_AutoTranslate "AutoTranslate"

#define SettingsKey_AudioDevice_ManagerXML "AudioDeviceManagerXML"
class SystemSettingsHelper
{
public:
    std::unique_ptr<juce::ApplicationProperties> AppProperties;
    juce::PropertiesFile* AppPropertiesFile;

    SystemSettingsHelper();
    ~SystemSettingsHelper();

    // Get Settings
    juce::String GetAppDataBasePath(); // same as GetAppDataBaseFolder
    juce::File GetAppDataBaseFolder(); // same as GetAppDataBasePath
    bool GetAutoTranslate();
    juce::String GetLanguage();
    juce::uint64 GetSpotSampleRate();
    juce::uint32 GetSpotDepth();
    void GetAudioDevice(juce::AudioDeviceManager* audioDeviceManager);

    // Set Settings
    void SetAppDataBasePath(juce::String basePath); // same as SetAppDataBaseFolder
    void SetAppDataBaseFolder(juce::File basePathFolder); // same as SetAppDataBasePath
    void SetAutoTranslate(bool autoTrans);
    void SetLanguage(juce::String language);
    void SetSpotSampleRate(juce::uint64 rate);
    void SetSpotDepth(juce::uint32 depth);
    void SetAudioDevice(juce::AudioDeviceManager* device);
};