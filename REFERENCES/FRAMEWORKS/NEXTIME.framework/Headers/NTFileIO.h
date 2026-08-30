/*
 *  NTFileIO.h
 * 	Copyright 1993, NeXT Computer, Inc.
 *	
 *	Protocol to be implemented by File IO objects which are used by
 *	a media object.  The protocol specifies the API used by a media object
 *	in reading samples from a file or appending samples to a file, and the
 *	methods to be used in enabling or disabling write access.
 *
 *	19 April 1993 mpaque Created.
 */
#import <Foundation/NSObject.h>
#import <Foundation/NSString.h>

typedef unsigned long NTFilePosition;
typedef unsigned long NTFileSize;

@protocol NTFileIO <NSObject>

/*
 * These methods all return nil on an error, or self on success.
 * In the event of an error in readData, the contents of the NSData buffer are
 * undefined.
 */
- initWithFile:(NSString *)name forWriting:(BOOL)writable;
- initWithFile:(NSString *)name;
- (void)dealloc;
- (void)truncate:(NTFilePosition)pos;
- (NTFilePosition)currentPosition;
- (NTFilePosition)length;	/* Current file length */
- (BOOL)setWriteEnable:(BOOL)writable;
- (BOOL)isWriteEnabled;
- (NSString *)filename;

- readData:(NSMutableData *)data fromPosition:(NTFilePosition)pos;
- appendData:(NSData *)data atPosition:(NTFilePosition *)pos;

- (NTFileSize)readBytes:(void *)data maxLength:(NTFileSize)len fromPosition:(NTFilePosition)pos;
- (NTFileSize)writeBytes:(void *)data length:(NTFileSize)len toPosition:(NTFilePosition)pos;
- (NTFileSize)appendBytes:(void *)data length:(NTFileSize)len atPosition:(NTFilePosition *)pos;
@end

/*
 * File I/O implementation for large data transfers. This is a simple
 * thread-safe wrapper around traditional Unix I/O operations.
 * It should be portable to non-Unix systems with litle difficulty.
 */

@interface NTFileIO: NSObject <NTFileIO>
{
@private
	id <NTFileIO>	sharedFile;
	BOOL		isWritable;
}
@end
