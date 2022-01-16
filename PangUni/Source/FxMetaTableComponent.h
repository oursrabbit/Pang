#pragma once
#include <JuceHeader.h>
#include "SearchDataStruct.h"

class FxMetaTableListener
{
public:
    virtual void fxMetaTableSelectedRowChanged() = 0;
    virtual ~FxMetaTableListener() {}
};

class FxMetaTableComponent : public juce::Component, juce::TableListBoxModel
{
public:
    std::unique_ptr<juce::TableListBox> table;
    SearchDataStruct* newData;
    FxMetaTableListener* Listener = nullptr;

    FxMetaTableComponent();
    FxMetaTableComponent(SearchDataStruct* newData);
    ~FxMetaTableComponent() override;

    void paint(juce::Graphics& g) override;
    void resized() override;
    bool keyPressed(const juce::KeyPress& press) override;
    void UpdateNewFx();


    virtual int getNumRows() override;
    virtual void paintRowBackground(juce::Graphics&, int rowNumber, int width, int height, bool rowIsSelected) override;
    virtual void paintCell(juce::Graphics&, int rowNumber, int columnId, int width, int height, bool rowIsSelected) override;
    virtual void selectedRowsChanged(int lastRowSelected) override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(FxMetaTableComponent)
};
