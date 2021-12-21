#include "DatabaseHelper.h"
#include "SystemSettingsHelper.h"

std::vector <FxDB> DatabaseHelper::DatabaseFiles = std::vector <FxDB>();
FxDB* DatabaseHelper::CurrentFxDB = nullptr;
Fx* DatabaseHelper::CurrentFx = nullptr;

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
    juce::AlertWindow waitWindow(TRANS("Loading..."), 
        TRANS("Loading Database.") + "\n\n" + 
        TRANS("Please DO NOT close window.") + "\n\n" + 
        TRANS("This window will be hold for a while,") + "\n" + 
        TRANS("if audio files are not at local disk."), juce::MessageBoxIconType::WarningIcon);
    waitWindow.enterModalState();
    DatabaseHelper::CurrentFxDB = nullptr;
    auto fxdb = std::find_if(std::begin(DatabaseHelper::DatabaseFiles), std::end(DatabaseHelper::DatabaseFiles), [id](FxDB t) { return t.ComboboxItemID == id; });
    if (fxdb != std::end(DatabaseHelper::DatabaseFiles))
    {
        fxdb->LoadDB();
        DatabaseHelper::CurrentFxDB = fxdb._Ptr;
    }
    waitWindow.exitModalState(0);
}

// Table RowNumber Start From 1st.
// Table SelectedRow Start From Row Index 0
// par index is the fxs array index Start From 0
void DatabaseHelper::LoadFxFile(int index)
{
    DatabaseHelper::CurrentFx = nullptr;
    if (DatabaseHelper::CurrentFxDB != nullptr && index >= 0)
    {
        DatabaseHelper::CurrentFx = &DatabaseHelper::CurrentFxDB->Fxs[index];
    }
}