#include <JuceHeader.h>
class RegionSpotter {

public:
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
	static void Spot(juce::int64 startSample, juce::int64 endSample
		/* short trackOffset,
		long spotLocationSample,
		short playlistNumber,
		const char* regionNameString */);

    static void Spot(juce::int64 startSample, juce::int64 endSample, short pl
            /* short trackOffset,
            long spotLocationSample,
            short playlistNumber,
            const char* regionNameString */);
};