/*
  ==============================================================================

    CustomTableCells.h
    Created: 12 Jan 2022 5:37:00pm
    Author:  YC

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

enum OwnerTypeEnum
{
    FxInfoTable, FxTable
};

class DoubleClickedEditableLabel : public juce::Label
{
public:
    OwnerTypeEnum OwnerType;
    int RowNumber;
    int ColumnID;
    std::function<void(int,int)> OnClicked;

    void mouseDown(const juce::MouseEvent& event) override
    {
        getParentComponent()->mouseDown(event);
        OnClicked(RowNumber, ColumnID);
        Label::mouseDown(event);
    }

    DoubleClickedEditableLabel();
    DoubleClickedEditableLabel(bool editable, int rowNumber, int columnID, OwnerTypeEnum ownerType, std::function<void(int, int)> onClicked);
    ~DoubleClickedEditableLabel();
};