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
    auto path = AppPropertiesFile->getValue(SettingsKey_Basic_AppDataBasePath, "");
    auto pathFile = juce::File::createFileWithoutCheckingPath(path);
    if (pathFile.existsAsFile())
        return juce::File::getSpecialLocation(juce::File::SpecialLocationType::userApplicationDataDirectory).getFullPathName();
    else
        return path;
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

int SystemSettingsHelper::GetSpotSampleRate()
{
    return AppPropertiesFile->getIntValue(SettingsKey_Spot_SampleRate, 48000);
}

int SystemSettingsHelper::GetSpotDepth()
{
    return AppPropertiesFile->getIntValue(SettingsKey_Spot_BitDepth, 24);
}

int SystemSettingsHelper::GetSpotChannels()
{
    return AppPropertiesFile->getIntValue(SettingsKey_Spot_Channels, 2);
}

juce::String SystemSettingsHelper::GetSpotOutputFolder()
{
    auto path = AppPropertiesFile->getValue(SettingsKey_Spot_OutputFolder, "");
    auto pathFile = juce::File::createFileWithoutCheckingPath(path);
    if (pathFile.existsAsFile())
        return juce::File::getSpecialLocation(juce::File::SpecialLocationType::userDocumentsDirectory).getFullPathName();
    else
        return path;
}

juce::String SystemSettingsHelper::GetSpotResampleType()
{
    return AppPropertiesFile->getValue(SettingsKey_Spot_ResampleType, "LinearInterpolator");
}

void SystemSettingsHelper::GetAudioDevice(juce::AudioDeviceManager* audioDeviceManager)
{
    auto stateXML = AppPropertiesFile->getXmlValue(SettingsKey_AudioDevice_ManagerXML);
    if (stateXML != nullptr)
    {
        audioDeviceManager->initialise(0, 2, stateXML.get(), true);
    }
    else
    {
        audioDeviceManager->initialiseWithDefaultDevices(0, 2);
    }
    if(audioDeviceManager->getCurrentAudioDevice() == nullptr)
        juce::AlertWindow::showMessageBoxAsync(juce::MessageBoxIconType::InfoIcon
            , TRANS("Message"), TRANS("Can't open audio device.") +  "\r\n\r\n" + TRANS("Go to setting window to reset."));
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

void SystemSettingsHelper::SetSpotSampleRate(int rate)
{
    AppPropertiesFile->setValue(SettingsKey_Spot_SampleRate, rate);
    AppPropertiesFile->saveIfNeeded();
}

void SystemSettingsHelper::SetSpotDepth(int depth)
{
    AppPropertiesFile->setValue(SettingsKey_Spot_BitDepth, depth);
    AppPropertiesFile->saveIfNeeded();
}

void SystemSettingsHelper::SetSpotChannels(int channels)
{
    AppPropertiesFile->setValue(SettingsKey_Spot_Channels, channels);
    AppPropertiesFile->saveIfNeeded();
}

void SystemSettingsHelper::SetSpotOutputFolder(juce::String path)
{
    AppPropertiesFile->setValue(SettingsKey_Spot_OutputFolder, path);
    AppPropertiesFile->saveIfNeeded();
}

void SystemSettingsHelper::SetSpotResampleType(juce::String typeName)
{
    AppPropertiesFile->setValue(SettingsKey_Spot_ResampleType, typeName);
    AppPropertiesFile->saveIfNeeded();
}

void SystemSettingsHelper::SetAudioDevice(juce::AudioDeviceManager* device)
{
    device->updateXml();
    auto xml = device->createStateXml();
    if (xml != nullptr)
    {
        auto xmlstring = xml->toString();
        AppPropertiesFile->setValue(SettingsKey_AudioDevice_ManagerXML, xml.get());
        AppPropertiesFile->saveIfNeeded();
    }
    else
    {
        AppPropertiesFile->setValue(SettingsKey_AudioDevice_ManagerXML, "");
        AppPropertiesFile->saveIfNeeded();
    }
}
//[/Set Settings]