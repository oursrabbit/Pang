#include "DatabaseHelper.h"

std::vector <FxDB*> DatabaseHelper::DatabaseFiles = std::vector <FxDB* >();
FxDB* DatabaseHelper::CurrentFxDB = nullptr;
Fx* DatabaseHelper::CurrentFx = nullptr;

void DatabaseHelper::LoadAllFxDatabase(juce::File appDataPath)
{
    // Load DatabaseList
    juce::File databasePath = appDataPath.getChildFile("DB");
    auto dbF = databasePath.findChildFiles(juce::File::findFiles, false, "*.pxml");
    DatabaseHelper::DatabaseFiles.clear();
    for (int i = 0; i < dbF.size(); ++i)
    {
        DatabaseHelper::DatabaseFiles.push_back(new FxDB(dbF[i], i + 1));
    }
}

// Combobox Item ID
// ID start from 1
void DatabaseHelper::LoadFxDatabase(int id)
{
    DatabaseHelper::CurrentFxDB = nullptr;
    if (DatabaseHelper::DatabaseFiles.size() >= id && id >= 1)
    {
        DatabaseHelper::CurrentFxDB = DatabaseHelper::DatabaseFiles[id - 1];
    }
}

// Table RowNumber Start From 1st.
// Table SelectedRow Start From Row Index 0
// par index is the fxs array index Start From 0
void DatabaseHelper::LoadFxFile(int index)
{
    DatabaseHelper::CurrentFx = nullptr;
    if (DatabaseHelper::CurrentFxDB != nullptr && index >= 0)
    {
        DatabaseHelper::CurrentFx = DatabaseHelper::CurrentFxDB->Fxs[(unsigned long)index];
    }
}
