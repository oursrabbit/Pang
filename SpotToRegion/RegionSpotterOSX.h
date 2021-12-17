/*
 *  RegionSpotterOSX.h
 *  Spot a Pro Tools region from an external Windows program
 *  Author: Bob Lee, 2/7/2005
 *
 *  Copyright (c) 2005
 *  Digidesign, A Division of Avid
 *
 */

#ifndef REGIONSPOTTEROSX_H
#define REGIONSPOTTEROSX_H

#include <Carbon/Carbon.h>
#include "RegionSpotter.h"

class RegionSpotterOSX : public RegionSpotter {

	public:
		// See parameter descriptions in RegionSpotter.h
		RegionSpotterOSX( const char *filenameString,		
							long regionStartSample,	
							long regionStopSample);


		// Spots audio to a location from another App into ProTools using Apple Events
  		//  by Bill Mitsakos, 2000
		int spot(short trackOffset, 
						long spotLocationSample, 
						short playlistNumber, 
						const char *regionNameString);

	private:
			AliasHandle 		filenameAlias;
			int					yourStartSample;
			int					yourStopSample;
};


#endif  //    REGIONSPOTTEROSX_H