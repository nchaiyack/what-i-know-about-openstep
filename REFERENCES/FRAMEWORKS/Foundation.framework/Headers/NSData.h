/*	NSData.h
	Object container for bags of bytes
	Copyright 1994-1996, NeXT Software, Inc.  All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSRange.h>

@class NSString;

/****************	Immutable Data		****************/

@interface NSData : NSObject <NSCopying, NSMutableCopying, NSCoding>

- (unsigned)length;
- (const void *)bytes;

@end

@interface NSData (NSExtendedData)

- (NSString *)description;
- (void)getBytes:(void *)buffer;
- (void)getBytes:(void *)buffer length:(unsigned)length;
- (void)getBytes:(void *)buffer range:(NSRange)range;
- (BOOL)isEqualToData:(NSData *)other;
- (NSData *)subdataWithRange:(NSRange)range;
- (BOOL)writeToFile:(NSString *)path atomically:(BOOL)useAuxiliaryFile;

@end

@interface NSData (NSDataCreation)

+ (id)data;
+ (id)dataWithBytes:(const void *)bytes length:(unsigned)length;
+ (id)dataWithBytesNoCopy:(void *)bytes length:(unsigned)length;
+ (id)dataWithContentsOfFile:(NSString *)path;
+ (id)dataWithContentsOfMappedFile:(NSString *)path;
- (id)initWithBytes:(const void *)bytes length:(unsigned)length;
- (id)initWithBytesNoCopy:(void *)bytes length:(unsigned)length;
- (id)initWithContentsOfFile:(NSString *)path;
- (id)initWithContentsOfMappedFile:(NSString *)path;
- (id)initWithData:(NSData *)data;

#if !defined(STRICT_OPENSTEP)
+ (id)dataWithData:(NSData *)data;
#endif /* !STRICT_OPENSTEP */

@end

/****************	Mutable Data		****************/

@interface NSMutableData : NSData

- (void *)mutableBytes;
- (void)setLength:(unsigned)length;

@end

@interface NSMutableData (NSExtendedMutableData)

- (void)appendBytes:(const void *)bytes length:(unsigned)length;
- (void)appendData:(NSData *)other;
- (void)increaseLengthBy:(unsigned)extraLength;
- (void)replaceBytesInRange:(NSRange)range withBytes:(const void *)bytes;
- (void)resetBytesInRange:(NSRange)range;

#if !defined(STRICT_OPENSTEP)
- (void)setData:(NSData *)data;
#endif /* !STRICT_OPENSTEP */

@end

@interface NSMutableData (NSMutableDataCreation)

+ (id)dataWithCapacity:(unsigned)aNumItems;
+ (id)dataWithLength:(unsigned)length;
- (id)initWithCapacity:(unsigned)capacity;
- (id)initWithLength:(unsigned)length;

@end

