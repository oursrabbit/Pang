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

class FxInfoElement
{
public:
    int ColumnIndex;
    juce::String HeaderName;
    juce::String Value;

    FxInfoElement(int index, juce::String name = "", juce::String value = "")
    {
        ColumnIndex = index;
        HeaderName = name;
        Value = value;
    }

    bool ContainKeywords(juce::StringArray keywords)
    {
        for each (auto kw in keywords)
        {
            return Value.containsIgnoreCase(kw);
        }
        return false;
    }
};

class FxInfo
{
public:
    std::vector<FxInfoElement> Infos;
    juce::File AudioFile;

    FxInfoElement* FindInfoByColumnID(int id)
    {
        auto info = std::find_if(Infos.begin(), Infos.end(), [id](FxInfoElement t) {return t.ColumnIndex == id;});
        if (info != std::end(Infos))
            return info._Ptr;
        else
            return nullptr;
    }

    FxInfoElement* FindInfoByHeaderName(juce::String name)
    {
        auto info = std::find_if(Infos.begin(), Infos.end(), [name](FxInfoElement t) {return t.HeaderName == name;});
        if (info != std::end(Infos))
            return info._Ptr;
        else
            return nullptr;
    }

    std::vector<FxInfoElement> FindInfoElementsByKeywords(juce::StringArray keywords)
    {
        auto res = std::vector<FxInfoElement>();
        for each (auto element in Infos)
        {
            if (element.ContainKeywords(keywords))
                res.push_back(element);
        }
        return res;
    }

    void SetValueByColumnID(int id, juce::String value)
    {
        auto info = std::find_if(Infos.begin(), Infos.end(), [id](FxInfoElement t) {return t.ColumnIndex == id; });
        if (info != std::end(Infos))
            info->Value = value;
    }
};

class FxDB
{
public:
    static juce::String SchemaPath;
    static juce::String DBPath;
    static std::vector<FxInfoElement> DBSchema;
    
    int ItemID;
    juce::String FileBasePath;
    std::vector<FxInfo> Fxs;
    std::vector<FxInfo> FilteredFxs;
    juce::File RowFile;

    FxDB(juce::File dbFile, int id)
    {
        ItemID = id;
        RowFile = dbFile;
        Fxs.clear();
        FileBasePath = "";
    }

    void Load()
    {
        Fxs.clear();
        FilteredFxs.clear();
        FileBasePath = "";
        if (RowFile.exists())
        {
            auto tutorialData = juce::XmlDocument::parse(RowFile);
            FileBasePath = tutorialData->getChildByName("BasePath")->getAllSubText();
            auto SoundEffectInfos = tutorialData->getChildByName("SoundEffectInfos");
            for (auto FXInfoXML : SoundEffectInfos->getChildIterator())
            {
                FxInfo newFx;
                newFx.Infos.clear();
                for each (auto key in FxDB::DBSchema)
                {
                    auto childNode = FXInfoXML->getChildByName(key.HeaderName);
                    if (childNode != nullptr)
                    {
                        newFx.Infos.push_back(FxInfoElement(key.ColumnIndex, key.HeaderName, childNode->getAllSubText()));
                    }
                    else
                    {
                        newFx.Infos.push_back(FxInfoElement(key.ColumnIndex, key.HeaderName));
                    }
                }
                Fxs.push_back(newFx);
                FilteredFxs.push_back(newFx);
            }
        }
    }

    void ResetFilter()
    {
        FilteredFxs = Fxs;
    }

    void SetFilter(juce::StringArray keywords)
    {
        auto res = std::vector<FxInfo>();
        for each (auto info in FilteredFxs)
        {
            if (info.FindInfoElementsByKeywords(keywords).size() != 0)
                res.push_back(info);
        }
        FilteredFxs = res;
    }
};

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
    static std::vector<FxDB> DatabaseFiles;
    static FxDB* CurrentFxDB;
    static FxInfo* CurrentFx;

    static void LoadAllFxDatabase()
    {
        // Load Schema
        auto databaseSchemaFile = juce::File(SystemSettingsHelper::GetAppDataBasePath() + FxDB::SchemaPath);
        if (databaseSchemaFile.exists())
        {
            auto databaseSchema = juce::XmlDocument::parse(databaseSchemaFile);

            int columnIndex = 1;
            FxDB::DBSchema.clear();
            for (auto tableHeader : databaseSchema->getChildByName("SoundEffect")->getChildIterator())
            {
                FxInfoElement newHeader(columnIndex++, tableHeader->getTagName());
                FxDB::DBSchema.push_back(newHeader);
            }

            // Load DatabaseList
            juce::File databasePath = juce::File(SystemSettingsHelper::GetAppDataBasePath() + FxDB::DBPath);
            auto dbF = databasePath.findChildFiles(juce::File::findFiles, false, "*.pxml");
            DatabaseHelper::DatabaseFiles.clear();
            for (int i = 0; i < dbF.size(); ++i)
            {
                DatabaseHelper::DatabaseFiles.push_back(FxDB(dbF[i], i + 1));
            }
        }
    }

    static void LoadFxDatabase(int id)
    {
        auto fxdb = std::find_if(std::begin(DatabaseHelper::DatabaseFiles), std::end(DatabaseHelper::DatabaseFiles), [id](FxDB t) { return t.ItemID == id; });
        if (fxdb != std::end(DatabaseHelper::DatabaseFiles))
        {
            fxdb->Load();
            CurrentFxDB = fxdb._Ptr;
        }
    }

    static void LoadFxFile(int index)
    {
        delete CurrentFx;
        CurrentFx = nullptr;
        if (CurrentFxDB != nullptr)
        {
            auto fx = CurrentFxDB->Fxs[index];
            fx.OpenFlie();
        }
    }
};