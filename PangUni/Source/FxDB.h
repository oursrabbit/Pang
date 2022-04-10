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
    FxDB(juce::File excelFile);

    // file: pxml
    // id: combobox itemid, Start from 1, CANNOT BE 0
    FxDB(juce::File pxmlFile, int id);
    void LoadFxDBFromExcel(juce::File excelFile);
    void LoadFxDBFromPXML(juce::File pxmlFile, int id);
    void SerializationToPXML(juce::File pxmlFile);
    void SerializationToExcel(juce::File excelFile);

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