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

DoubleClickedEditableLabel::DoubleClickedEditableLabel(bool editable, int rowNumber, int columnID, OwnerTypeEnum ownerType, std::function<void(int)> onClicked)
{
    OwnerType = ownerType;
    RowNumber = rowNumber;
    ColumnID = columnID;
    OnClicked = onClicked;
    setEditable(false, editable, true);
}

DoubleClickedEditableLabel::~DoubleClickedEditableLabel()
{
}
