#include "FxDB.h"

FxDB::FxDB()
{
    DBSchema.clear();
    Fxs.clear();
    ComboboxItemID = 0;
    DatabaseFile = juce::File();

    DBSchema.push_back(new FxInfo(1, TRANS("FileName"), ""));
    DBSchema.push_back(new FxInfo(2, TRANS("Description"), ""));
}

FxDB::FxDB(juce::File file, int id)
{
    // Clear
    DBSchema.clear();
    Fxs.clear();

    // Combobox
    ComboboxItemID = id;

    // FxDB
    DatabaseFile = file;

    auto fxXMLData = juce::XmlDocument::parse(file);
    auto SoundEffectInfos = fxXMLData->getChildByName("Pang");
    if (SoundEffectInfos == nullptr
        || SoundEffectInfos->getNumChildElements() < 1
        || SoundEffectInfos->getFirstChildElement()->getChildByName("FileName") == nullptr
        || SoundEffectInfos->getFirstChildElement()->getChildByName("Description") == nullptr)
    {
        return;
    }
    else
    {
        // 0 node for schema
        int columnIndex = 1;
        for (auto tableHeader : SoundEffectInfos->getFirstChildElement()->getChildIterator())
        {
            DBSchema.push_back(new FxInfo(columnIndex++, tableHeader->getTagName()));
        }

        for (int i = 1; i < SoundEffectInfos->getNumChildElements(); i++)
        {
            auto fxInfoXML = SoundEffectInfos->getChildElement(i);
            auto newFx = new Fx(fxInfoXML, DBSchema);
            Fxs.push_back(newFx);
        }
    }
}


void FxDB::FindFxByKeywords(juce::StringArray keywords)
{
    auto res = std::vector<Fx* >();
    for(auto info : Fxs)
    {
        if (info->FindInfosByKeywords(keywords).size() != 0)
            res.push_back(info);
    }
    FilteredFxs = res;
}