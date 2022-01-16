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
#include "SystemSettingsWindow.h"
#include "SystemSettingsHelper.h"
#include "LanguageHelper.h"
#include "BaiduAIHelper.h"

class SystemHelper
{
public:
    static void InitSystemHelper();
    static void ReleaseSystemHelper();
    static std::unique_ptr<SystemHelper> Helper;

    std::unique_ptr<SystemSettingsHelper> systemSettingsHelper;
    std::unique_ptr<LanguageHelper> languageHelper;
    std::unique_ptr<BaiduAIHelper> baiduAIHelper;

    void OpenMainWindow();
    void OpenDatabaseEditorWindow();
    void OpenSystemSettingsWindow();

private:
    std::unique_ptr<SystemSettingsWindow> systemSettingsWindow;
    std::vector<std::unique_ptr<SearchWindow>> searchWindows;
    std::vector<std::unique_ptr<DatabaseEditorWindow>> databaseEditorWindows;

    SystemHelper();
    void _initSystemHelper();
    void _releaseSystemHelper();
};