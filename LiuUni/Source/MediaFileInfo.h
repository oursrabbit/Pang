/*
  ==============================================================================

    MediaFileInfo.h
    Created: 6 Mar 2022 7:44:03pm
    Author:  YC

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class MediaFileInfo
{
public:
    MediaFileInfo();
    ~MediaFileInfo();

    juce::String FileName;
    juce::String FileFullPath;

    int TotalSeconds;

    juce::StringArray FileKeyWords;
};
