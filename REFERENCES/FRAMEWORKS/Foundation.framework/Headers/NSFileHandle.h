/*	NSFileHandle.h
	Basic operations on open files and communication channels
	Copyright 1994-1996, NeXT Software, Inc.  All rights reserved.
*/

#if !defined(STRICT_OPENSTEP)

#import <Foundation/NSObject.h>
#import <Foundation/NSArray.h>
#import <Foundation/NSRange.h>

@class NSString, NSData;

@interface NSFileHandle : NSObject

- (NSData *)availableData;

- (NSData *)readDataToEndOfFile;
- (NSData *)readDataOfLength:(unsigned int)length;

- (void)writeData:(NSData *)data;

- (unsigned long long)offsetInFile;
- (unsigned long long)seekToEndOfFile;
- (void)seekToFileOffset:(unsigned long long)offset;

- (void)truncateFileAtOffset:(unsigned long long)offset;
- (void)synchronizeFile;
- (void)closeFile;

@end

@interface NSFileHandle (NSFileHandleCreation)

+ (id)fileHandleWithStandardInput;
+ (id)fileHandleWithStandardOutput;
+ (id)fileHandleWithStandardError;

#if !defined(STRICT_40)
+ (id)fileHandleWithNullDevice;
#endif

+ (id)fileHandleForReadingAtPath:(NSString *)path;
+ (id)fileHandleForWritingAtPath:(NSString *)path;
+ (id)fileHandleForUpdatingAtPath:(NSString *)path;

@end

FOUNDATION_EXPORT NSString *NSFileHandleOperationException;

FOUNDATION_EXPORT NSString *NSFileHandleReadCompletionNotification;
FOUNDATION_EXPORT NSString *NSFileHandleReadToEndOfFileCompletionNotification;
FOUNDATION_EXPORT NSString *NSFileHandleConnectionAcceptedNotification;
#if !defined(STRICT_41) && !defined(STRICT_40)
FOUNDATION_EXPORT NSString *NSFileHandleDataAvailableNotification;
#endif

FOUNDATION_EXPORT NSString *NSFileHandleNotificationDataItem;
FOUNDATION_EXPORT NSString *NSFileHandleNotificationFileHandleItem;
FOUNDATION_EXPORT NSString *NSFileHandleNotificationMonitorModes;

@interface NSFileHandle (NSFileHandleAsynchronousAccess)

- (void)readInBackgroundAndNotifyForModes:(NSArray *)modes;
- (void)readInBackgroundAndNotify;

- (void)readToEndOfFileInBackgroundAndNotifyForModes:(NSArray *)modes;
- (void)readToEndOfFileInBackgroundAndNotify;

- (void)acceptConnectionInBackgroundAndNotifyForModes:(NSArray *)modes;
- (void)acceptConnectionInBackgroundAndNotify;

#if !defined(STRICT_41) && !defined(STRICT_40)
- (void)waitForDataInBackgroundAndNotifyForModes:(NSArray *)modes;
- (void)waitForDataInBackgroundAndNotify;
#endif

@end

@interface NSFileHandle (NSFileHandlePlatformSpecific)

#if defined(WIN32)
#if !defined(STRICT_40)
- (id)initWithNativeHandle:(void *)nativeHandle closeOnDealloc:(BOOL)closeopt;
#endif
- (id)initWithNativeHandle:(void *)nativeHandle;
- (void *)nativeHandle;
#endif

#if !defined(STRICT_40)
- (id)initWithFileDescriptor:(int)fd closeOnDealloc:(BOOL)closeopt;
#endif
- (id)initWithFileDescriptor:(int)fd;
- (int)fileDescriptor;

@end

@interface NSPipe : NSObject

- (NSFileHandle *)fileHandleForReading;
- (NSFileHandle *)fileHandleForWriting;

- (id)init;
+ (id)pipe;

@end

#endif /* !STRICT_OPENSTEP */
