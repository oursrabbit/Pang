/*
  ==============================================================================

    SystemHelper.h
    Created: 11 Jan 2022 6:26:49pm
    Author:  YC

  ==============================================================================
*/

#pragma once
#include "DatabaseEditorWindow.h"
#include "SearchWindow.h"

class SystemHelper
{
public:
    static void InitSystemHelper();
    static void ReleaseSystemHelper();
    static std::unique_ptr<SystemHelper> Helper;

    void OpenMainWindow();
    void OpenDatabaseEditorWindow();
    void OpenSystemSettingsWindow();

    ~SystemHelper();
private:
   

    std::vector<std::unique_ptr<SearchWindow>> searchWindows;
    std::vector<std::unique_ptr<DatabaseEditorWindow>> databaseEditorWindows;

    SystemHelper();
};