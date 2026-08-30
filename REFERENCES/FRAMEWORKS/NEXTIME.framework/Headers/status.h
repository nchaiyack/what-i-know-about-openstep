 
/*
 * Status codes, reported by NTMovie, NTTrack, and NTMedia status methods
 */
typedef enum
{
	NTStatusSuccess = 0,
	NTStatusCorruptData,
	NTStatusCorruptFile,
	NTStatusBadImageDescription,
	NTStatusBadSoundDescription,
	NTStatusBadDataDescription,
	NTStatusBadComponentType,
	NTStatusNoMediaHandler,
	NTStatusNoDataHandler,
	NTStatusInvalidMedia,
	NTStatusInvalidTrack,
	NTStatusInvalidMovie,
	NTStatusInvalidSampleTable,
	NTStatusInvalidDataReference,
	NTStatusInvalidDuration,
	NTStatusInvalidTime,
	NTStatusBadEditList,
	NTStatusFileWriteError,
	NTStatusFileCreateError,
	NTStatusInvalidEditState,
	NTStatusEditStateMismatch,
	NTStatusStaleEditState,
	NTStatusUserDataNotFound,
	NTStatusUserDataItemNotFound,
	NTStatusBadTrackIndex,
	NTStatusTrackIDNotFound,
	NTStatusTrackNotInMovie,
	NTStatusTimeNotInTrack,
	NTStatusTimeNotInMedia,
	NTStatusBadEditIndex,
	NTStatusCantEnableTrack,
	NTStatusInvalidSampleNumber,
	NTStatusInvalidSampleDescription,
	NTStatusInvalidDataOperation,
	NTStatusAtEndOfData,
	NTStatusInternalError
} NTStatusCode;

