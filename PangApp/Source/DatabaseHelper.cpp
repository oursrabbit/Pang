#include "DatabaseHelper.h"
#include "SystemSettingsHelper.h"

std::vector <FxDB> DatabaseHelper::DatabaseFiles = std::vector <FxDB>();
FxDB* DatabaseHelper::CurrentFxDB = nullptr;
Fx* DatabaseHelper::CurrentFx = nullptr;
// must DELETE every time, or use std::unique_ptr and RESET every time
juce::AudioFormatReader* DatabaseHelper::CurrentFxFileReader = nullptr;

void DatabaseHelper::LoadAllFxDatabase()
{
    // Load DatabaseList
    juce::File databasePath = juce::File(SystemSettingsHelper::GetAppDataBasePath() + FXDBPATH);
    auto dbF = databasePath.findChildFiles(juce::File::findFiles, false, "*.pxml");
    DatabaseHelper::DatabaseFiles.clear();
    for (int i = 0; i < dbF.size(); ++i)
    {
        DatabaseHelper::DatabaseFiles.push_back(FxDB(dbF[i], i + 1));
    }
}

// Combobox Item ID
void DatabaseHelper::LoadFxDatabase(int id)
{
    DatabaseHelper::CurrentFxDB = nullptr;
    auto fxdb = std::find_if(std::begin(DatabaseHelper::DatabaseFiles), std::end(DatabaseHelper::DatabaseFiles), [id](FxDB t) { return t.ComboboxItemID == id; });
    if (fxdb != std::end(DatabaseHelper::DatabaseFiles))
    {
        fxdb->LoadDB();
        DatabaseHelper::CurrentFxDB = fxdb._Ptr;
    }
}

// Table RowIndex
void DatabaseHelper::LoadFxFile(int index)
{
    DatabaseHelper::CurrentFx = nullptr;
    if (DatabaseHelper::CurrentFxDB != nullptr)
    {
        DatabaseHelper::CurrentFx = &DatabaseHelper::CurrentFxDB->Fxs[index];
        delete DatabaseHelper::CurrentFxFileReader;
        DatabaseHelper::CurrentFxFileReader = nullptr;
        if (DatabaseHelper::CurrentFx->AudioFile.existsAsFile())
        {
            juce::AudioFormatManager manager;
            manager.registerBasicFormats();
            DatabaseHelper::CurrentFxFileReader = manager.createReaderFor(DatabaseHelper::CurrentFx->AudioFile);
        }
    }
}