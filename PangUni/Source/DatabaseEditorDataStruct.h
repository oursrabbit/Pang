/*
  ==============================================================================

    DatabaseEditorDataStruct.h
    Created: 15 Jan 2022 3:55:43pm
    Author:  YC

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "FxDB.h"

class DatabaseEditorDataStruct
{
public:
    FxDB* newFxDB;

    DatabaseEditorDataStruct();
    ~DatabaseEditorDataStruct();
};