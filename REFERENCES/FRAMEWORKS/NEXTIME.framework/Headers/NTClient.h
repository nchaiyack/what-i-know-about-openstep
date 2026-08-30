/*
 *  NTClient.m
 * 	Copyright 1992, NeXT Computer, Inc.
 *	
 *
 *	A simple class to establish a connection with the NEXTIME server,
 *	and vend a proxy to the Component Manager.
 *
 *	17 Sept 1992 mpaque Created.
 */
#import <Foundation/NSObject.h>
#import <Foundation/NSDictionary.h>
#import "NTErrorMonitor.h"

/*
 * Notification posted on NTServer death.
 */
extern NSString * NTServerDidDieNotification;

@interface NTClient:NSObject <NTErrorMonitor>
{
@private
	id			serverContext;	// Server thread proxy
	id			componentManager; // NTComponentManager proxy
	NSDictionary *		lastError;
	void *			_private;
}

+ sharedClient;	// Returns task-wide shared instance - preferred initializer
+ new;		// Returns new instance
- init;
- (id)componentManager;
- (void)dealloc;
- (id)connection;
@end

