/*
  ==============================================================================

    CustomTableCells.cpp
    Created: 12 Jan 2022 5:37:00pm
    Author:  YC

  ==============================================================================
*/

#include "CustomTableCells.h"

DoubleClickedEditableLabel::DoubleClickedEditableLabel()
{
    setEditable(false, true, true);
}

DoubleClickedEditableLabel::DoubleClickedEditableLabel(int rowNumber, int columnID)
{
    RowNumber = rowNumber;
    ColumnID = columnID;
    setEditable(false, true, true);
}

DoubleClickedEditableLabel::~DoubleClickedEditableLabel()
{
}
