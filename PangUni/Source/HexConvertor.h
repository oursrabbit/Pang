/*
  ==============================================================================

    HexConcertor.h
    Created: 21 Jan 2022 1:17:45pm
    Author:  YC

  ==============================================================================
*/

#pragma once

int ConvertToInt(char* buffer)
{
    return (int)((int)(buffer[0] << 0) & 0x000000FF)
        + (int)((int)(buffer[1] << 8) & 0x0000FF00)
        + (int)((int)(buffer[2] << 16) & 0x00FF0000)
        + (int)((int)(buffer[3] << 24) & 0xFF000000);
}

bool IsAlphabetCharacter(char* buff, int maxBytesToRead)
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