/*	NSDebug.h
	Debug utilities - do not depend on this in production code
	Copyright 1994-1996, NeXT Software, Inc.  All rights reserved.
*/

#if !defined(STRICT_OPENSTEP)

/**************************************************************************
WARNING: Unsupported API.

This module contains material that is only partially supported -- if
at all.  Do not depend on the existance of any of these symbols in your
code in future releases of this software.  Certainly, do not depend on
the symbols in this header in production code.  The format of any data
produced by the functions in this header may also change at any time.

However, it should be noted that the features in this file have been
found to be generally useful, and in some cases invaluable, and are not
likely to go away anytime soon. Some of these facilities, unfortunately,
are oriented towards most convenient use on a UNIX-like platform.
**************************************************************************/

#import <Foundation/NSObject.h>
#import <Foundation/NSAutoreleasePool.h>

/* The environment component of this API

The boolean- and integer-valued variables declared in this header,
plus some values set by methods, read starting values from the
process's environment at process startup.  This is mostly a benefit
if you need to initialize these variables to some non-default value
before your program's main() routine gets control, but it also
allows you to change the value without modifying your program's
source. (Variables can be set and methods called around specific
areas within a program, too, of course.)

This opens the door to various possibilites, such as a
statistics-gathering application which spawns off the process to
be measured, providing a custom environment.  The parent process
could then read the output of the statistics from the file
descriptor it had opened, and specified in the environment.

In sh/ksh/zsh or other sh-influenced shell, you can set the value in
the environment like this:
% export NSKeepAllocationStatistics=YES
% myProg

or for just that process:
% NSKeepAllocationStatistics=YES myProg

In a csh/tcsh or other csh-influenced shell, you do this:
> setenv NSKeepAllocationStatistics YES
> myProg


The initialization from the environment happens very early, but may
not have happened yet at the time of a +load method statically linked
into an application (as opposed to one in a dynamically loaded module). 
But as noted in the "Foundation Release Notes", +load methods that are
statically linked into an application are tricky to use and are not
recommended.

Here is a table of the variables/values initialized from the environment
at startup.  Some of these just set variables, others call methods to
set the values.

NAME OF ENV. VARIABLE			DEFAULT		SET IT TO...
NSDebugEnabled				  NO		"YES"
NSZombieEnabled				  NO		"YES"
NSDeallocateZombies			  NO		"YES"
NSHangOnMallocError			  NO		"YES"

NSNegativeRetainCheckEnabled		  NO		"YES"

NSEnableAutoreleasePool			  YES		"NO"
NSAutoreleaseFreedObjectCheckEnabled	  NO		"YES"
NSAutoreleaseHighWaterMark		  0		non-negative integer
NSAutoreleaseHighWaterResolution	  0		non-negative integer

NSKeepZoneStatistics			  NO		"YES"
NSZoneStatisticsFD			  file in /tmp	open file descriptor number
NSZoneStatisticsOutputVersion		  16		16 or 18
NSZoneStatisticsOutputMask		  0xFFFF	16-bit decimal, hex, or octal number

NSKeepAllocationStatistics		  NO		"YES"
NSAllocationStatisticsFD		  file in /tmp	open file descriptor number
NSAllocationStatisticsOutputVersion	  16		16 or 18
NSAllocationStatisticsOutputMask	  0xFFFF	16-bit decimal, hex, or octal number

NSKeepNotificationStatistics		  NO		"YES"
NSNotificationStatisticsFD		  file in /tmp	open file descriptor number

*/

/****************	General		****************/

FOUNDATION_EXPORT BOOL NSDebugEnabled;
	// Mostly used to turn on the stack-processing and recording facility.
	// The 'oh' command can be used to most easily access this facility.
	// The default is NO. ('oh' is currently available only on MACH.)

FOUNDATION_EXPORT BOOL NSZombieEnabled;
	// Enable object zombies. When an object is deallocated, its isa
	// pointer is modified to be that of a "zombie" class (whether or
	// not the storage is then freed can be controlled by the
	// NSDeallocateZombies variable). Messages sent to the zombie
	// object cause logged messages and can be broken on in a debugger.
	// The default is NO.

FOUNDATION_EXPORT BOOL NSDeallocateZombies;
	// Determines whether the storage of objects that have been
	// "zombified" is then freed or not. The default value (NO)
	// is most suitable for debugging messages sent to zombie
	// objects. And since the memory is never freed, storage
	// allocated to an object will never be reused, either (which
	// is sometimes useful otherwise).

