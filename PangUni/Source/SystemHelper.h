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
#include "AudioConvertorWindow.h"
#include "RIFFEditorWindow.h"

#include "SystemSettingsHelper.h"
#include "LanguageHelper.h"
#include "BaiduAIHelper.h"
#include "SpotHelper.h"

class SystemHelper
{
public:
    static void InitSystemHelper();
    static void ReleaseSystemHelper();
    static std::unique_ptr<SystemHelper> Helper;

    std::unique_ptr<SystemSettingsHelper> systemSettingsHelper;
    std::unique_ptr<LanguageHelper> languageHelper;
    std::unique_ptr<BaiduAIHelper> baiduAIHelper;
    std::unique_ptr<SpotHelper> spotHelper;

    std::unique_ptr<juce::AudioDeviceManager> audioDeviceManager;
    juce::String userPurposeSpotDAW;

    std::unique_ptr<juce::FileChooser> chooser;

    void OpenMainWindow();
    void OpenSystemSettingsWindow();
    void OpenAudioConvertorWindow();
    void OpenRIFFEditorWindow();

    void ExportDBTPFile();
    void ConvertExcelToPXML();
    void ConvertPXMLToExcel();
    void ImportDB();
    void OpenHandBookFile();

private:
    std::unique_ptr<SystemSettingsWindow> systemSettingsWindow;
    std::vector<std::unique_ptr<SearchWindow>> searchWindows;
    std::vector<std::unique_ptr<DatabaseEditorWindow>> databaseEditorWindows;
    std::vector<std::unique_ptr<AudioConvertorWindow>> audioConvertorWindows;
    std::vector<std::unique_ptr<RIFFEditorWindow>> riffEditorWindows;

    SystemHelper();
    void _initSystemHelper();
    void _releaseSystemHelper();
};
