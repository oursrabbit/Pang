/*
  ==============================================================================

    SearchDataStruct.cpp
    Created: 15 Jan 2022 4:18:18pm
    Author:  YC

  ==============================================================================
*/

#include "SearchDataStruct.h"
#include "SystemHelper.h"

SearchDataStruct::SearchDataStruct()
{
    AllFxDBs.clear();
    auto DBFolder = SystemHelper::Helper->systemSettingsHelper->GetAppDataBaseFolder().getChildFile("DB").findChildFiles(juce::File::findFiles, true, "*.pxml");
    auto DBID = 1;
    for (auto DB : DBFolder)
    {
        AllFxDBs.push_back(new FxDB(DB, DBID++));
    }
    AllFxs.clear();
    CurrentFxDB = nullptr;
    CurrentFx = nullptr;
    CurrentFxMetaData.clear();
}

SearchDataStruct::~SearchDataStruct()
{
}