FOUNDATION_EXPORT BOOL NSHangOnMallocError;
	// MACH only: Cause the process to hang after printing out the
	// "Malloc-related error detected with code N" message to stderr.
	// A backtrace can be gotten from the process with the 'sample'
	// utility. The default is NO. Has no effect on non-MACH platforms.


/****************	Stack processing/recording	****************/

FOUNDATION_EXPORT void NSDebugRecordObjectAndStack(id self);
	// Used with NSDebugEnabled to record object history. In a
	// method, use like:
	//     if (NSDebugEnabled) NSDebugRecordObjectAndStack(self);
	// The 'oh' command can be used to dump the recorded information.
	// ('oh' is currently available only on MACH.)

#if !defined(STRICT_40)

FOUNDATION_EXPORT void *NSFrameAddress(unsigned frame);
FOUNDATION_EXPORT void *NSReturnAddress(unsigned frame);
	// Returns the value of the frame pointer or return address,
	// respectively, of the specified frame. Frames are numbered
	// sequentially, with the "current" frame being zero, the
	// previous frame being 1, etc. The current frame is the
	// frame in which either of these functions is called. For
	// example, NSReturnAddress(0) returns an address near where
	// this function was called, NSReturnAddress(1) returns the
	// address to which control will return when current frame
	// exits, etc. If the requested frame does not exist, then
	// NULL is returned. The behavior of these functions is
	// undefined in the presence of code which has been compiled
	// without frame pointers.

FOUNDATION_EXPORT unsigned NSCountFrames(void);
	// Returns the number of call frames on the stack. The behavior
	// of this functions is undefined in the presence of code which
	// has been compiled without frame pointers.

#endif

/****************	Autorelease pool debugging	****************/

@interface NSAutoreleasePool (NSAutoreleasePoolDebugging)

// Functions used as interesting breakpoints in a debugger
FOUNDATION_EXPORT void _NSAutoreleaseNoPool(void *object);
	// Called to log the "Object X of class Y autoreleased with no
	// pool in place - just leaking" message.

FOUNDATION_EXPORT void _NSAutoreleaseFreedObject(void *freedObject);
	// Called when a previously freed object would be released
	// by an autorelease pool. See +enableFreedObjectCheck: below.

FOUNDATION_EXPORT void _NSAutoreleaseHighWaterLog(unsigned int count);
	// Called whenever a high water mark is reached by a pool.
	// See +setPoolCountHighWaterMark: below.

+ (void)enableRelease:(BOOL)enable;
	// Enables or disables autorelease pools; that is, whether or
	// not the autorelease pools send the -release message to their
	// objects when each pool is released. This message affects only
	// the pools of the autorelease pool stack of the current thread
	// (and any future pools in that thread). The "default default"
	// value can be set in the initial environment when a program
	// is launched with the NSEnableAutoreleasePool environment
	// variable (see notes at the top of this file) -- as thread
	// pool-stacks are created, they take their initial enabled
	// state from that environment variable.

+ (void)showPools;
	// Displays to stderr the state of the current thread's
	// autorelease pool stack.

+ (void)resetTotalAutoreleasedObjects;
+ (unsigned)totalAutoreleasedObjects;
	// Returns the number of objects autoreleased (in ALL threads,
	// currently) since the counter was last reset to zero with
	// +resetTotalAutoreleasedObjects.

+ (void)enableFreedObjectCheck:(BOOL)enable;
	// Enables or disables freed-object checking for the pool stack
	// of the current thread (and any future pools in that thread).
	// When enabled, an autorelease pool will call the function
	// _NSAutoreleaseFreedObject() when it is about to attempt to
	// release an object that the runtime has marked as freed (and
	// then it doesn't attempt to send -release to the freed storage).
	// The pointer to the freed storage is passed to that function.
	// The "default default" value can be set in the initial
	// environment when a program is launched with the
	// NSAutoreleaseFreedObjectCheckEnabled environment variable
	// (see notes at the top of this file) -- as thread pool-stacks
	// are created, they take their initial freed-object-check state
	// from that environment variable.

+ (unsigned int)autoreleasedObjectCount;
	// Returns the total number of autoreleased objects in all pools
	// in the current thread's pool stack.

+ (unsigned int)topAutoreleasePoolCount;
	// Returns the number of autoreleased objects in top pool of
	// the current thread's pool stack.

