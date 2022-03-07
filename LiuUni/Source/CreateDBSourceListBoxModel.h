/*
  ==============================================================================

    CreateDBSourceListBoxModel.h
    Created: 6 Mar 2022 8:13:34pm
    Author:  YC

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class CreateDBSourceListBoxModel: public juce::Component, juce::ListBoxModel
{
public:
    juce::StringArray SourcePaths;
    juce::ListBox listbox;

    // Í¨¹ý ListBoxModel ¼Ì³Ð
    virtual int getNumRows() override;
    virtual void paintListBoxItem(int rowNumber, juce::Graphics& g, int width, int height, bool rowIsSelected) override;

    CreateDBSourceListBoxModel();
    ~CreateDBSourceListBoxModel() override;

    void updateList(juce::String fullPath, bool isAdd = true);

    void paint(juce::Graphics& g) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CreateDBSourceListBoxModel)

};