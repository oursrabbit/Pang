/*
  ==============================================================================

    WAVFormatPangEx.h
    Created: 21 Jan 2022 12:49:18pm
    Author:  YC

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class WavChunk
{
public:
    juce::String Name;
    int Size;
    char* Data;

    WavChunk() {
        Name = "";
        Size = 0;
        Data = nullptr;
    };

    ~WavChunk()
    {
        if (Size != 0)
            delete Data;
    };
};

class WavAudioFormatPangEx :public juce::WavAudioFormat
{
public:
    std::vector<WavChunk*> restChunks;
    juce::FileInputStream* auidoInputStream;

    WavAudioFormatPangEx(juce::FileInputStream* auidoInputStream);
    ~WavAudioFormatPangEx();
    void Feed();
};