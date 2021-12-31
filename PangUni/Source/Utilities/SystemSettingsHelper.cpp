#include "SystemSettingsHelper.h"
#include "DatabaseHelper.h"

std::unique_ptr<juce::ApplicationProperties> SystemSettingsHelper::AppProperties = nullptr;

//[Get Settings]
juce::String SystemSettingsHelper::GetAppDataBasePath()
{
    return GetApplicationSettings()->getUserSettings()->getValue(SettingsKey_AppDataBasePath, juce::File::getSpecialLocation(juce::File::SpecialLocationType::userApplicationDataDirectory).getFullPathName());
}

bool SystemSettingsHelper::GetAutoTranslate()
{
    return GetApplicationSettings()->getUserSettings()->getBoolValue(SettingsKey_AutoTranslate, false);
}

juce::String SystemSettingsHelper::GetLanguage()
{
    return GetApplicationSettings()->getUserSettings()->getValue(SettingsKey_Language, "");
}
//[/Get Settings]

//[Set Settings]
void SystemSettingsHelper::SetAppDataBasePath(juce::String basePath)
{
    auto settings = GetApplicationSettings()->getUserSettings();
    settings->setValue(SettingsKey_AppDataBasePath, basePath);
    settings->saveIfNeeded();
}

void SystemSettingsHelper::SetAutoTranslate(bool autoTrans)
{
    auto settings = GetApplicationSettings()->getUserSettings();
    settings->setValue(SettingsKey_AutoTranslate, autoTrans);
    settings->saveIfNeeded();
}

void SystemSettingsHelper::SetLanguage(juce::String language)
{
    auto settings = GetApplicationSettings()->getUserSettings();
    settings->setValue(SettingsKey_Language, language);
    settings->saveIfNeeded();
}
//[/Set Settings]

juce::ApplicationProperties* SystemSettingsHelper::GetApplicationSettings()
{
    if (AppProperties == nullptr)
    {
        AppProperties.reset(new juce::ApplicationProperties());
        juce::PropertiesFile::Options options;
        options.applicationName = ProjectInfo::projectName;
        options.filenameSuffix = ".pxml";
        options.osxLibrarySubFolder = "Application Support";
        options.folderName = juce::File::getSpecialLocation(juce::File::userDocumentsDirectory).getFullPathName() + "\\Pang\\";
        options.storageFormat = juce::PropertiesFile::storeAsXML;
        AppProperties->setStorageParameters(options);
    }
    return AppProperties.get();
}

void SystemSettingsHelper::Clear()
{
    SystemSettingsHelper::AppProperties = nullptr;
    DatabaseHelper::CurrentFxDB = nullptr;
    DatabaseHelper::CurrentFx = nullptr;
}

juce::String SystemSettingsHelper::FilePathClear(juce::String path) {
#ifdef WIN32
    path = path.replace("////", "\\\\\\\\", true);
    path = path.replace("///", "\\\\\\", true);
    path = path.replace("//", "\\\\", true);
    path = path.replace("/", "\\", true);
#else
    path = path.replace("\\\\\\\\", "////", true);
    path = path.replace("\\\\\\", "///", true);
    path = path.replace("\\\\", "//", true);
    path = path.replace("\\", "/", true);
#endif
    return path;
}