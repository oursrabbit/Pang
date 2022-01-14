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

FxDB::FxDB(juce::File file, int id, bool none)
{
    // Clear
    DBSchema.clear();
    Fxs.clear();

    // Combobox
    ComboboxItemID = id;

    // FxDB
    DatabaseFile = file;

    juce::StringArray lines;
    file.readLines(lines);
    if (lines.size() < 1
        || !lines[0].contains("FileName")
        || !lines[0].contains("Description"))
    {
        return;
    }
    else
    {
        // 1st. line for schema
        int columnIndex = 1;
        juce::StringArray headers;
        headers.addTokens(lines[0], "\t", "\"");
        for (auto tableHeader : headers)
        {
            DBSchema.push_back(new FxInfo(columnIndex++, tableHeader));
        }

        for (int i = 1; i < lines.size(); i++)
        {
            auto newFx = new Fx(lines[i], DBSchema);
            Fxs.push_back(newFx);
        }
    }
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
    auto Pang = juce::XmlDocument::parse(file);
    if (Pang == nullptr
        || Pang->getNumChildElements() < 1
        || Pang->getFirstChildElement()->getChildByName("FileName") == nullptr
        || Pang->getFirstChildElement()->getChildByName("Description") == nullptr)
    {
        return;
    }
    else
    {
        // 0 node for schema
        int columnIndex = 1;
        for (auto tableHeader : Pang->getFirstChildElement()->getChildIterator())
        {
            DBSchema.push_back(new FxInfo(columnIndex++, tableHeader->getTagName()));
        }

        for (int i = 1; i < Pang->getNumChildElements(); i++)
        {
            auto SoundEffect = Pang->getChildElement(i);
            auto newFx = new Fx(SoundEffect, DBSchema);
            Fxs.push_back(newFx);
        }
    }
}

void FxDB::Serialization(juce::File file)
{
    juce::XmlElement Pang("Pang");
    // First node for schema
    auto Schema = Pang.createNewChildElement("SoundEffect");
    for (auto itr = DBSchema.begin(); itr != DBSchema.end(); itr++)
    {
        Schema->createNewChildElement((*itr)->HeaderName);
    }
    // Real Fxs start from the second node
    for (auto fx = Fxs.begin(); fx != Fxs.end(); fx++)
    {
        auto SoundEffect = Pang.createNewChildElement("SoundEffect");
        for (auto info = DBSchema.begin(); info != DBSchema.end(); info++)
        {
            auto SoundEffectInfoNode = SoundEffect->createNewChildElement((*info)->HeaderName);
            auto value = (*fx)->GetInfoValueByColumnID((*info)->ColumnIndex);
            auto text = value == nullptr ? "" : value->Value;
            SoundEffectInfoNode->addTextElement(text);
        }
    }
    Pang.writeTo(file);
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