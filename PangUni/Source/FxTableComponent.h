#pragma once
#include <JuceHeader.h>
#include "SearchDataStruct.h"

class FxTableListener
{
public:
    virtual void tableSelectedRowChanged() = 0;
    virtual ~FxTableListener() {}
};

class FxTable : public juce::Component, juce::TableListBoxModel
{
public:
    std::unique_ptr<juce::TableListBox> table;
    SearchDataStruct* newData;
    FxTableListener* Listener = nullptr;

    FxTable();
    FxTable(SearchDataStruct* newData);
    ~FxTable() override;

    void paint(juce::Graphics& g) override;
    void resized() override;
    bool keyPressed(const juce::KeyPress& press) override;
    void UpdateNewFx();


    virtual int getNumRows() override;
    virtual void paintRowBackground(juce::Graphics&, int rowNumber, int width, int height, bool rowIsSelected) override;
    virtual void paintCell(juce::Graphics&, int rowNumber, int columnId, int width, int height, bool rowIsSelected) override;
    virtual void selectedRowsChanged(int lastRowSelected) override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(FxTable)
};
