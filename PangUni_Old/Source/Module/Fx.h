#pragma once
#include <JuceHeader.h>
#include "FxInfo.h"

class Fx
{
public:
    std::vector<FxInfo* > Infos;

    Fx();
    Fx(juce::XmlElement* infosXMLNode, std::vector<FxInfo* > dbSchema);

    juce::File GetAudioFile();
    juce::String GetAudioDescription();

    // Table
    FxInfo* GetInfoValueByColumnID(int id);
    void SetInfoValueByColumnID(int id, juce::String value);
    FxInfo* GetInfoValueByName(juce::String name);
    void SetInfoValueByName(juce::String name, juce::String value);
    
    // Search
    std::vector<FxInfo* > FindInfosByKeywords(juce::StringArray keywords);
};
