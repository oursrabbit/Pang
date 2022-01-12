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
        << "    <file>" << DatabaseHelper::CurrentFx->GetAudioFile().getFullPathName() << "</file>" << std::endl  // FILE
        << "    <trackNum>" << -99 << "</trackNum>" << std::endl  // Trak
        << "    <frameFormat>" << 0 << "</frameFormat>" << std::endl  // FFrm
        << "    <trackOffset>" << 0 << "</trackOffset>" << std::endl  // TkOf
        << "    <sampleLoc>" << 0 << "</sampleLoc>" << std::endl  // SMSt
        << "    <stream>" << 1 << "</stream>" << std::endl  // Strm
        << "    <region>" << std::endl  // Rgn
        << "        <start>" << startSample << "</start>" << std::endl  // Star
        << "        <stop>" << endSample << "</stop>" << std::endl  // Stop
        << "        <name>" << DatabaseHelper::CurrentFx->GetAudioFile().getFileNameWithoutExtension() << "</name>" << std::endl  // Name
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
#include <Carbon/Carbon.h>
void RegionSpotter::Spot(juce::int64 startSample, juce::int64 endSample)
{
    // allocate and null out AEDesc's
    AEAddressDesc   		processAEAddressDesc; // Des Add
    AppleEvent              appleEventToSend,appleEventReply; // Send&Rec Event
    AERecord                regionAERecord; // Region Param
    OSErr                   osError = noErr; //
    OSType                  ProToolsSignature = 'PTul'; // Pro Tools

    // Your local variable declarations here
    processAEAddressDesc.dataHandle = nullptr;
    regionAERecord.dataHandle = nullptr;
    appleEventToSend.dataHandle = nullptr;
    appleEventReply.dataHandle = nullptr;

    // Create an address descriptor for the target process/application
    if(osError == noErr)
        osError = AECreateDesc(typeApplSignature, &ProToolsSignature, sizeof(ProToolsSignature), &processAEAddressDesc);

    // Create an apple event to send
    if(osError == noErr)
        osError = AECreateAppleEvent('Sd2a','SRgn', &processAEAddressDesc, kAutoGenerateReturnID,kAnyTransactionID, &appleEventToSend);

    AliasHandle filenameAlias;
    // Specify the audio file which contains the region data
    if(osError == noErr)
        osError = FSNewAliasFromPath(nullptr, DatabaseHelper::CurrentFx->AudioFile.getFullPathName().toRawUTF8(), 0, &filenameAlias, nullptr);

    // add an alias to the apple event
    if(osError == noErr) {
        HLock((Handle)filenameAlias);
        osError = AEPutParamPtr(&appleEventToSend, 'FILE', typeAlias, (Ptr)(*filenameAlias), GetHandleSize((Handle)(filenameAlias)));
        HUnlock((Handle)(filenameAlias));
    }

    short yourTrackNumber = -99;
    if(osError == noErr) {
        // Specify which track to spot region to
        // To spot to selection pass in value of "-99" in yourTrackNumber
        // ProTools will place the region into the first track currently selected
        osError = AEPutParamPtr(&appleEventToSend,'Trak',typeSInt16, (Ptr)&yourTrackNumber, sizeof(yourTrackNumber));
    }

    short yourFrameFormat = 0;
    if(osError == noErr) {
        // does nothing right now
        // ProTools parses this parameter, then ignores it.
        osError = AEPutParamPtr(&appleEventToSend,'FFrm',typeSInt16, (Ptr)&yourFrameFormat, sizeof(yourFrameFormat));
    }

    short yourTrackOffset = 0;

    if(osError == noErr) {
        // Specify Track Offset from selection or specified track.
        // Normally you will set this to zero, however, if you want to batch spot
        // run of regions across multiple tracks, you can send multiple Events
        // with varying track offsets.
        osError = AEPutParamPtr(&appleEventToSend,'TkOf',typeSInt16, (Ptr)&yourTrackOffset, sizeof(yourTrackOffset));
    }

    long yourSpotLocation = 0;

    if(osError == noErr) {
        // Specify sample location to spot region
        // NOTE** This is the sample location from absolute zero, not necessarily the start of your session.
        // If spot to selection (yourTrackNumber = -99), ProTools interprets "SMSt" as the sample offset
        // from the start of the current selection.  This can be used to batch spot a run of regions.
        osError = AEPutParamPtr(&appleEventToSend,'SMSt',typeSInt32, (Ptr)&yourSpotLocation, sizeof(yourSpotLocation));
    }

    short yourPlayListNumber = 1;
    if(osError == noErr) {
        // Specify which stream, playlist within a multichannel track to spot region
        // For example, in a stereo file, stream 1 is the left channel, stream 2 is the right
        osError =  AEPutParamPtr(&appleEventToSend,'Strm',typeSInt16, (Ptr) &yourPlayListNumber, sizeof(yourPlayListNumber));
    }

    // Make a region descriptor
    if(osError == noErr) {
        osError = AECreateList(nullptr, 0, true /*isRecord*/, &regionAERecord);
    }

    long yourStartSample = 0;

    if(osError == noErr) {
        // Start location of region within audio file
        osError =  AEPutKeyPtr(&regionAERecord,'Star',typeSInt32, (Ptr) &yourStartSample, sizeof(yourStartSample));
    }

    long yourStopSample = 441000;

    if(osError == noErr) {
        // End location of region within audio file
        osError =  AEPutKeyPtr(&regionAERecord,'Stop',typeSInt32, (Ptr) &yourStopSample, sizeof(yourStopSample));
    }

    Str255 yourRegionNameString;
    CFStringRef fileNameCF = CFStringCreateWithCString(kCFAllocatorDefault, DatabaseHelper::CurrentFx->AudioFile.getFileNameWithoutExtension().toRawUTF8(), kCFStringEncodingASCII);
    CFStringGetPascalString(fileNameCF, yourRegionNameString, sizeof(yourRegionNameString), kCFStringEncodingASCII);

    if(osError == noErr) {
        osError = AEPutKeyPtr(&regionAERecord,'Name',typeChar, (Ptr) &yourRegionNameString[0], sizeof(yourRegionNameString));
    }

    // Add the region descriptor to the apple event
    if(osError == noErr) {
        osError = AEPutParamDesc(&appleEventToSend,'Rgn ', &regionAERecord);
    }

    // Create a NULL reply event because we don't expect any reply
    if(osError == noErr) {
        osError = AECreateDesc(typeNull, nullptr, 0, &appleEventReply);
    }


    // Send Event
    if(osError == noErr) {
        osError = AESend(&appleEventToSend, &appleEventReply, kAEWaitReply|kAECanInteract,kAENormalPriority, kAEDefaultTimeout,nullptr, nullptr);
    }

    // Clean up
    AEDisposeDesc(&processAEAddressDesc);
    AEDisposeDesc(&appleEventToSend);
    AEDisposeDesc(&appleEventReply);
    AEDisposeDesc(&regionAERecord);
}
#endif
