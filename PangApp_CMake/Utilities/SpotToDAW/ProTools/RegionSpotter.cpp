#include "RegionSpotter.h"
#include "../../DatabaseHelper.h"
#include <strstream>
#include <string.h>

#ifdef WIN32
    #include <windows.h>
/*! \brief Spots audio in a RegionSpotter object to a Pro Tools region
 *
 *  \par NOTE:
 *  \li Currently only spots to one playlist at a time.  You must call spot() twice to spot a stereo
 *      piece of audio.
 *
 *  \par Undefined when:
 *  \li region name is larger than Pro Tools allows
 *  \li track number does not exist
 *  \li playlist does not exist (e.g. playlist 2 in a mono track)
 *
 *  \param trackOffset This is the track offset from the current selection.
 *  \param spotLocationSample This is the sample offset from the start of the
 *         current selection.
 *  \param playlistNumber Playlist to spot region in a multichannel track.  Left = 1, Right = 2, etc.
 *  \param regionNameString Name of the region to spot.  Should be a null-terminated char array.
 *  \retval int On OS X, Return OSErr value.  On Windows, return 0 if successful, -1 if Pro Tools
 *          window was not available, -2 if Pro Tools window was available but message was not
 *          received.  (Could be an old version of PT)
 */
void RegionSpotter::Spot(juce::int64 startSample, juce::int64 endSample
    /* short trackOffset,
    long spotLocationSample,
    short playlistNumber,
    const char* regionNameString */)
{
    std::ostrstream os;
    // Equivalent AppleEvent keywords
    os << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>" << std::endl
        << "<request>" << std::endl
        << "    <action>spotRegion</action>" << std::endl
        << "    <file>" << DatabaseHelper::CurrentFx->AudioFile.getFullPathName() << "</file>" << std::endl  // FILE
        << "    <trackNum>" << -99 << "</trackNum>" << std::endl  // Trak
        << "    <frameFormat>" << 0 << "</frameFormat>" << std::endl  // FFrm
        << "    <trackOffset>" << 0 << "</trackOffset>" << std::endl  // TkOf
        << "    <sampleLoc>" << 0 << "</sampleLoc>" << std::endl  // SMSt
        << "    <stream>" << 1 << "</stream>" << std::endl  // Strm
        << "    <region>" << std::endl  // Rgn
        << "        <start>" << startSample << "</start>" << std::endl  // Star
        << "        <stop>" << endSample << "</stop>" << std::endl  // Stop
        << "        <name>" << DatabaseHelper::CurrentFx->AudioFile.getFileNameWithoutExtension() << "</name>" << std::endl  // Name
        << "    </region>" << std::endl
        << "</request>" << std::endl
        << std::ends;

    std::string request = std::string(os.str());

    HWND hwnd = ::FindWindow("ptOpenWindowClass", "ptOpenWindow");
    if (hwnd)
    {
        COPYDATASTRUCT cds;
        cds.dwData = 'XMLR';
        cds.lpData = (void*)request.c_str();
        cds.cbData = (DWORD)request.size() + 1;

        ::SendMessage(hwnd, WM_COPYDATA, NULL, (LPARAM)&cds);
    }
}
#else //MAC_OS
void RegionSpotter::Spot(juce::int64 startSample, juce::int64 endSample
    /* short trackOffset,
    long spotLocationSample,
    short playlistNumber,
    const char* regionNameString */)
{

}
#endif
