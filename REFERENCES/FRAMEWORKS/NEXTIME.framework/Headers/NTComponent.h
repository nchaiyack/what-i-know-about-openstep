/*
 *  NTComponent.h
 * 	Copyright 1992, NeXT Computer, Inc.
 *	
 *	In-core representation of a potentially loadable object
 *	and it's properties
 *
 *	17 Sept 1992 mpaque Created.
 */
#import <Foundation/NSObject.h>
#import <Foundation/NSArray.h>
#import <Foundation/NSString.h>
#import <Foundation/NSBundle.h>
#import <Foundation/NSDictionary.h>
#import "NTValueDictionary.h"

@protocol NTComponent <NSObject>
// The NTComponent class provides a way for an instance to find it's
// class's component, for access to component resources.

// Given a principal class, return the component
+ componentForClass:class;

// Given a directory, build a list of components for the
// bundle in the directory.
+ (NSArray *)newForDirectory:(NSString *)fullpath;

// Access to NTComponent contents
- (NSBundle *)bundle;
- (bycopy NSDictionary *)dictionary;
- principalClass;
- classNamed:(NSString *)classname;

// Construction of instances from the classes within the component
- newInstance;
- newInstanceFromClassNamed:(in NSString *)classname;

@end

@class NSLock;

@interface NTComponent:NSObject <NTComponent>
{
@private
	NSLock *		instLock;
	unsigned		refcount;
	id			bundle;		// Private subclass of NXBundle
	NSMutableDictionary *	dictionary;
	Class			_principalClass;
	struct mach_header *	_mach_header;
	BOOL			_codeLoaded;
}

+ (void)initialize;

// Initialize and return a list of components from a bundle directory
+ (NSArray *)newForDirectory:(NSString *)fullpath;

// designated initializer
- initWithDictionary	:(NSDictionary *)dictionary
	forBundle	:(NSBundle *)bundle;
- (struct mach_header *)machHeader;


@end

