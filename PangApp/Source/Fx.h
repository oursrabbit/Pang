#pragma once
#include <JuceHeader.h>
#include "FxInfo.h"

class Fx
{
public:
    std::vector<FxInfo> Infos;
    juce::File AudioFile;

    Fx(juce::String audioFileBasePath, juce::XmlElement* infosXMLNode, std::vector<FxInfo> dbSchema);

    FxInfo* FindInfoByColumnID(int id);
    FxInfo* FindInfoByHeaderName(juce::String name);
    std::vector<FxInfo> FindInfoElementsByKeywords(juce::StringArray keywords);
    void SetValueByColumnID(int id, juce::String value);
};
