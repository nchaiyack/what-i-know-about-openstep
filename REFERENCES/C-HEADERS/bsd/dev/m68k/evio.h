/******************************************************************************

    evio.h
    Ioctl calls for the events driver
    Leovitch 02Jan88
    
    Copyright 1988 NeXT, Inc.
    
    Modified:
    
    09Dec88 Leo  Broken out from evsio.h
    24Aug89 Ted  ANSI function prototyping.
    19Feb90 Ted  Major revision for multiple driver support.
    26Feb90 Ted  New evioScreen structure and EVIOST ioctl.
    12Mar90 Ted  New ev_unregister_screen function, SCREENTOKEN constant.
    06May90 Ted  Added AALastEventSent and AALastEventConsumed to EvVars.
    22May90 Trey More wait cursor vars in EvVars.
    13Jun90 Ted  NXCursorData structure.
    18Jun90 Ted  Default wait cursor constants.
    26Sep90 Ted  Enhanced cursor system to support intelligent drivers.
    26Nov90 Ted  Removed NXSaveCursor and NXCursorData structures
    28Nov90 Ted  Remove EvVars, rolled into EventGlobals
    28Nov90 Ted  Renamed EventGlobals -> EvGlobals, eventGlobals -> evg

******************************************************************************/

#ifndef _M68K_DEV_EVIO_
#define _M68K_DEV_EVIO_

#import <sys/ioctl.h>
#import <mach/port.h>
#import <mach/message.h>
#import <bsd/dev/ev_types.h>
#import <bsd/dev/m68k/event.h>

/* Default Wait Cursor Contants (in 68Hz ticks) */
#define DefaultWCSustain 20	/* 0.3 seconds */	
#define DefaultWCFrameRate 5	/* 13.6 frames/second */
#define DefaultWCThreshold 80	/* 1.2 seconds */

/* Pressure Constants */
#define MINPRESSURE 0
#define MAXPRESSURE 255

/* Mouse Button Constants  */
#define RB		(0x01)
#define LB		(0x04)
#define MOUSEBUTTONMASK	(LB | RB)

#ifndef MAXMOUSESCALINGS
/* Maximum length of SetMouseScaling arrays */
#define MAXMOUSESCALINGS NX_MAXMOUSESCALINGS
#endif MAXMOUSESCALINGS

#define SCREENTOKEN 256	/* Some non-zero token to or with screen number */
#define	LLEQSIZE 80	/* Entries in low-level event queue */

typedef struct _NXEQElStruct {
    short next;		/* Slot of lleq for next event */
    short sema;		/* Is high-level code is reading this event now? */
    NXEvent event;	/* The event itself */
} NXEQElement;

/* The following typedefs are defined here for compatibility with PostScript */

#if !defined(__Point__) && !defined(BINTREE_H)
#define __Point__
typedef struct { short x, y; } Point;
#endif

#if !defined(__Bounds__) && !defined(BINTREE_H)
#define __Bounds__
typedef struct { short minx, maxx, miny, maxy; } Bounds;
#endif

typedef struct _evRetry {
    unsigned level:1;
    unsigned cursor:2;
    unsigned :29;
} EvRetry;

/******************************************************************************
    EvScreen
    This structure is used both by the ev driver and screen drivers.
    It holds information about a single screen: how much private shmem it owns,
    where its private shmem region starts, its global bounds and four procedure
    vectors. This structure is allocated by the ev driver and is filled in
    when a driver calls ev_register_screen(). This structure is correspondingly
    passed to each procedure vector as the first argument to allow a driver to
    know which screen the call refers to (in the case a driver controls more
    than one screen for instance).

    The priv field is the only field a driver is permitted to modify at any
    given time.  Every other field is off limits.  This structure may grow
    in length, but the field order will not change.

    The procedure vectors allow the kernel to direct cursor activity and
    delegate responsibility for drawing, erasing, and moving the cursor to
    screen drivers. (See video.c for the MegaPixel driver's implementation).
    Each procedure must return an error status.  Returning "0" means that
    a procedure successfully processed the given message.  Returning "1"
    signifies that it wasn't successful in processing the message and should
    be retried at a later time. This should releave most error conditions that
    might arrive and prevents drivers from (god for bin) having to spin within
    time-critical interrupt periods. Usually a retry is requested if a driver's
    cursor semaphore or lock is busy. 
******************************************************************************/

typedef volatile struct _evScreen {
    void *priv;		/* Driver's private use */
    void *shmemPtr;	/* Ptr to private shmem (if non-zero size) */
    int shmemSize;	/* Size of private shmem */
    Bounds bounds;	/* Screen's bounds in device coordinates */
    EvRetry retry;	/* private to ev driver */
    int (*hide)(struct _evScreen *esp);
    int (*move)(struct _evScreen *esp, Point loc, int frame);
    int (*show)(struct _evScreen *esp, Point loc, int frame);
    int (*level)(struct _evScreen *esp, int brightness);
} EvScreen;

