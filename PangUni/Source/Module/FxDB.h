#pragma once
#include <JuceHeader.h>
#include "Fx.h"

#define XML_FXROOT_NODENAME "SoundEffect"
#define XML_FXAUDIOBASEPATH_NODENAME "BasePath"
#define XML_FXINFO_NODENAME "SoundEffectInfos"
#define XML_FILENAME_NODENAME "Filename"

class FxDB
{
public:

    // Start from 1, CANNOT BE 0
    int ComboboxItemID;
    juce::File DatabaseFile;
    std::vector<FxInfo> DBSchema;

    // For Searching
    std::vector<Fx> Fxs;
    std::vector<Fx> FilteredFxs;

    // id for combobox itemif, Start from 1, CANNOT BE 0
    FxDB(juce::File file, int id);

    void LoadDB();
    void ResetFilter();
    void SetFilter(juce::StringArray keywords);
};