/*
  ==============================================================================

    DatabaseHelper.cpp
    Created: 3 Dec 2021 3:47:32pm
    Author:  庞兴庆

  ==============================================================================
*/

#include "DatabaseHelper.h"

std::unique_ptr<juce::ApplicationProperties> SystemSettingsHelper::AppProperties = nullptr;


juce::String DatabaseHelper::fileBasePath = "";
std::map<int, juce::File> DatabaseHelper::databaseFiles = std::map<int, juce::File>();
std::map<int, juce::String> DatabaseHelper::databaseHeaderIndexSchema = std::map<int, juce::String>();
std::vector<std::map<int, juce::String>> DatabaseHelper::FXInfos = std::vector<std::map<int, juce::String>>();
std::vector<std::map<int, juce::String>> DatabaseHelper::FilteredFxInfos = std::vector<std::map<int, juce::String>>();
