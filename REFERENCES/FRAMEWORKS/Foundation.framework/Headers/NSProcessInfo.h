/*	NSProcessInfo
	Copyright 1994-1996, NeXT Software, Inc.  All rights reserved.
*/

#import <Foundation/NSObject.h>

enum {	/* Constants returned by -operatingSystem */
	NSWindowsNTOperatingSystem = 1,
	NSWindows95OperatingSystem,
	NSSolarisOperatingSystem,
	NSHPUXOperatingSystem,
	NSMACHOperatingSystem,
	NSSunOSOperatingSystem,
	NSOSF1OperatingSystem
};

@class NSArray, NSString, NSDictionary;

@interface NSProcessInfo : NSObject {
    @private	
    NSDictionary	*environment;
    NSArray		*arguments;
    NSString		*hostName;    
    NSString		*name;
    void		*reserved;
}

+ (NSProcessInfo *)processInfo;	

- (NSDictionary *)environment;

- (NSArray *)arguments;

- (NSString *)hostName;

- (NSString *)processName;

- (void)setProcessName:(NSString *)newName;

- (NSString *)globallyUniqueString;

#if !defined(STRICT_OPENSTEP)

- (unsigned int)operatingSystem;

#endif /* STRICT_OPENSTEP */

@end
