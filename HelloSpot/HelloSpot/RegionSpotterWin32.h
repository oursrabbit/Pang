/*
 *  RegionSpotterWin32.h
 *  Spot a Pro Tools region from an external Windows program
 *  Author: Bob Lee, 2/7/2005
 *
 *  Copyright (c) 2005
 *  Digidesign, A Division of Avid
 *
 */

#ifndef REGIONSPOTTERWIN32_H
#define REGIONSPOTTERWIN32_H

#include "RegionSpotter.h"

class RegionSpotterWin32 : public RegionSpotter {

public:
	// See parameter descriptions in RegionSpotter.h
	RegionSpotterWin32(const char* filenameString,
		long regionStartSample,
		long regionStopSample);

	// Builds an XML request string from the passed in parameters and sends it in a 
	//   WM_COPYDATA message to ProTools.
	// author: Graham Lyus
	int spot(short trackOffset,
		long spotLocationSample,
		short playlistNumber,
		const char* regionNameString);


private:
	const char* filename_p;
	int					regionStart_p;
	int					regionStop_p;
};


#endif  //    REGIONSPOTTERWIN32_H