+ (unsigned int)poolCountHighWaterMark;
+ (void)setPoolCountHighWaterMark:(unsigned int)count;
	// Sets the pool count high water mark for the pool stack of
	// the current thread (and any future pools in that thread). When
	// 'count' objects have accumulated in the top autorelease pool,
	// the pool will call _NSAutoreleaseHighWaterLog(), which
	// generates a message to stderr. The number of objects in the
	// top pool is passed as the parameter to that function. The
	// default high water mark is 0, which disables pool count
	// monitoring. The "default default" value can be set in the
	// initial environment when a program is launched with the
	// NSAutoreleaseHighWaterMark environment variable (see notes at
	// the top of this file) -- as thread pool-stacks are created,
	// they take their initial high water mark value from that
	// environment variable. See also +setPoolCountHighWaterResolution:.

+ (unsigned int)poolCountHighWaterResolution;
+ (void)setPoolCountHighWaterResolution:(unsigned int)res;
	// Sets the pool count high water resolution for the pool stack of
	// the current thread (and any future pools in that thread). A
	// call to _NSAutoreleaseHighWaterLog() is generated every multiple
	// of 'res' objects above the high water mark. If 'res' is zero
	// (the default), only one call to _NSAutoreleaseHighWaterLog() is
	// made, when the high water mark is reached. The "default default"
	// value can be set in the initial environment when a program is
	// launched with the NSAutoreleaseHighWaterResolution environment
	// variable (see notes at the top of this file) -- as thread
	// pool-stacks are created, they take their initial high water
	// resolution value from that environment variable. See also
	// +setPoolCountHighWaterMark:.


// Obsolete API.  Use the methods above instead.
+ (void)enableDoubleReleaseCheck:(BOOL)enable;
	// Use +enableFreedObjectCheck:
+ (void)showPoolsWithObjectIdenticalTo:(id)object;
	// Use +showPools
+ (void)setPoolCountThreshold:(unsigned)count;
	// Equivalent to:
	//	[NSAutoreleasePool setPoolCountHighWaterMark:count];
	//	[NSAutoreleasePool setPoolCountHighWaterResolution:count];

@end

/****************	Statistics-keeping	****************/

// The statistics-keeping facilities generate output on various
// types of events. Currently, output logs can be generated for
// use of the zone allocation functions (NSZoneMalloc(), etc.),
// allocation and deallocation of objects (and other types of
// lifetime-related events), and for use of the notification
// facilities (NSNotificationCenter). Currently, also, the output
// generated is in a columnar ASCII form, to make it most
// convenient to use command-line data processing utilities,
// like 'awk', 'grep', 'sed', or 'perl'.

// The boolean enabling variables can be set in a program, perhaps
// "around" a section of code that is of interest, and the values
// can also be given a non-default initial state by placing special
// environment variables into a process's initial environment (see
// notes at the top of this file). The names of those environment
// variables are the same as the names of the enabling variables.

// The destination of the output can be controlled somewhat by
// setting the values of the "FD" variables below, either at runtime
// or in the environment, as described above.

FOUNDATION_EXPORT BOOL NSKeepNotificationStatistics;
	// Default is NO.  NOTE:  There is no documentation on the
	// format of the notification statistics output at this time
	// (but the format is similar to that of the zone and
	// allocation statistics output).

FOUNDATION_EXPORT int NSNotificationStatisticsFD;
	// Number of open file descriptor to which output will be
	// written, currently using write(). By default, a file
	// called "note_stats_<name>_<pid>" (where <name> is the
	// process name and <pid> is the process id) is created in
	// the platform's temporary directory when first needed.
	// If this variable is set to -1, no output is generated.

FOUNDATION_EXPORT unsigned int NSNotificationStatisticsOutputVersion;
	// Not currently used.


FOUNDATION_EXPORT BOOL NSKeepZoneStatistics;
	// Default is NO.

FOUNDATION_EXPORT int NSZoneStatisticsFD;
	// Number of open file descriptor to which output will be
	// written, currently using write(). By default, a file
	// called "zone_stats_<name>_<pid>" (where <name> is the
	// process name and <pid> is the process id) is created in
	// the platform's temporary directory when first needed.
	// If this variable is set to -1, no output is generated.

#if !defined(STRICT_41) && !defined(STRICT_40)

FOUNDATION_EXPORT unsigned int NSZoneStatisticsOutputVersion;
	// Specifies the output format version. The default is 16.
	// Other valid values are 18 and 0.  Version 18 has the
	// same format as version 16, except that a numeric
	// "backtrace" of the return instruction pointers is
	// appended to every output line (see detailed format
	// description below for more information). Version 0
	// specifies the obsolete 4.0/4.1 output version. Note
	// that NSZoneStatisticsOutputMask is not used by
	// version 0.

