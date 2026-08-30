#import <Foundation/NSObject.h>
#import <Foundation/NSString.h>
#import <Foundation/NSThread.h>
#import <Foundation/NSLock.h>
#import <Foundation/NSZone.h>
#import "NTDictionaryKeys.h"
#import "NTComponentManager.h"
#import "NTErrorMonitor.h"

// Protocol for context client.  Used for keepalive pings
@protocol NTClient
- (void)pingClient;
@end
// Protocol for the NTContext API that we export for use by the NTClient
// object.
@protocol NTContext <NTErrorGenerator>
- (NTComponentManager *)componentManager;
- (void)pingServer:(id <NTClient>)client;	// target for keepalive pings from client
@end

/* NSNotification names */
extern NSString *NTContextWillTerminateNotification;

/*
 * A class for representing a context within the NT server.
 * Contexts are associated with a specific client connection.
 * Each context holds a zone used for all memory allocation within the
 * context.  One or more cthreads may share a context.
 *
 * Contexts also hold generally useful context dependent information, including
 * a Component Manager instance.
 *
 */
@interface NTContext: NSObject <NTContext>
{
@private
	int			_refcount;
	NSLock			*contextLock;
	NSLock			*zoneLock;
	NTComponentManager	*componentManager;
	NSZone *		sampleZone;
	NSZone *		zone;
	NSString *		name;
	id <NTErrorMonitor>	errorMonitor;
	BOOL			connIsOK;
}

//
// Construct a new context, running in a new thread, and return the name
// it is advertised with.  This is the factory through which all new
// contexts are normally constructed.
//
+ (NSString *)nameForNewContext;

/* Create a new context, with a new zone */
+ new;

/* Return the current context instance. */
+ (NTContext *)currentContext;

/*
 * Return the root context instance, used to hold
 * everything not claimed by other contexts.
 */
+ (NTContext *)rootContext;
/*
 * Add a thread to a context. If the thread is a member of another context
 * that context is dereferenced, possibly freeing it.
 */
+ (void)addThread:(NSThread *)thread toContext:(NTContext *)context;
+ (void)removeThread:(NSThread *)thread;

/* Support for creating new contexts and service threads on new connections */
- (void)runConnection;

- init;
- (void)dealloc;
- (NSZone *)zone;

- (NSZone *)sampleZone;	// Return playback zone, creating it if needed.
- (void)freeSampleZone;	// Destroy the playback zone and it's contents
- (void)wireSampleZone;	// Try to make the zone's pages resident
- (void)unwireSampleZone;	// Try to make the zone's pages non-resident

- (NSLock *)zoneLock;

- (NSString *)name;

- (void)postErrorTitle:(NSString *)title
	message:(NSString *)msg
	details:(NSString *)details
	errorCode:(NSString *)code;

- (void)postErrorForClass:(id)class
	title:(NSString *)title
	prefix:(NSString *)prefix
	filename:(NSString *)file
	message:(NSString *)message
	details:(NSString *)details
	errorCode:(NSString *)code;

@end

// Interesting messages a context can send to registered objects
@interface NSObject(NTContextEvents)
- (void)contextWillTerminate:(id)sender;
@end
