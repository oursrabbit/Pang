/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 6.1.2

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library.
  Copyright (c) 2020 - Raw Material Software Limited.

  ==============================================================================
*/

#pragma once

//[Headers]     -- You can add your own extra header files here --
#include <JuceHeader.h>
#include "DatabaseHelper.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/

class WaveMetadataTableListBoxModelListener
{
public:
    virtual void tableSelectedRowChanged(int) {};
};

class WaveMetadataTableListBoxModel : public juce::Component, juce::TableListBoxModel
{
public:
    juce::TableListBox table;

    //==============================================================================
    WaveMetadataTableListBoxModel();
    ~WaveMetadataTableListBoxModel() override;

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    //[/UserMethods]

    void paint(juce::Graphics& g) override;
    void resized() override;

    void Update();
    WaveMetadataTableListBoxModelListener* Listener = nullptr;

    juce::String getText(const int columnNumber, const int rowNumber) const
    {
        FxInfoElement* fx = DatabaseHelper::CurrentFxDB->FilteredFxs[rowNumber].FindInfoByColumnID(columnNumber);
        return fx == nullptr ? "" : fx->Value;
    }

    void setText(const int columnNumber, const int rowNumber, const juce::String& newText)
    {
        auto fx = DatabaseHelper::CurrentFxDB->FilteredFxs[rowNumber];
        fx.SetValueByColumnID(columnNumber, newText);
    }
private:
    //[UserVariables]   -- You can add your own custom variables in this section.

    virtual int getNumRows() override;
    virtual void paintRowBackground(juce::Graphics&, int rowNumber, int width, int height, bool rowIsSelected) override;
    virtual void paintCell(juce::Graphics&, int rowNumber, int columnId, int width, int height, bool rowIsSelected) override;
    virtual void selectedRowsChanged(int lastRowSelected) override;
    virtual juce::Component* WaveMetadataTableListBoxModel::refreshComponentForCell(int rowNumber, int columnId, bool /*isRowSelected*/, juce::Component* existingComponentToUpdate) override;
    //[/UserVariables]

    //==============================================================================

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(WaveMetadataTableListBoxModel)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

class EditableTextCustomComponent : public juce::Label
{
public:
    EditableTextCustomComponent(WaveMetadataTableListBoxModel& td)
        : owner(td)
    {
        setEditable(false, true, false);
    }

    void mouseDown(const juce::MouseEvent& event) override
    {
        owner.table.selectRowsBasedOnModifierKeys(row, event.mods, false);

        Label::mouseDown(event);
    }

    void textWasEdited() override
    {
        owner.setText(columnId, row, getText());
    }

    void setRowAndColumn(const int newRow, const int newColumn)
    {
        row = newRow;
        columnId = newColumn;
        setText(owner.getText(columnId, row), juce::dontSendNotification);
    }

private:
    WaveMetadataTableListBoxModel& owner;
    int row, columnId;
    juce::Colour textColour;
};