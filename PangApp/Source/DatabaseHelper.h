#pragma once
#include <JuceHeader.h>
#include "FxDB.h"

class DatabaseHelper
{
public:
    static std::vector<FxDB> DatabaseFiles;
    static FxDB* CurrentFxDB;
    static Fx* CurrentFx;
    static juce::AudioFormatReader* CurrentFxFileReader;

    static void LoadAllFxDatabase();
    static void LoadFxDatabase(int id);
    static void LoadFxFile(int index);
};