#pragma once
#include <JuceHeader.h>

#define SettingsKey juce::String

#define SettingsKey_Basic_Language "Language"
#define SettingsKey_Basic_AppDataBasePath "AppDataBasePath"
#define SettingsKey_Basic_AutoTranslate "AutoTranslate"

#define SettingsKey_AudioDevice_ManagerXML "AudioDeviceManagerXML"

#define SettingsKey_Spot_SampleRate "SpotSampleRate"
#define SettingsKey_Spot_BitDepth "SpotBitDepth"
#define SettingsKey_Spot_Channels "SpotChannels"
#define SettingsKey_Spot_OutputFolder "SpotOutputFolder"
#define SettingsKey_Spot_ResampleType "SpotResampleType"

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
    void GetAudioDevice(juce::AudioDeviceManager* audioDeviceManager);
    int GetSpotSampleRate();
    int GetSpotDepth();
    int GetSpotChannels();
    juce::String GetSpotOutputFolder();
    juce::String GetSpotResampleType();

    // Set Settings
    void SetAppDataBasePath(juce::String basePath); // same as SetAppDataBaseFolder
    void SetAppDataBaseFolder(juce::File basePathFolder); // same as SetAppDataBasePath
    void SetAutoTranslate(bool autoTrans);
    void SetLanguage(juce::String language);
    void SetAudioDevice(juce::AudioDeviceManager* device);
    void SetSpotSampleRate(int rate);
    void SetSpotDepth(int depth);
    void SetSpotChannels(int channels);
    void SetSpotOutputFolder(juce::String path);
    void SetSpotResampleType(juce::String typeName);
};