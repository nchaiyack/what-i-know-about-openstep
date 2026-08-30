/*
 *  NTComponentManager.h
 * 	Copyright 1992, NeXT Computer, Inc.
 *	
 *	Protocol and default implementation for a finder of loadable
 *	objects.
 *
 *	17 Sept 1992 mpaque Created.
 */

#import <Foundation/NSObject.h>
#import <Foundation/NSDictionary.h>
#import <Foundation/NSArray.h>
#import <Foundation/NSString.h>
#import "NTValueDictionary.h"
#import "NTComponent.h"

@protocol NTComponentManager <NSObject>
//
// Default component access methods, as convenience methods
//
- init;
- (void)dealloc;

- defaultComponentWithDescription:(in bycopy NSDictionary *)description;
- defaultComponentClassWithDescription:
				(in bycopy NSDictionary *)description;
- defaultComponentInstanceWithDescription:
				(in bycopy NSDictionary *)description;


- componentInstance: comp;	// Given a component, return an instance

// Method to set a default Component Item
- (BOOL)setDefaultComponentItem:(in id)item;

// Register a component bundle.  Returns a list of component item instances
// built from the bundle.  Unregister using the returned instance
- (NSArray *)registerComponentBundle:(in NSString *)bundleDir;

// Register a component item
- registerComponent:item;

// Unregister a component item
- unregisterComponent:item;

// map from a class back to a component
- componentForClass:class;

//
// The following routines generate sublists of type (NSArray *)
// holding copies of all components.
//
- (NSArray *)components; // Returns a copy of the master list of all components

// Return a list of all components in master list which match description
- (NSArray *)componentsWithDescription	:(in bycopy NSDictionary *)description;

// Return a list of all components in argument list which match description
- (NSArray *)componentsWithDescription	:(in bycopy NSDictionary *)description
		fromList	:(NSArray *)list;

@end

@class NSLock;

@interface NTComponentManager:NSObject <NTComponentManager>
{
@private
	NSMutableArray *	componentList;
	NSLock *		instLock;
	int			_refcount;
}

+ (void)startup;
- initWithDirectory:(NSString *)dirname;
- initWithDirectories:(NSArray *)dirnames; // designated initializer
@end
