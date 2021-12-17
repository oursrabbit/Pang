/*
 *  RegionSpotterOSX.cpp
 *  Spot a Pro Tools region from an external program
 *  Author: Bob Lee, 2/7/2005
 *
 *  Copyright (c) 2005
 *  Digidesign, A Division of Avid
 *
 */


#include <iostream>
#include "RegionSpotterOSX.h"


RegionSpotterOSX::RegionSpotterOSX(const char *fName, long rStart, long rStop) 
: yourStartSample(rStart), yourStopSample(rStop){

	Str255 fName_pascal;
	FSSpec fsSpec;
	OSErr osError = noErr;
	
	
	// Create an alias for the source file
	CopyCStringToPascal(fName, fName_pascal);
    osError = FSMakeFSSpec(0,0,(unsigned char*)fName_pascal,&fsSpec);
    if(osError != noErr)
       	std::cout << "no FSSpec was created, OSError = " << osError << ", file = " << fName << std::endl;
     
    if(osError == noErr)
       	osError = NewAlias(NULL, &fsSpec, &filenameAlias); 
    if(filenameAlias == NULL)
        std::cout << "no alias was created" << std::endl;

}




int RegionSpotterOSX::spot(	  short           yourTrackOffset,
							  long            yourSpotLocation,
							  short           yourPlayListNumber,
							  const char*     yourRegionNameString_C)
{
	// Removed from parameter list because only spot to selection is implemented
	short yourTrackNumber = -99;
	short yourFrameFormat = 0;

	// allocate and null out AEDesc's
    AEAddressDesc   		processAEAddressDesc;
   	AppleEvent              appleEventToSend,appleEventReply;
    AERecord                regionAERecord;
 	OSErr                   osError = noErr;
    OSType                  ProToolsSignature = 'PTul';

    // Your local variable declarations here        
    processAEAddressDesc.dataHandle = NULL;
 	regionAERecord.dataHandle = NULL;
    appleEventToSend.dataHandle = NULL;
    appleEventReply.dataHandle = NULL;
    
    Str255 yourRegionNameString;
	CopyCStringToPascal(yourRegionNameString_C, yourRegionNameString);


    // Create an address descriptor for the target process/application
    if(osError == noErr)
    	osError = AECreateDesc(typeApplSignature, &ProToolsSignature, sizeof(ProToolsSignature), &processAEAddressDesc);

   	// Create an apple event to send
    if(osError == noErr)
     	osError = AECreateAppleEvent('Sd2a','SRgn', &processAEAddressDesc, kAutoGenerateReturnID,kAnyTransactionID, &appleEventToSend);

 	// add an alias to the apple event
    if(osError == noErr) {
    	// Specify the audio file which contains the region data
        HLock((Handle)filenameAlias);
        osError = AEPutParamPtr(&appleEventToSend, 'FILE', typeAlias, (Ptr)(*filenameAlias), GetHandleSize((Handle)(filenameAlias)));
        HUnlock((Handle)(filenameAlias));
	}

    if(osError == noErr) {
    	// Specify which track to spot region to
        // To spot to selection pass in value of "-99" in yourTrackNumber
        // ProTools will place the region into the first track currently selected
        osError = AEPutParamPtr(&appleEventToSend,'Trak',typeShortInteger, (Ptr)&yourTrackNumber, sizeof(yourTrackNumber));
    }

	yourFrameFormat = 1;

    if(osError == noErr) {
        // does nothing right now
        // ProTools parses this parameter, then ignores it.
        osError = AEPutParamPtr(&appleEventToSend,'FFrm',typeShortInteger, (Ptr)&yourFrameFormat, sizeof(yourFrameFormat));
    }

	if(osError == noErr) {
          // Specify Track Offset from selection or specified track.
          // Normally you will set this to zero, however, if you want to batch spot
          // run of regions across multiple tracks, you can send multiple Events
          // with varying track offsets.
          osError = AEPutParamPtr(&appleEventToSend,'TkOf',typeShortInteger, (Ptr)&yourTrackOffset, sizeof(yourTrackOffset));
    }

    if(osError == noErr) {
          // Specify sample location to spot region
          // NOTE** This is the sample location from absolute zero, not necessarily the start of your session.
          // If spot to selection (yourTrackNumber = -99), ProTools interprets "SMSt" as the sample offset
          // from the start of the current selection.  This can be used to batch spot a run of regions. 
          osError = AEPutParamPtr(&appleEventToSend,'SMSt',typeLongInteger, (Ptr)&yourSpotLocation, sizeof(yourSpotLocation));
    }

    if(osError == noErr) {
          // Specify which stream, playlist within a multichannel track to spot region
          // For example, in a stereo file, stream 1 is the left channel, stream 2 is the right
          osError =  AEPutParamPtr(&appleEventToSend,'Strm',typeShortInteger, (Ptr) &yourPlayListNumber, sizeof(yourPlayListNumber));
    }

    // Make a region descriptor
    if(osError == noErr) {
          osError = AECreateList(NULL, 0, true /*isRecord*/, &regionAERecord);
    }

    if(osError == noErr) {
          // Start location of region within audio file
          osError =  AEPutKeyPtr(&regionAERecord,'Star',typeLongInteger, (Ptr) &yourStartSample, sizeof(yourStartSample));
    }

    if(osError == noErr) {
          // End location of region within audio file
          osError =  AEPutKeyPtr(&regionAERecord,'Stop',typeLongInteger, (Ptr) &yourStopSample, sizeof(yourStopSample));
	}

    if(osError == noErr) {
          // name of the region to spot
          osError = AEPutKeyPtr(&regionAERecord,'Name',typeChar, (Ptr)&yourRegionNameString[0], sizeof(yourRegionNameString));
    }

    // Add the region descriptor to the apple event
    if(osError == noErr) {
          osError = AEPutParamDesc(&appleEventToSend,'Rgn ', &regionAERecord);
    }

    // Create a NULL reply event because we don't expect any reply
    if(osError == noErr) {
          osError = AECreateDesc(typeNull, NULL, 0, &appleEventReply);
    }


    // Send Event
    if(osError == noErr) {
          osError = AESend(&appleEventToSend, &appleEventReply, kAEWaitReply|kAECanInteract,kAENormalPriority, kAEDefaultTimeout,NULL, NULL);
    }

    // Clean up
    AEDisposeDesc(&processAEAddressDesc);
    AEDisposeDesc(&appleEventToSend);
    AEDisposeDesc(&appleEventReply);
    AEDisposeDesc(&regionAERecord);

	return osError;
}


