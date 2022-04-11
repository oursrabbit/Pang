#pragma once
#include <JuceHeader.h>

class RIFFTableComponent : public juce::Component, juce::TableListBoxModel
{
public:
    std::unique_ptr<juce::TableListBox> table;

    RIFFTableComponent();
    ~RIFFTableComponent() override;

    void paint(juce::Graphics& g) override;
    void resized() override;
    bool keyPressed(const juce::KeyPress& press) override;
    void UpdateNewFx();


    virtual int getNumRows() override;
    virtual void paintRowBackground(juce::Graphics&, int rowNumber, int width, int height, bool rowIsSelected) override;
    virtual void paintCell(juce::Graphics&, int rowNumber, int columnId, int width, int height, bool rowIsSelected) override;
    virtual void selectedRowsChanged(int lastRowSelected) override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(RIFFTableComponent)
};