FOUNDATION_EXPORT unsigned short NSZoneStatisticsOutputMask;
	// Bit-mask specifying zone events to log.  See the
	// defines below. The default value is 0xFFFF.

#endif


FOUNDATION_EXPORT BOOL NSKeepAllocationStatistics;
	// Default is NO.

FOUNDATION_EXPORT int NSAllocationStatisticsFD;
	// Number of open file descriptor to which output will be
	// written, currently using write(). By default, a file
	// called "alloc_stats_<name>_<pid>" (where <name> is the
	// process name and <pid> is the process id) is created in
	// the platform's temporary directory when first needed.
	// If this variable is set to -1, no output is generated.

#if !defined(STRICT_41) && !defined(STRICT_40)

FOUNDATION_EXPORT unsigned int NSAllocationStatisticsOutputVersion;
	// Specifies the output format version. The default is 16.
	// Other valid values are 18 and 0.  Version 18 has the
	// same format as version 16, except that a numeric
	// "backtrace" of the return instruction pointers is
	// appended to every output line (see detailed format
	// description below for more information). Version 0
	// specifies the obsolete 4.0/4.1 output version. Note
	// that NSAllocationStatisticsOutputMask is not used by
	// version 0.

FOUNDATION_EXPORT unsigned short NSAllocationStatisticsOutputMask;
	// Bit-mask specifying zone events to log.  See the
	// defines below. The default value is 0xFFFF.

#endif

#define NSZoneMallocEventMask			(1 << 0)
#define NSZoneCallocEventMask			(1 << 1)
#define NSZoneReallocEventMask			(1 << 2)
#define NSZoneFreeEventMask			(1 << 3)
#define NSVMAllocateEventMask			(1 << 4)
#define NSVMDeallocateEventMask			(1 << 5)
#define NSVMCopyEventMask			(1 << 6)
#define NSZoneCreatedEventMask			(1 << 7)
#define NSZoneRecycledEventMask			(1 << 8)

#define NSObjectAllocatedEventMask		(1 << 0)
#define NSObjectDeallocatedEventMask		(1 << 1)
#define NSObjectCopiedEventMask			(1 << 2)
#define NSObjectAutoreleasedEventMask		(1 << 3)
#define NSObjectExtraRefIncrementedEventMask	(1 << 4)
#define NSObjectExtraRefDecrementedEventMask	(1 << 5)
#define NSObjectInternalRefIncrementedEventMask	(1 << 6)
#define NSObjectInternalRefDecrementedEventMask	(1 << 7)
#define NSObjectPoolDeallocStartedEventMask	(1 << 8)
#define NSObjectPoolDeallocFinishedEventMask	(1 << 9)


