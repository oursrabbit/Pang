/*
 *  RegionSpotter.cpp
 *  Spot a Pro Tools region from an external program
 *  Author: Bob Lee, 2/7/2005
 *
 *  Copyright (c) 2005
 *  Digidesign, A Division of Avid
 *
 */

#include "RegionSpotter.h"

#ifdef WIN32
	#include "RegionSpotterWin32.h"
#else
	#include "RegionSpotterOSX.h"
#endif


RegionSpotter* RegionSpotter::CreateRegionSpotter(const char *filenameString,	
									long regionStartSample, long regionStopSample) {
    #ifdef WIN32
        return new RegionSpotterWin32(filenameString, regionStartSample, regionStopSample);
    #else
        return new RegionSpotterOSX(filenameString, regionStartSample, regionStopSample);

    #endif
}
