#pragma once
#include <JuceHeader.h>
#include "Fx.h"

class FxDB
{
public:
    // FxDB =============================================================================================

    juce::File DatabaseFile;
    std::vector<Fx* > Fxs;

    FxDB();
    // file: excel txt
    // id: combobox itemid, Start from 1, CANNOT BE 0
    FxDB(juce::File file, int id, bool none);

    // file: pxml
    // id: combobox itemid, Start from 1, CANNOT BE 0
    FxDB(juce::File file, int id);
    void Serialization(juce::File file);

    // FxDB =============================================================================================

    // Combobox =========================================================================================
    
    //Start from 1, CANNOT BE 0
    int ComboboxItemID; 

    // Combobox =========================================================================================

    // TableList ========================================================================================

    std::vector<FxInfo* > DBSchema;

    // TableList ========================================================================================

    // Searching ========================================================================================

    std::vector<Fx* > FilteredFxs;
    void ResetFilteredFxs() { FilteredFxs = Fxs; }
    void FindFxByKeywords(juce::StringArray keywords);

    // Searching ========================================================================================
};