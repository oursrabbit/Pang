#include "SystemSettingsHelper.h"

SystemSettingsHelper::SystemSettingsHelper()
{
    AppProperties.reset(new juce::ApplicationProperties());
    juce::PropertiesFile::Options options;
    options.applicationName = ProjectInfo::projectName;
    options.filenameSuffix = ".pxml";
    options.osxLibrarySubFolder = "Application Support";
    options.folderName = juce::File::getSpecialLocation(juce::File::userDocumentsDirectory).getFullPathName() + "\\Pang\\";
    options.storageFormat = juce::PropertiesFile::storeAsXML;
    AppProperties->setStorageParameters(options);

    AppPropertiesFile = AppProperties->getUserSettings();
}

SystemSettingsHelper::~SystemSettingsHelper()
{
    AppProperties = nullptr;
    AppPropertiesFile = nullptr;
}

//[Get Settings]
juce::String SystemSettingsHelper::GetAppDataBasePath()
{
    return AppPropertiesFile->getValue(SettingsKey_Basic_AppDataBasePath, juce::File::getSpecialLocation(juce::File::SpecialLocationType::userApplicationDataDirectory).getFullPathName());
}

juce::File SystemSettingsHelper::GetAppDataBaseFolder()
{
    return juce::File(SystemSettingsHelper::GetAppDataBasePath());
}

bool SystemSettingsHelper::GetAutoTranslate()
{
    return AppPropertiesFile->getBoolValue(SettingsKey_Basic_AutoTranslate, false);
}

juce::String SystemSettingsHelper::GetLanguage()
{
    return AppPropertiesFile->getValue(SettingsKey_Basic_Language, "");
}

juce::uint64 SystemSettingsHelper::GetSpotSampleRate()
{
    return 48000;
}

juce::uint32 SystemSettingsHelper::GetSpotDepth()
{
    return 16;
}

juce::AudioDeviceManager* SystemSettingsHelper::GetAudioDevice()
{
    std::unique_ptr<juce::AudioDeviceManager> manager;
    manager.reset(new juce::AudioDeviceManager());
    auto stateXML = AppPropertiesFile->getXmlValue(SettingsKey_AudioDevice_ManagerXML);
    auto error = manager->initialise(0, 2, stateXML.get(), false);
    error = manager->initialiseWithDefaultDevices(0, 2);
    return new juce::AudioDeviceManager();
}
//[/Get Settings]

//[Set Settings]
void SystemSettingsHelper::SetAppDataBasePath(juce::String basePath)
{
    AppPropertiesFile->setValue(SettingsKey_Basic_AppDataBasePath, basePath);
    AppPropertiesFile->saveIfNeeded();
}

void SystemSettingsHelper::SetAppDataBaseFolder(juce::File basePathFolder)
{
    SetAppDataBasePath(basePathFolder.getFullPathName());
}

void SystemSettingsHelper::SetAutoTranslate(bool autoTrans)
{
    AppPropertiesFile->setValue(SettingsKey_Basic_AutoTranslate, autoTrans);
    AppPropertiesFile->saveIfNeeded();
}

void SystemSettingsHelper::SetLanguage(juce::String language)
{
    AppPropertiesFile->setValue(SettingsKey_Basic_Language, language);
    AppPropertiesFile->saveIfNeeded();
}

void SystemSettingsHelper::SetSpotSampleRate(juce::uint64 rate)
{
}

void SystemSettingsHelper::SetSpotDepth(juce::uint32 depth)
{
}

void SystemSettingsHelper::SetAudioDevice(juce::AudioDeviceManager* audioDevice)
{
}
//[/Set Settings]