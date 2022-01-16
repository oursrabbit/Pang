/*
  ==============================================================================

    SearchDataStruct.h
    Created: 15 Jan 2022 4:18:18pm
    Author:  YC

  ==============================================================================
*/

#pragma once
#include "FxDB.h"
#include <JuceHeader.h>

class SearchDataStruct
{
public:
    std::vector<FxDB*> AllFxDBs;
    std::vector<Fx*> AllFxs;
    FxDB* CurrentFxDB;
    Fx* CurrentFx;
    juce::StringPairArray CurrentFxMetaData;

    SearchDataStruct();
    ~SearchDataStruct();
};