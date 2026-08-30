/*
 * Definitions of types used in NeXTime movie representation.
 *
 */
#import "typetags.h"

/*
 * Player hints, for the NTMovie setPlayHints and playHints methods.
 * All values should be powers of 2 (bit definitions).
 */
typedef enum
{
	NTHintPlayMode		= 0,
	NTHintScrubMode		= 1 << 0
} NTPlayHintFlags;


/*
 * Interesting time flags, for calls to getNextInterestingTime method
 * in NTMedia, NTTrack, and NTMovie.
 */
typedef enum
{
	NTNextMediaSample	= 1 << 0,
	NTNextMediaEdit		= 1 << 1,
	NTNextTrackEdit		= 1 << 2,
	NTNextSyncSample	= 1 << 3,
	NTTimeEdgeOK		= 1 << 30,
	NTIgnoreActiveSegment	= 1 << 31
} NTInterestingTimeFlags;

/*
 * Flags denoting the use of the track in the movie, preview, or poster.
 */
typedef enum
{
	NTUsageInMovie		= 1 << 1,
	NTUsageInPreview	= 1 << 2,
	NTUsageInPoster		= 1 << 3
} NTUsage;

/*
 * 3x3 transformation matrix
 */
typedef struct
{
	double		a;
	double		b;
	double		u;
	double		c;
	double		d;
	double		v;
	double		x;
	double		y;
	double		w;
}
NTMatrix;