/******************************************************************************
    SHARED MEMORY OVERVIEW
    
    PERSPECTIVE
    The ev driver and PostScript share at least one page of wired memory.
    This memory contains the low-level event queue which ev deposits events
    into and PostScript reads events from. Also, this memory contains other
    important data such as wait cursor state and some general cursor state.
    This memory is critical for speed.  That is, we avoid having to make
    system calls for common operations.
    
    SHARED MEMORY REGIONS
    There are currently three "regions" or "zones" delineated within this
    shared memory.  The first zone is the EvOffsets structure. This structure
    contains two offsets from the beginning of shared memory. The first offset
    is to the second zone, EvGlobals. The second offset is to the third
    zone, private shmem for drivers.
    
    INITIALIZATION OF SHARED MEMORY
    When the WindowServer starts up, it finds all screens that will be active.
    It then opens the ev driver and calls the EVIOSSCR ioctl repeatedly for
    each screen in use. This lets the ev driver set up the evScreen array
    and fill in each element. This ioctl also returns to PostScript a running
    total shared memory size with which to allocate. PostScript then allocates
    a region of memory this size and calls evmmap to "map in" this shared
    region.  Evmmap initializes and fills in the EvOffsets and EvGlobals.
    Next the WindowServer calls each screen in turn to register itself with
    the ev driver in the same sequence as presented to EVIOSSCR.  Each screen
    driver calls ev_register_screen() which among other things allocates a
    part of the private shmem (of the third shared memory zone) for the driver.
    
    DEBUGGING NOTES
    You can easily display and set this shared memory from kgdb, but usually
    cannot do so from within PostScript.  Gdb (or some weird interaction
    between gdb and the os) chokes on this shmem.  So if you read or write
    this area of memory, copy-on-write will occur and you'll get a completely
    new page for PostScript.  This will render the shared memory scheme
    useless and you will have to restart PostScript.  It was my understanding
    that before, we were able to "read" this area from PS, but not write to
    it (the idea behind copy-on-WRITE).  However, this seems to be broken
    in 2.0.  We think this is a kernel bug.
******************************************************************************/

typedef volatile struct _evOffsets {
    int	evGlobalsOffset;	/* Offset to EvGlobals structure */
    int evShmemOffset;		/* Offset to private shmem regions */
} EvOffsets;

/******************************************************************************
    EvGlobals
    This structures defines the portion of the events driver data structure
    that is exported to the PostScript server. It contains the event queue
    which is in memory shared between the driver and the PostScript server.
    All the variables necessary to read and process events from the queue are
    contained here.
******************************************************************************/

typedef volatile struct _evGlobals {
    short LLEHead;		/* The next event to be read */
    short LLETail;		/* Where the next event will go */
    short LLELast;		/* The last event entered */
    short eNum;			/* Unique id for mouse events */
    int buttons;		/* State of the mouse buttons 1==down, 0==up */
    int eventFlags;		/* The current value of event.flags */
    int VertRetraceClock;	/* The current value of event.time */
    int cursorSema; 		/* set to disable interrupt code */
    Point cursorLoc;		/* The current location of the cursor */
    int frame;			/* current cursor frame */
    Bounds workBounds;		/* bounding box of all screens */
    Bounds mouseRect;		/* Rect for mouse-exited events */
    unsigned reserved:27;
    unsigned wantPressure:1;	/* pressure in current mouseRect? */
    unsigned wantPrecision:1;	/* precise coordinates in current mouseRect? */
    unsigned dontWantCoalesce:1;/* coalesce within the current mouseRect? */
    unsigned dontCoalesce:1;	/* actual flag which determines coalescing */
    unsigned mouseRectValid:1;	/* If nonzero, post a mouse-exited
				   whenever mouse outside mouseRect. */
    int movedMask;		/* This contains an event mask for the
				   three events MOUSEMOVED,
				   LMOUSEDRAGGED,  and RMOUSEDRAGGED.
				   It says whether driver should
				   generate those events. */
    int AALastEventSent;	/* timestamp for wait cursor */
    int AALastEventConsumed;	/* timestamp for wait cursor */	
    int waitCursorUp;		/* Is wait cursor up? */
    char ctxtTimedOut;		/* Has wait cursor timer expired? */
    char waitCursorEnabled;	/* Play wait cursor game (per ctxt)? */
    char globalWaitCursorEnabled; /* Play wait cursor game (global)? */
    char waitCursorSema;	/* protects wait cursor fields */
    short waitThreshold;	/* time before wait cursor appears */
    NXEQElement lleq[LLEQSIZE];	/* The event queue itself */
} EvGlobals;

/* These evio structs are used in various ioctls supported by the ev driver. */

struct evioLLEvent {
    int type;
    Point location;
    NXEventData data;
};

/* This structure is used privately by the WindowServer */
struct evioSetScreen {
    int totalShmemSize;		/* out: returned size of shmem to allocate */
    int totalScreens;		/* in:  number of screens in the screen list */
    int screenIndex;		/* in:  this screen (0..totalScreens) */
    int screenShmemSize;	/* in:  this screen's desired shmem size */
    Bounds screenBounds;	/* in:  this screen's global bounds */
};

/* General ioctls */

#define EVIOSEP	  _IOW('e', 1, port_t)		   /* Set event port */
#define EVIOLLPE  _IOW('e', 2, struct evioLLEvent) /* Low-level Post Event */
#define EVIOMM	  _IOR('e', 3, void)		   /* mini_mon (gone) */
#define EVIOSSCR  _IOWR('e', 4, struct evioSetScreen) /* set up screens */

/* Mouse-related ioctls */

#define EVIOSD	  _IOWR('e', 66, int)		   /* StillDown */
#define	EVIORSD	  _IOWR('e', 67, int)		   /* RightStillDown */
#define	EVIOSM	  _IOW('e', 68, Point)		   /* SetMouse */
#define	EVIOCM	  _IOR('e', 69, Point)		   /* CurrentMouse */
#define EVIOST    _IO('e', 70)			   /* StartCursor */

#endif _M68K_DEV_EVIO_
