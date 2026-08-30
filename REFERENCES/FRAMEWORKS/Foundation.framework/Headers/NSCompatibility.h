/*	NSCompatibility.h
	Copyright 1994-1996, NeXT Software, Inc.  All rights reserved.
*/

#if !defined(STRICT_OPENSTEP)

/***************        Compatibility with NEXTSTEP 3.0         ***********/

#import <objc/Object.h>
#import <Foundation/NSCoder.h>
#import <Foundation/NSData.h>

#if !defined(__TEFLON__)
#import <remote/NXConnection.h>
#endif

@interface Object (NSCompatibility)

- (BOOL)respondsToSelector:(SEL)sel;
- (BOOL)conformsToProtocol:(Protocol *)protocol;
- (BOOL)isKindOfClass:(Class)cls;
- (BOOL)isMemberOfClass:(Class)cls;
- (id)performSelector:(SEL)sel withObject:(id)object;
- (id)performSelector:(SEL)sel withObject:(id)object1 withObject:(id)object2;
- (NSString *)description;
- (id)retain;
- (unsigned)retainCount;
- (void)release;
- (id)autorelease;
+ (id)allocWithZone:(NSZone *)zone;
- (id)copyWithZone:(NSZone *)zone;
- (void)dealloc;
+ (void)poseAsClass:(Class)cls;
+ (BOOL)instancesRespondToSelector:(SEL)sel;
- (IMP)methodForSelector:(SEL)sel;
+ (IMP)instanceMethodForSelector:(SEL)sel;
- (void)doesNotRecognizeSelector:(SEL)sel;
- (id)initWithCoder:(NSCoder *)coder;
- (void)encodeWithCoder:(NSCoder *)coder;
- (id)awakeAfterUsingCoder:(NSCoder *)coder;

@end

/********	Compatibility with NEXTSTEP 3.0 archiving	**********/

FOUNDATION_EXPORT void NXWriteNSObject(NXTypedStream *typedStream, NSObject *object);
    /* Writes object onto the typedStream; no sharing is possible across separate NXWriteNSObject */
    
FOUNDATION_EXPORT NSObject *NXReadNSObject(NXTypedStream *typedStream);
    /* Reads an object written with NXWriteNSObject; returned object is autoreleased */

FOUNDATION_EXPORT NSObject *NXReadNSObjectFromCoder(NSCoder *decoder);
    /* Reads an object written with NXWriteNSObject given an NSCoder; returned object is autoreleased */

@interface NSCoder (NSTypedstreamCompatibility)

- (void)encodeNXObject:(Object *)object;
    /* Writes old-style object onto the coder; no shraing is possible across separate -encodeNXObject */
    
- (Object *)decodeNXObject;
    /* recovers object written with -encodeNXObject */
    
@end

/********	Compatibility with NEXTSTEP 3.0 streams	**********/

@interface NSData (NSDataCreationFromNXStream)

+ (id)dataWithStream:(NXStream *)stream;
    /* Reads bytes from stream till the end */

- (id)initWithStream:(NXStream *)stream;

@end

#if !defined(__TEFLON__)
/******************* 3.0 DO compatibility **********************/

@interface NXAutoreleaseConnection : NXConnection
@end

// Run old DO via the RunLoop - moral equivalent to runFromAppKit

@interface NXConnection (NSRunFromRunLoop)
- (void)runFromRunLoop;
@end
#endif

#endif /* !STRICT_OPENSTEP */