/* The format of the zone and object allocation statistics output

The output format of versions 16 and 18 of the zone and object allocation
recording facility is given by:

    TIME EVENT ZONE PTR SIZE NEWPTR|RC|DSTPTR|GRAN CLASS|CANFREE [ @ RETPCS... ]

Each column in the output is separated by whitespace.  The first 7
columns are always present in the output (but may not be meaninngful).
The columns are:
    TIME    The time in seconds since the reference date for NSDate
            (2001-01-01 00:00:00 GMT), as a floating point number.
            This number is negative for dates before the reference date.

    EVENT   One of the following strings (the associated mask for the output
            mask variables, described above, is given in parenthesis):
	For object allocation events:
            OALLOC	Object allocated (NSObjectAllocatedEventMask)
            OFREE	Object deallocated (NSObjectDeallocatedEventMask)
            OCOPY	Object copied with NSCopyObject() (NSObjectCopiedEventMask)
            OAUTO	Object autoreleased (NSObjectAutoreleasedEventMask)
            OREF+	Object external ref. count ++ (NSObjectExtraRefIncrementedEventMask)
            OREF-	Object external ref. count -- (NSObjectExtraRefDecrementedEventMask)
            OIREF+	Object internal ref. count ++ (NSObjectInternalRefIncrementedEventMask)
            OIREF-	Object internal ref. count -- (NSObjectInternalRefDecrementedEventMask)
            AFREE_START	NSAutoreleasePool dealloc start (NSObjectPoolDeallocStartedEventMask)
            AFREE_END	NSAutoreleasePool dealloc end (NSObjectPoolDeallocFinishedEventMask)
	For zone events:
            ZMALLOC	Call to NSZoneMalloc() (NSZoneMallocEventMask)
            ZCALLOC	Call to NSZoneCalloc() (NSZoneCallocEventMask)
            ZREALLOC	Call to NSZoneRealloc() (NSZoneReallocEventMask)
            ZFREE	Call to NSZoneFree() (NSZoneFreeEventMask)
            VMALLOC	Call to NSAllocateMemoryPages() (NSVMAllocateEventMask)
            VMFREE	Call to NSDeallocateMemoryPages() (NSVMDeallocateEventMask)
            VMCOPY	Call to NSCopyMemoryPages() (NSVMCopyEventMask)
            ZCREATE	Call to NSCreateZone() (NSZoneCreatedEventMask)
            ZRECYCLE	Call to NSRecycleZone() (NSZoneRecycledEventMask)

    ZONE    The zone of the operation as a hex number for the zone events;
	    "0" for the VMALLOC, VMFREE, and VMCOPY events. The zone as a
	    hex number of the object for object allocation events.

    PTR     The pointer of the operation as a hex number for zone events. The
	    pointer to the object as a hex number for object allocation events.

    SIZE    The size of the memory (bytes) in the operation as a decimal
	    number. This field is valid for the OALLOC, OCOPY, ZMALLOC,
	    ZCALLOC, ZREALLOC, VMALLOC, VMFREE, VMCOPY, and ZCREATE events;
	    it is "0" for all other events.

	    For the OALLOC and OCOPY events, it is the total size of the object
	    allocated (including the extra bytes requested); for the ZMALLOC
	    and ZCALLOC events, it is the size of the block allocated; for the
	    ZREALLOC event, it is the new size of the block; for the VMALLOC,
	    VMFREE, and VMCOPY events, this field is the number of bytes; and
	    for the ZCREATE events it is the starting size of the zone.

    NEWPTR|RC|DSTPTR|GRAN
	    Miscellaneous field. For OCOPY and ZREALLOC, this is the new
	    pointer; for OREF+ and OIREF+ events, this is the (external,
	    internal) reference count of the object after incrementing;
	    for OREF- and OIREF- events, this is the (external, internal)
	    reference count of the object before decrementing; for VMCOPY,
	    the destination pointer; and for ZCREATE, it is the granularity
	    of the zone. For all other events, this field is "0".

    CLASS|CANFREE
	    For object allocation events, this is the class name of the object
	    the event is about. For the ZCREATE event, it is "YES" or "NO",
	    describing whether or not the zone frees memory. For all other zone
	    events, and for the AFREE_START and AFREE_END events, it is
	    "-".

Output version 18 adds a return address backtrace at the end of each line:

    @ RETPCS...
	    A literal "@" appears in the eigth column followed by the return
	    address backtrace, giving the return addresses (as hexidecimal
	    numbers) on the procedure call stack, the most recent frame on
	    the left. The last value in this list is "0".

Not all classes implement an internal reference count, and not all of those
that do emit OIREF+ and OIREF- events.  Note also that NeXT's frameworks do
not exclusively use the zone routines to allocate and free memory, although
the Foundation does (except at the lowest level where the zone routines may
be implemented in terms of the system's malloc package on some platforms).

Note: Output format version 0 is undocumented.

*/

/****************	Retain count monitoring		****************/

FOUNDATION_EXPORT BOOL NSNegativeRetainCheckEnabled;

FOUNDATION_EXPORT void _NSNegativeRetain(void *object, int virtual_retains);
	// Called when an object being autoreleased or released is
	// about to have less than zero virtual retains. The virtual
	// retain count is the number of real retains on the object
	// minus the number of times the object occurs in all autorelease
	// pools in all threads. This check is enabled by setting the
	// environment variable "NSNegativeRetainCheckEnabled" as
	// explained above, or by setting NSNegativeRetainCheckEnabled
	// flag to YES. This uses the allocation statistics facility
	// described above, and so requires NSKeepAllocationStatistics
	// to be YES. If the output of the allocation statistics
	// facility is not desired, set NSAllocationStatisticsFD to -1,
	// either via the environment or in the debugger or code. Note
	// that this facility does not indicate which autorelease or
	// release of the object is extraneous; it is not necessarily
	// the one which makes the virtual retain count negative, nor
	// one that occurs while the virtual retain count is negative.
	// Note also that an extraneous release may cause an object to
	// be deallocated without its virtual retain count becoming
	// negative.

#endif /* !STRICT_OPENSTEP */
