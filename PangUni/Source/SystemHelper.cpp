#include "SystemHelper.h"

std::unique_ptr<SystemHelper> SystemHelper::Helper = nullptr;

SystemHelper::SystemHelper()
{}

void SystemHelper::_initSystemHelper()
{
    systemSettingsHelper.reset(new SystemSettingsHelper());
    languageHelper.reset(new LanguageHelper());
    baiduAIHelper.reset(new BaiduAIHelper());

    audioDeviceManager.reset(SystemHelper::Helper->systemSettingsHelper->GetAudioDevice());

    auto currentLangS = SystemHelper::Helper->systemSettingsHelper->GetLanguage();
    auto currentAppBasePath = SystemHelper::Helper->systemSettingsHelper->GetAppDataBasePath();
    auto transFile = SystemHelper::Helper->languageHelper->GetTransFileByLanguage(currentAppBasePath, currentLangS);
    if (transFile.existsAsFile())
    {
        juce::LocalisedStrings::setCurrentMappings(new juce::LocalisedStrings(transFile, false));
    }
    juce::LookAndFeel_V4::getDefaultLookAndFeel().setDefaultSansSerifTypefaceName("YaHei");

    searchWindows.clear();
    databaseEditorWindows.clear();
}

void SystemHelper::_releaseSystemHelper()
{
    for (auto itr = searchWindows.begin(); itr != searchWindows.end(); itr++)
    {
        itr->reset(nullptr);
    }

    for (auto itr = databaseEditorWindows.begin(); itr != databaseEditorWindows.end(); itr++)
    {
        itr->reset(nullptr);
    }

    systemSettingsWindow = nullptr;

    audioDeviceManager = nullptr;

    systemSettingsHelper = nullptr;
    languageHelper = nullptr;
    baiduAIHelper = nullptr;
}

void SystemHelper::InitSystemHelper()
{
    SystemHelper::Helper.reset(new SystemHelper());
    SystemHelper::Helper->_initSystemHelper();
}

void SystemHelper::ReleaseSystemHelper()
{
    SystemHelper::Helper->_releaseSystemHelper();
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
    systemSettingsWindow.reset(new SystemSettingsWindow("Pang Uni System Settings"));
}
