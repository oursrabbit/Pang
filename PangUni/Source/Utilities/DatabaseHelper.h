#pragma once
#include <JuceHeader.h>
#include <atomic>
#include "../Module/FxDB.h"

class DatabaseHelper
{
public:
    static std::vector<FxDB> DatabaseFiles;
    static FxDB* CurrentFxDB;
    // Used by FxTable, AudioSearch: meta data, AudioExport: play and thumb
    static Fx* CurrentFx;

    static void LoadAllFxDatabase();
    static void LoadFxDatabase(int id);
    static void LoadFxFile(int index);
};