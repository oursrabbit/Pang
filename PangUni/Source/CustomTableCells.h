/*
  ==============================================================================

    CustomTableCells.h
    Created: 12 Jan 2022 5:37:00pm
    Author:  YC

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class DoubleClickedEditableLabel : public juce::Label
{
public:
    int RowNumber;
    int ColumnID;
    DoubleClickedEditableLabel();
    DoubleClickedEditableLabel(int rowNumber, int columnID);
    ~DoubleClickedEditableLabel();
};