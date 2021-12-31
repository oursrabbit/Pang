#include "Fx.h"
#include "FxDB.h"

Fx::Fx(juce::String audioFileBasePath, juce::XmlElement* infosXMLNode, std::vector<FxInfo> dbSchema)
{
    Infos.clear();
    for(auto key : dbSchema)
    {
        auto childNode = infosXMLNode->getChildByName(key.HeaderName);
        if (childNode != nullptr)
            Infos.push_back(FxInfo(key.ColumnIndex, key.HeaderName, childNode->getAllSubText()));
        else
            Infos.push_back(FxInfo(key.ColumnIndex, key.HeaderName));
    }

    auto fileInfo = std::find_if(Infos.begin(), Infos.end(), [](FxInfo t) {return t.HeaderName == XML_FILENAME_NODENAME; });
    if (fileInfo != Infos.end())
    {
        AudioFile = juce::File(audioFileBasePath).getChildFile(fileInfo->Value);
    }
}

FxInfo* Fx::FindInfoByColumnID(int id)
{
    auto info = std::find_if(Infos.begin(), Infos.end(), [id](FxInfo t) {return t.ColumnIndex == id; });
    if (info != std::end(Infos))
        return &(*info);
    else
        return nullptr;
}

FxInfo* Fx::FindInfoByHeaderName(juce::String name)
{
    auto info = std::find_if(Infos.begin(), Infos.end(), [name](FxInfo t) {return t.HeaderName == name; });
    if (info != std::end(Infos))
        return &(*info);
    else
        return nullptr;
}

std::vector<FxInfo> Fx::FindInfoElementsByKeywords(juce::StringArray keywords)
{
    auto res = std::vector<FxInfo>();
    for(auto element : Infos)
    {
        if (element.ContainKeywords(keywords))
            res.push_back(element);
    }
    return res;
}


void Fx::SetValueByColumnID(int id, juce::String value)
{
    auto info = std::find_if(Infos.begin(), Infos.end(), [id](FxInfo t) {return t.ColumnIndex == id; });
    if (info != std::end(Infos))
        info->Value = value;
}
