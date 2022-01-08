#include "Fx.h"
#include "FxDB.h"

Fx::Fx()
{
    Infos.clear();

    Infos.push_back(new FxInfo(1, "FileName", ""));
    Infos.push_back(new FxInfo(2, "Description", ""));
}

Fx::Fx(juce::XmlElement* infosXMLNode, std::vector<FxInfo* > dbSchema)
{
    Infos.clear();
    for(auto key : dbSchema)
    {
        auto childNode = infosXMLNode->getChildByName(key->HeaderName);
        if (childNode != nullptr)
            Infos.push_back(new FxInfo(key->ColumnIndex, key->HeaderName, childNode->getAllSubText()));
        else
            Infos.push_back(new FxInfo(key->ColumnIndex, key->HeaderName));
    }
}

juce::File Fx::GetAudioFile()
{
    return juce::File(GetInfoValueByName("FileName")->Value);
}

juce::String Fx::GetAudioDescription()
{
    return juce::String(GetInfoValueByName("Description")->Value);
}

FxInfo* Fx::GetInfoValueByColumnID(int id)
{
    auto info = std::find_if(Infos.begin(), Infos.end(), [id](FxInfo* t) {return t->ColumnIndex == id; });
    if (info != std::end(Infos))
        return *info;
    else
        return nullptr;
}

void Fx::SetInfoValueByColumnID(int id, juce::String value)
{
    auto info = std::find_if(Infos.begin(), Infos.end(), [id](FxInfo* t) {return t->ColumnIndex == id; });
    if (info != std::end(Infos))
        (*info)->Value = value;
}

FxInfo* Fx::GetInfoValueByName(juce::String name)
{
    auto info = std::find_if(Infos.begin(), Infos.end(), [name](FxInfo* t) {return t->HeaderName == name; });
    if (info != std::end(Infos))
        return *info;
    else
        return nullptr;
}

void Fx::SetInfoValueByName(juce::String name, juce::String value)
{
    auto info = std::find_if(Infos.begin(), Infos.end(), [name](FxInfo* t) {return t->HeaderName == name; });
    if (info != std::end(Infos))
        (*info)->Value = value;
}

std::vector<FxInfo* > Fx::FindInfosByKeywords(juce::StringArray keywords)
{
    auto res = std::vector<FxInfo* >();
    for(auto element : Infos)
    {
        if (element->ContainKeywords(keywords))
            res.push_back(element);
    }
    return res;
}
