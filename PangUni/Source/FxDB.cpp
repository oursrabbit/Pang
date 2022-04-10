#include "FxDB.h"

FxDB::FxDB()
{
    DBSchema.clear();
    Fxs.clear();
    FilteredFxs.clear();
    ComboboxItemID = 0;
    DatabaseFile = juce::File();

    DBSchema.push_back(new FxInfo(1, TRANS("FileName"), ""));
    DBSchema.push_back(new FxInfo(2, TRANS("Description"), ""));
    DBSchema.push_back(new FxInfo(3, TRANS("FileFullPath"), ""));
}

FxDB::FxDB(juce::File excelFile)
{
    this->LoadFxDBFromExcel(excelFile);
}

FxDB::FxDB(juce::File pxmlFile, int id)
{
    this->LoadFxDBFromPXML(pxmlFile, id);
}

void FxDB::LoadFxDBFromExcel(juce::File excelFile)
{
    // Clear
    DBSchema.clear();
    Fxs.clear();
    FilteredFxs.clear();

    // Combobox
    ComboboxItemID = 1;

    // FxDB
    DatabaseFile = excelFile;

    juce::StringArray lines;
    excelFile.readLines(lines);
    if (lines.size() < 2
        || !lines[1].contains("FileName")
        || !lines[1].contains("Description")
        || !lines[1].contains("FileFullPath"))
    {
        return;
    }
    else
    {
        // 1st. line for schema
        int columnIndex = 1;
        juce::StringArray headers;
        headers.addTokens(lines[1], "\t", "\"");
        for (auto tableHeader : headers)
        {
            DBSchema.push_back(new FxInfo(columnIndex++, tableHeader));
        }

        // from 2nd. line for data
        for (int i = 2; i < lines.size(); i++)
        {
            auto newFx = new Fx(lines[i], DBSchema);
            Fxs.push_back(newFx);
        }
        FilteredFxs = Fxs;
    }
}

void FxDB::LoadFxDBFromPXML(juce::File pxmlFile, int id)
{
    // Clear
    DBSchema.clear();
    Fxs.clear();
    FilteredFxs.clear();

    // Combobox
    ComboboxItemID = id;

    // FxDB
    DatabaseFile = pxmlFile;
    auto Pang = juce::XmlDocument::parse(pxmlFile);
    if (Pang == nullptr
        || Pang->getNumChildElements() < 1
        || Pang->getFirstChildElement()->getChildByName("FileName") == nullptr
        || Pang->getFirstChildElement()->getChildByName("Description") == nullptr
        || Pang->getFirstChildElement()->getChildByName("FileFullPath") == nullptr)
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
        FilteredFxs = Fxs;
    }
}

void FxDB::SerializationToPXML(juce::File pxmlFile)
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
    Pang.writeTo(pxmlFile);
}

void FxDB::SerializationToExcel(juce::File excelFile)
{
    excelFile.create();
    excelFile.appendText(juce::CharPointer_UTF8("\xe8\xaf\xb4\xe6\x98\x8e\xef\xbc\x88\xe6\xad\xa4\xe8\xa1\x8c\xe5\x8b\xbf\xe5\x88\xa0\xef\xbc\x89\xef\xbc\x9a""FileFullPath\xe3\x80\x81""FileName\xe5\x8f\x8a""Description\xe5\x88\x97\xe5\xbf\x85\xe9\xa1\xbb\xe5\xad\x98\xe5\x9c\xa8\xef\xbc\x8c\xe4\xb8\x94\xe9\xa1\xba\xe5\xba\x8f\xe4\xb8\x8d\xe5\x8f\xaf\xe6\x94\xb9\xe5\x8f\x98\xef\xbc\x8c\xe5\x85\xb6\xe4\xbb\x96\xe5\x88\x97\xe5\x8f\xaf\xe8\x87\xaa\xe8\xa1\x8c\xe6\xb7\xbb\xe5\x8a\xa0\xef\xbc\x8c\xe4\xbd\x86\xe5\x8f\xaa\xe8\x83\xbd\xe4\xbd\xbf\xe7\x94\xa8\xe8\x8b\xb1\xe6\x96\x87\xe5\xad\x97\xe7\xac\xa6\xef\xbc\x8c\xe4\xbf\x9d\xe5\xad\x98\xe6\x97\xb6\xe6\xa0\xbc\xe5\xbc\x8f\xe9\x80\x89\xe6\x8b\xa9\xe4\xb8\xba\"\xe6\x96\x87\xe6\x9c\xac\xe6\x96\x87\xe6\xa1\xa3(\xe5\x88\xb6\xe8\xa1\xa8\xe7\xac\xa6\xe9\x97\xb4\xe9\x9a\x94)(*.txt)\"\xe6\xa0\xbc\xe5\xbc\x8f\n"));
    auto itr = DBSchema.begin();
    excelFile.appendText((*itr)->HeaderName);
    itr++;
    for (; itr != DBSchema.end(); itr++)
    {
        excelFile.appendText("\t" + (*itr)->HeaderName);
    }
    excelFile.appendText("\n");
    for (auto fx = Fxs.begin(); fx != Fxs.end(); fx++)
    {
        auto info = DBSchema.begin();
        auto value = (*fx)->GetInfoValueByColumnID((*info)->ColumnIndex);
        auto text = value == nullptr ? "" : value->Value;
        excelFile.appendText(text);
        info++;
        for (; info != DBSchema.end(); info++)
        {
            auto value = (*fx)->GetInfoValueByColumnID((*info)->ColumnIndex);
            auto text = value == nullptr ? "" : value->Value;
            excelFile.appendText("\t" + text);
        }
        excelFile.appendText("\n");
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