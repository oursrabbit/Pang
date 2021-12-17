/*
 *  RegionSpotter.h
 *  Spot a Pro Tools region from an external program
 *  Author: Bob Lee, 2/7/2005
 *	
 *  Copyright (c) 2005
 *  Digidesign, A Division of Avid
 */

#ifndef REGIONSPOTTER_H
#define REGIONSPOTTER_H

/*! \brief API for spotting a region from an external program
 *
 *  The RegionSpotter class allows external programs to spot audio into a Pro Tools region.  It
 *    sends an XML message on Windows, or an AppleEvent on Macintosh.
 *
 *  Currently, the preprocessor definition \c WIN32 determines whether a Macintosh or Windows
 *    RegionSpotter object is created.  This can be changed in RegionSpotter.cpp
 *
 *  \par Compatibility:
 *  \li Macintosh: Pro Tools version 5.1 or later.
 *  \li Windows: Pro Tools version 6.7 or later.
 */
class RegionSpotter {

	public:

		/*! \brief Static function for creating a RegionSpotter object
		 * 
		 *  \par Undefined when:
		 *  \li regionStartSample or regionStopSample is larger than the number of samples in the source file
		 *  \li regionStartSample is larger than regionStopSample
		 *  \li file does not exist or cannot be read
		 *
		 *  \param filenameString A null-terminated char array of the absolute path to the input audio file
		 *  \param regionStartSample The first sample of the audio file to be included in the region
		 *  \param regionStopSample The last sample of the audio file to be included in the region
		 *  \retval RegionSpotter* Returns a pointer to a platform specific RegionSpotter object
		 */
		static RegionSpotter* CreateRegionSpotter( 
							const char* filenameString,		// String of absolute filename
							long regionStartSample,			// Start location of region in audio file.
							long regionStopSample			// Stop location of region in audio file.
						);

		// DNU! - Use RegionSpotter::CreateRegionSpotter(...) static method instead of constructor!
		RegionSpotter(){}
		virtual ~RegionSpotter(){}

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
		virtual int spot( short trackOffset,
						  long spotLocationSample,
						  short playlistNumber,
						  const char* regionNameString
						) = 0;

	private:
		// NOT IMPLEMENTED
		RegionSpotter(const RegionSpotter &);
		RegionSpotter& operator=(const RegionSpotter &);
};


#endif  //  REGIONSPOTTER_H