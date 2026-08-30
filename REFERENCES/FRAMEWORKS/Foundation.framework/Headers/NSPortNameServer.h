/*      NSPortNameServer.h
	A basic name server for ports
	Copyright 1994-1996, NeXT Software, Inc.  All rights reserved.
*/

#if !defined(STRICT_OPENSTEP)

#import <Foundation/NSObject.h>

@class NSString, NSPort;

@interface NSPortNameServer : NSObject

+ (id)defaultPortNameServer;

- (NSPort *)portForName:(NSString *)name;
- (NSPort *)portForName:(NSString *)name host:(NSString *) host;

- (BOOL)registerPort:(NSPort *)port name:(NSString *)netName;

- (void)removePortForName:(NSString *)key;

@end

@interface NSPortNameServer (NSPortNameServerObsolete)
- (NSPort *)portForName:(NSString *)name onHost:(NSString *) host;
- (BOOL)registerPort:(NSPort *)port forName:(NSString *)netName;
@end


#endif /* !STRICT_OPENSTEP */
