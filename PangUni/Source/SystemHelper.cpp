#include "SystemHelper.h"

std::unique_ptr<SystemHelper> SystemHelper::Helper = nullptr;

SystemHelper::SystemHelper()
{
    searchWindows.clear();
    databaseEditorWindows.clear();
}

void SystemHelper::InitSystemHelper()
{
    SystemHelper::Helper.reset(new SystemHelper());
}

void SystemHelper::ReleaseSystemHelper()
{
    SystemHelper::Helper = nullptr;
}

void SystemHelper::OpenMainWindow()
{
    searchWindows.push_back(std::unique_ptr<SearchWindow>(new SearchWindow("Pang Uni Search")));
}

void SystemHelper::OpenDatabaseEditorWindow()
{
    databaseEditorWindows.push_back(std::unique_ptr<DatabaseEditorWindow>(new DatabaseEditorWindow("Pang Uni Database Editor")));
}

void SystemHelper::OpenSystemSettingsWindow()
{
}

SystemHelper::~SystemHelper()
{
    for (auto itr = searchWindows.begin(); itr != searchWindows.end() ; itr++)
    {
        itr->reset(nullptr);
    }

    for (auto itr = databaseEditorWindows.begin(); itr != databaseEditorWindows.end(); itr++)
    {
        itr->reset(nullptr);
    }
}
