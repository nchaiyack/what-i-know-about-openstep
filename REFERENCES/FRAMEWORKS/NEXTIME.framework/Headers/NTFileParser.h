/*
 *  NTFileParser.h
 * 	Copyright 1994, NeXT Computer, Inc.
 *	
 *	API for objects which parse files into movie objects.
 *
 *	27 Jan 1994 mpaque Created.
 *	28 Mar 1994 mpaque Add file write and copy/paste API.
 */
#import <Foundation/NSObject.h>
#import <Foundation/NSDictionary.h>
#import <Foundation/NSData.h>
#import "NTMovie.h"

@protocol NTFileParser <NSObject>
/*
 * The parameters dictionary must contain a NTFilename key, specifying the 
 * file data will be loaded from.
 */
- (id <NTMovie>)initMovieWithParameters:(bycopy NSDictionary *)parameters;
@end

/*
 * File parser extensions to support copy and paste operations
 * capable of persisting beyond the life of an NTServer.
 */
@protocol NTPasteboardMovieParser <NSObject>
/*
 * Constructs and returns a memory object referencing "movie".
 * 
 * In the case of the QuickTime format file parser, the
 * object contains a data reference for each media in the movie,
 * along with detailed control information.
 *
 * The object can be placed on the pasteboard using the
 * pasteboard writeType:data:length method. The returned
 * data value should be marked for delayed free once it
 * is passed over a DO connection.  This causes the
 * server's copy of the data to be freed once the data has
 * reached the client.
 */
- (NSData *)pasteboardImageFromMovie:(id <NTMovie>)movie;

/*
 * Initialize a NTMovie from an NSData object built from
 * the pasteboard.  The pasteboard data should have originated from
 * a call to dataReferenceFromMovie:.  'data' is freed once the
 * movie is initialized.
 */
- (id <NTMovie>)movieFromPasteboardImage:(NSData *)data;

@end

/*
 * API to be used by components capable of saving movie data to a file.
 */
@protocol NTFileWriter <NSObject>
/*
 * Writes movie to a file.  Samples from active tracks
 * within the active time range for each track are copied
 * to the file, with interleaving between each track's data.
 * The movie is saved to a "~" file which is renamed to file
 * when writing is completed.
 *
 * This is the  preferred way to save a file after performing
 * edits, to produce a result with good playback performance.
 *
 * The parameters dictionary must contain a NTFilename key, specifying the 
 * file data will be saved to, and may also contain subdictionaries indicating
 * how the media should be encoded.
 */
- (BOOL)writeAndFlattenMovie:(id <NTMovie>)movie
	withParameters:(bycopy NSDictionary *)parameters;
	

/*
 * Write or update a movie to a file.  If the file exists,
 * this method updates the file's control
 * structures if possible.  In the case of a QuickTime movie,
 * this rewrites the MooV atom in the file.  If the file does
 * not exist, or cannot be updated or overwritten, then the movie is saved
 * using an atomic write, as in writeAndFlattenMovie:toFile:
 *
 * The parameters dictionary must contain a NTFilename key, specifying the 
 * file data will be saved to, and may also contain subdictionaries indicating
 * how the media should be encoded.
 */
- (BOOL)writeMovie:(id <NTMovie>)movie
	withParameters:(bycopy NSDictionary *)parameters;

/*
 * Create a new movie file, reserving space for whatever header is needed.
 * Destroys any existing file!
 * The parameters dictionary must contain a NTFilename key, specifying the 
 * file to be created.
 */
- (BOOL) newMovieFileWithParameters:(bycopy NSDictionary *)param;

@end
