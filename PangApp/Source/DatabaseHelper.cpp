/*
  ==============================================================================

    DatabaseHelper.cpp
    Created: 3 Dec 2021 3:47:32pm
    Author:  庞兴庆

  ==============================================================================
*/

#include "DatabaseHelper.h"

std::unique_ptr<juce::ApplicationProperties> SystemSettingsHelper::AppProperties = nullptr;

juce::String FxDB::SchemaPath = "\\Pang\\DB\\Template\\PXMLSchema.pxml";
juce::String FxDB::DBPath = "\\Pang\\DB";
std::vector<FxInfoHeader> FxDB::DBSchema = std::vector<FxInfoHeader>();

std::vector <FxDB> DatabaseHelper::DatabaseFiles = std::vector <FxDB>();
FxDB* DatabaseHelper::CurrentFxDB = nullptr;
