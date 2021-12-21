#include "FxDB.h"
#include "SystemSettingsHelper.h"

// id for combobox itemif, Start from 1, CANNOT BE 0
FxDB::FxDB(juce::File file, int id)
{
    // Reset or Default DB or NULL DB
    ComboboxItemID = id;
    DatabaseFile = file;
    DBSchema.clear();
    Fxs.clear();
    FilteredFxs.clear();
}

void FxDB::LoadDB()
{
    // Load Schema
    DBSchema.clear();
    auto databaseSchemaFile = juce::File(SystemSettingsHelper::GetAppDataBasePath() + SCHEMAPATH);
    if (databaseSchemaFile.exists())
    {
        auto databaseSchema = juce::XmlDocument::parse(databaseSchemaFile);

        int columnIndex = 1;

        for (auto tableHeader : databaseSchema->getChildByName(XML_FXROOT_NODENAME)->getChildIterator())
        {
            FxInfo newHeader(columnIndex++, tableHeader->getTagName());
            DBSchema.push_back(newHeader);
        }
    }

    // Load DB and ALL Fxs
    Fxs.clear();
    FilteredFxs.clear();
    if (DatabaseFile.exists())
    {
        auto fxXMLData = juce::XmlDocument::parse(DatabaseFile);
        auto audioFileBasePath = fxXMLData->getChildByName(XML_FXAUDIOBASEPATH_NODENAME)->getAllSubText();
        auto SoundEffectInfos = fxXMLData->getChildByName(XML_FXINFO_NODENAME);
        for (auto FXInfoXML : SoundEffectInfos->getChildIterator())
        {
            Fx newFx(audioFileBasePath, FXInfoXML, DBSchema);
            Fxs.push_back(newFx);
            FilteredFxs.push_back(newFx);
        }
    }

    // Try to Open File(for local network)
    if (Fxs.size() > 0)
    {
        juce::AudioFormatManager manager;
        manager.registerBasicFormats();
        auto* reader = manager.createReaderFor(Fxs[0].AudioFile);
        delete reader;
        reader = nullptr;
    }
}

void FxDB::ResetFilter()
{
    FilteredFxs = Fxs;
}

void FxDB::SetFilter(juce::StringArray keywords)
{
    auto res = std::vector<Fx>();
    for each (auto info in FilteredFxs)
    {
        if (info.FindInfoElementsByKeywords(keywords).size() != 0)
            res.push_back(info);
    }
    FilteredFxs = res;
}