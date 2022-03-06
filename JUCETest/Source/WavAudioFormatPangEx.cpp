
#include "WavAudioFormatPangEx.h"

int ConvertToIntYYY(char* buffer)
{
    return (int)((int)(buffer[0] << 0) & 0x000000FF)
        + (int)((int)(buffer[1] << 8) & 0x0000FF00)
        + (int)((int)(buffer[2] << 16) & 0x00FF0000)
        + (int)((int)(buffer[3] << 24) & 0xFF000000);
}

bool IsAlphabetCharacterYYY(char* buff, int maxBytesToRead)
{
    for (int i = 0; i < maxBytesToRead; i++)
    {
        int bi = (buff[i] & 0x000000FF);
        if ((bi >= 0x00000041 && bi <= 0x0000005A) // A - Z
            || (bi >= 0x00000061 && bi <= 0x0000007A) // a - z
            || (bi >= 0x30 && bi <= 0x39) // 0 - 9
            || (bi == 0x20)) // space
        {
        }
        else
            return false;
    }
    return true;
}

WavAudioFormatPangEx::WavAudioFormatPangEx(juce::FileInputStream* auidoInputStream)
{
    this->auidoInputStream = auidoInputStream;
    this->restChunks.clear();
    this->Feed();
}

WavAudioFormatPangEx::~WavAudioFormatPangEx()
{
    for (auto itr = this->restChunks.begin(); itr != this->restChunks.end(); itr++)
        delete* itr;
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
        if (IsAlphabetCharacterYYY(&chunkbuffer[0], 4))
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
        chunk->Size = ConvertToIntYYY(chunklengthbuffer);

        chunk->Data = (char*)malloc(chunk->Size * sizeof(char));
        auidoInputStream->read(chunk->Data, chunk->Size);

        if (chunk->Name == "id3 ")
        {
            ReadID3Tag();
        }

        restSize = auidoInputStream->getNumBytesRemaining();
    }
}

void WavAudioFormatPangEx::ReadID3Tag()
{
    // 'id3 ' Chunk
    auto chunk = *(restChunks.end() - 1);
    if (chunk->Name == "id3 ")
    {
        // ID3v2 header
        // 
    }
}
