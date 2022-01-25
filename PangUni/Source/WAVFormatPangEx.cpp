/*
  ==============================================================================

    WAVFormatPangEx.cpp
    Created: 21 Jan 2022 12:49:18pm
    Author:  YC

  ==============================================================================
*/

#include "WAVFormatPangEx.h"
#include "HexConvertor.h"

WavAudioFormatPangEx::WavAudioFormatPangEx(juce::FileInputStream* auidoInputStream)
{
    this->auidoInputStream = auidoInputStream;
    this->restChunks.clear();
    this->Feed();
}

WavAudioFormatPangEx::~WavAudioFormatPangEx()
{
    for (auto itr = this->restChunks.begin(); itr != this->restChunks.end(); itr++)
        delete *itr;
}

void WavAudioFormatPangEx::Feed()
{
    auidoInputStream->skipNextBytes(12); // RIFF SIZE WAVE = 12 Bytes
    auto restSize = auidoInputStream->getNumBytesRemaining();

    while (restSize >= 4)
    {
        restChunks.push_back(new WavChunk());
        auto chunk = *(restChunks.end() - 1);

        char chunkbuffer[4]{ 0 };
        auidoInputStream->read(&chunkbuffer[0], 4);
        if (IsAlphabetCharacter(&chunkbuffer[0], 4))
        {
            chunk->Name = juce::String(&chunkbuffer[0], 4);
        }
        else
        {
            chunk->Name = "Pang";
            auidoInputStream->setPosition(auidoInputStream->getPosition() - 3);
            restSize = auidoInputStream->getNumBytesRemaining();
            continue;
        }

        char chunklengthbuffer[4]{ 0 };
        auidoInputStream->read(&chunklengthbuffer[0], 4);
        chunk->Size = ConvertToInt(chunklengthbuffer);

        chunk->Data = (char*)malloc(chunk->Size * sizeof(char));
        auidoInputStream->read(chunk->Data, chunk->Size);

        restSize = auidoInputStream->getNumBytesRemaining();
    }
}