/*
 *  RegionSpotterWin32.cpp
 *  Spot a Pro Tools region from an external program
 *  Author: Bob Lee, 2/7/2005
 *
 *  Copyright (c) 2005
 *  Digidesign, A Division of Avid
 *
 */

#include <windows.h>
#include <strstream> 
#include <string.h>
#include "RegionSpotterWin32.h"


RegionSpotterWin32::RegionSpotterWin32(const char* fName, long rStart, long rStop)
    : filename_p(fName), regionStart_p(rStart), regionStop_p(rStop) {}


int RegionSpotterWin32::spot(short           trackOffset,
    long            sampleLoc,
    short           stream,
    const char* regionName)
{
    // Removed from parameter list because only spotting to a selection is allowed
    short trackNum = -99;
    short frameFormat = 0;


    std::ostrstream os;
    int result = 0;
    // Equivalent AppleEvent keywords
    os << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>" << std::endl
        << "<request>" << std::endl
        << "    <action>spotRegion</action>" << std::endl
        << "    <file>" << filename_p << "</file>" << std::endl  // FILE
        << "    <trackNum>" << trackNum << "</trackNum>" << std::endl  // Trak
        << "    <frameFormat>" << frameFormat << "</frameFormat>" << std::endl  // FFrm
        << "    <trackOffset>" << trackOffset << "</trackOffset>" << std::endl  // TkOf
        << "    <sampleLoc>" << sampleLoc << "</sampleLoc>" << std::endl  // SMSt
        << "    <stream>" << stream << "</stream>" << std::endl  // Strm
        << "    <region>" << std::endl  // Rgn
        << "        <start>" << regionStart_p << "</start>" << std::endl  // Star
        << "        <stop>" << regionStop_p << "</stop>" << std::endl  // Stop
        << "        <name>" << regionName << "</name>" << std::endl  // Name
        << "    </region>" << std::endl
        << "</request>" << std::endl
        << std::ends;

    std::string request = std::string(os.str());

    HWND hwnd = ::FindWindow(L"ptOpenWindowClass", L"ptOpenWindow");
    if (hwnd)
    {
        COPYDATASTRUCT cds;
        cds.dwData = 'XMLR';
        cds.lpData = (void*)request.c_str();
        cds.cbData = (DWORD)request.size() + 1;

        if (!(::SendMessage(hwnd, WM_COPYDATA, NULL, (LPARAM)&cds)))
            result = -2;
    }
    else result = -1;

    return result;
}
