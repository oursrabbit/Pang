/*
  ==============================================================================

    DatabaseHelper.h
    Created: 3 Dec 2021 3:21:30pm
    Author:  庞兴庆

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

#define SettingsKey_Language "Language"
#define SettingsKey_AppDataBasePath "AppDataBasePath"
#define SettingsKey_AutoTranslate "AutoTranslate"

class SystemSettingsHelper
{
public:
    enum LanguageEnum
    {
        English = 1,
        Chinese
    };

    static LanguageEnum GetLanguageEnumFirst()
    {
        return LanguageEnum::English;
    }

    static LanguageEnum GetLanguageEnumLast()
    {
        return LanguageEnum::Chinese;
    }

    static juce::String GetLanguageEnumString(LanguageEnum value)
    {
        switch (value)
        {
        case SystemSettingsHelper::English:
            return TRANS("English");
        case SystemSettingsHelper::Chinese:
            return TRANS("Chinese");
        default:
            return "";
        }
    }

    static std::unique_ptr<juce::ApplicationProperties> AppProperties;

    static juce::ApplicationProperties* GetApplicationSettings()
    {
        if (AppProperties == nullptr)
        {
            AppProperties.reset(new juce::ApplicationProperties());
            juce::PropertiesFile::Options options;
            options.applicationName = ProjectInfo::projectName;
            options.filenameSuffix = ".settings";
            options.osxLibrarySubFolder = "Application Support";
            options.folderName = options.getDefaultFile().getFullPathName();
            options.storageFormat = juce::PropertiesFile::storeAsXML;
            AppProperties->setStorageParameters(options);
        }
        return AppProperties.get();
    }

    static void SetApplicationSettings(juce::String key, juce::var value)
    {
        auto settings = GetApplicationSettings()->getUserSettings();
        settings->setValue(key, value);
        settings->saveIfNeeded();
    }

    static LanguageEnum GetLanguage()
    {
        return (SystemSettingsHelper::LanguageEnum)(GetApplicationSettings()->getUserSettings()->getIntValue(SettingsKey_Language, SystemSettingsHelper::English));
    }

    static juce::String GetAppDataBasePath()
    {
        return GetApplicationSettings()->getUserSettings()->getValue(SettingsKey_AppDataBasePath, juce::File::getSpecialLocation(juce::File::SpecialLocationType::userApplicationDataDirectory).getFullPathName());
    }

    static bool GetAutoTranslate()
    {
        return GetApplicationSettings()->getUserSettings()->getBoolValue(SettingsKey_AutoTranslate, false);
    }
};

class DatabaseHelper
{
public:
    static std::map<int, juce::File> databaseFiles;
    static std::map<int, juce::String> databaseHeaderIndexSchema;

    static juce::String fileBasePath;
    // Start Form 1
    static std::vector<std::map<int, juce::String>> FXInfos;
    static std::vector<std::map<int, juce::String>> FilteredFxInfos;



    static void LoadAllDatabase()
    {
        auto databaseSchemaFile = juce::File(SystemSettingsHelper::GetAppDataBasePath() + "\\Pang\\DB\\Template\\PXMLSchema.pxml");
        if (databaseSchemaFile.exists())
        {
            auto databaseSchema = juce::XmlDocument::parse(databaseSchemaFile);

            int columnIndex = 1;
            databaseHeaderIndexSchema.clear();
            for (auto tableHeader : databaseSchema->getChildByName("SoundEffect")->getChildIterator())
            {
                DatabaseHelper::databaseHeaderIndexSchema[columnIndex++] = tableHeader->getTagName();
            }

            juce::File databasePath = juce::File(SystemSettingsHelper::GetAppDataBasePath() + "\\Pang\\DB\\");
            auto dbF = databasePath.findChildFiles(juce::File::findFiles, false, "*.pxml");
            DatabaseHelper::databaseFiles.clear();
            for (int i = 0; i < dbF.size(); ++i)
            {
                DatabaseHelper::databaseFiles[i] = dbF[i];
            }
        }
    }

    static void LoadDatabase(int index)
    {
        auto databaseFile = databaseFiles[index];
        if (databaseFile.exists())
        {
            DatabaseHelper::FXInfos.clear();
            DatabaseHelper::FilteredFxInfos.clear();
            auto tutorialData = juce::XmlDocument::parse(databaseFile);

            fileBasePath = tutorialData->getChildByName("BasePath")->getAllSubText();
            auto SoundEffectInfos = tutorialData->getChildByName("SoundEffectInfos");
            for (auto FXInfoXML : SoundEffectInfos->getChildIterator())
            {
                auto FXInfo = std::map<int, juce::String>();
                for each (auto key in DatabaseHelper::databaseHeaderIndexSchema)
                {
                    auto childNode = FXInfoXML->getChildByName(key.second);
                    if (childNode != nullptr)
                    {
                        FXInfo[key.first] = FXInfoXML->getChildByName(key.second)->getAllSubText();
                    }
                    else
                    {
                        FXInfo[key.first] = "";
                    }
                }
                DatabaseHelper::FXInfos.push_back(FXInfo);
                DatabaseHelper::FilteredFxInfos.push_back(FXInfo);
            }
        }
    }

    //static void Find(juce::String keyword)
    //{
    //    std::vector<SoundEffectInfo> res;
    //    for each (auto FX in DatabaseHelper::FilteredFxInfos)
    //    {
    //        if(FX.FileName.contains(keyword) || FX.Description.contains(keyword))
    //            res.push_back(FX);
    //    }
    //    DatabaseHelper::FilteredFxInfos = res;
    //}

    //static void RsetDatabase()
    //{
    //    DatabaseHelper::FilteredFxInfos.clear();
    //    for each (auto FX in DatabaseHelper::FXInfos)
    //    {
    //        DatabaseHelper::FilteredFxInfos.push_back(FX);
    //    }
    //}
};