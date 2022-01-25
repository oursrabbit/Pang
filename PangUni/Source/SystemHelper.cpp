#include "SystemHelper.h"

std::unique_ptr<SystemHelper> SystemHelper::Helper = nullptr;

SystemHelper::SystemHelper()
{}

void SystemHelper::_initSystemHelper()
{
    userPerposeSpotDAW = "";
    systemSettingsHelper.reset(new SystemSettingsHelper());
    languageHelper.reset(new LanguageHelper());
    baiduAIHelper.reset(new BaiduAIHelper());
    spotHelper.reset(new SpotHelper());

    audioDeviceManager.reset(new juce::AudioDeviceManager());
    SystemHelper::Helper->systemSettingsHelper->GetAudioDevice(audioDeviceManager.get());

    auto currentLangS = SystemHelper::Helper->systemSettingsHelper->GetLanguage();
    auto currentAppBasePath = SystemHelper::Helper->systemSettingsHelper->GetAppDataBasePath();
    auto transFile = SystemHelper::Helper->languageHelper->GetTransFileByLanguage(currentAppBasePath, currentLangS);
    if (transFile.existsAsFile())
    {
        juce::LocalisedStrings::setCurrentMappings(new juce::LocalisedStrings(transFile, false));
    }
    
    // Only For Chinese
    if(currentLangS == "Chinese")
    {
#ifdef WIN32
        juce::LookAndFeel_V4::getDefaultLookAndFeel().setDefaultSansSerifTypefaceName("YaHei");
#else
        juce::LookAndFeel_V4::getDefaultLookAndFeel().setDefaultSansSerifTypefaceName("STHeiti");
#endif //WIN32
    }

    searchWindows.clear();
    databaseEditorWindows.clear();
    audioConvertorWindows.clear();
    riffEditorWindows.clear();
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

    for (auto itr = audioConvertorWindows.begin(); itr != audioConvertorWindows.end(); itr++)
    {
        itr->reset(nullptr);
    }

    for (auto itr = riffEditorWindows.begin(); itr != riffEditorWindows.end(); itr++)
    {
        itr->reset(nullptr);
    }

    systemSettingsWindow = nullptr;

    audioDeviceManager = nullptr;

    systemSettingsHelper = nullptr;
    languageHelper = nullptr;
    baiduAIHelper = nullptr;
    spotHelper = nullptr;
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

void SystemHelper::OpenAudioConvertorWindow()
{
    audioConvertorWindows.push_back(std::unique_ptr<AudioConvertorWindow>(new AudioConvertorWindow("Pang Uni Audio Convertor")));
}

void SystemHelper::OpenRIFFEditorWindow()
{
    riffEditorWindows.push_back(std::unique_ptr<RIFFEditorWindow>(new RIFFEditorWindow("Pang Uni RIFF Editor")));
}

void SystemHelper::OpenHandBookFile()
{
    auto handbookFile = SystemHelper::Helper->systemSettingsHelper->GetAppDataBaseFolder().getChildFile("Handbook.pdf");
    if(handbookFile.existsAsFile())
    {
#ifdef WIN32
#else
        auto command = "open " + handbookFile.getFullPathName();
        system(command.getCharPointer());
#endif //WIN32
    }
}
