/*
** IODeviceInspector - Inspects IRQ, DMA, port addrs, and mem maps
**
** This object provides a default implementation of a device inspector.
** If the driver for which you need to write an inspector is sufficiently
** strange, you may write a completely new inspector.  Only the methods
** in the IOConfigurationInspector protocol need be implemented.
**
** This inspector handles the arbitration of IRQ levels, DMA channels, 
** and the various address ranges.  If you need to add more controls to 
** the inspector window, override the init method, load your supplemental
** nib file, and use the setAccessoryView: method to install it in the
** UI.
** 
** By default, this inspector determines the number of IRQ levels, DMA
** channels, etc. by examining the first table it is provided with.  To
** override this behavrio, override init, call [super init], 
** then [self setNumInterrupts...].
**
** To use this object with a different nib file, override loadMainNibFile.
**
** Copyright 1993 by NeXT Computer, Inc.  All Rights Reserved.
*/

#import <appkit/appkit.h>

#define	IO_FIRST_INTERRUPT		1
#define IO_NUM_INTERRUPTS		15
#define IO_FIRST_CHANNEL		0
#define IO_NUM_CHANNELS			8
#define IO_MAX_DEVICES			32
#define IO_MAX_RANGES_PER_DEVICE	16

#define IO_MAX_RANGES		(IO_MAX_DEVICES * IO_MAX_RANGES_PER_DEVICE)

#define IO_INTERRUPTS_KEY	"IRQ Levels"
#define IO_CHANNELS_KEY		"DMA Channels"
#define IO_PORT_RANGES_KEY	"I/O Ports"
#define IO_MEMORY_RANGES_KEY	"Memory Maps"
#define IO_VALID_INTERRUPTS_KEY	"Valid IRQ Levels"
#define IO_VALID_CHANNELS_KEY	"Valid DMA Channels"
#define IO_VERSION_KEY		"Version"

typedef enum { 
    IO_ConflictUnknown = 0, IO_NoConflict, IO_ConflictExists 
} IOConfigurationConflict;

typedef struct IOAddressRange
{
    unsigned	start;
    unsigned	length;
} IOAddressRange;
    
typedef struct IOResources
{
    BOOL		interrupts[IO_NUM_INTERRUPTS];
    BOOL		channels[IO_NUM_CHANNELS];
    unsigned		numPortRanges;
    IOAddressRange  	portRanges[IO_MAX_RANGES];
    unsigned		numMemoryRanges;
    IOAddressRange	memoryRanges[IO_MAX_RANGES];
} IOResources;

@protocol IOConfigurationInspector
- setTable:(NXStringTable *)instance;
- (View *) inspectionView;
- resourcesChanged:(IOResources *)rsrc;
@end

@interface IODeviceInspector:Object <IOConfigurationInspector>
{
    id	accessoryHolder;		/* View where we put accessory */
    id	statusTitle;			/* At top of window */
    id  origWindow;			/* For getting contentView */
    
    id  dmaBox;				/* In case no DMA channels */
    id	dmaMatrix;			/* Buttons for DMA channels */
    id  irqBox;				/* In case no IRQ levels */
    id	irqMatrix;			/* Buttons for IRQ levels */
    id	memoryBox;			/* In case no mapped memory */
    id	memoryController;		/* Handles ranges */
    id	portsBox;			/* In case no port addresses */
    id	portsController;		/* Handles ranges */
    
    id  inspectionView;			/* The inspection view */
    id  versionTitle;			/* Text for driver version */
    id  infoPanel;			/* Text about the device */
    id  infoText;			/* Text object for info file */
    	
    NXStringTable  *table;		/* Device we're editing */
    int		   numInterrupts;	/* How many IRQ's to configure */
    int		   numChannels;		/* How many DMA's to configure */
    int		   portRangeLength;	/* Port address size */
    int		   memoryRangeLength;	/* Memory map size */
    
    BOOL	   infoTextLoaded;	/* Info panel has been loaded */
    BOOL	   knowsDetails;	/* Knows device's requirements */
    
    /* Conflict status on last update, used to minimize redraws */
    
    IOConfigurationConflict	portConflict;	/* Had conflict w/portaddrs? */
    IOConfigurationConflict	memoryConflict;	/* Had conflict w/memmap? */
    IOConfigurationConflict	totalConflict;	/* Any conflicts at all? */
}

- setNumInterrupts:(int)nirq numChannels:(int)ndma portRangeLength:(int)nport 
    memoryRangeLength:(int)nmap;
- loadMainNibFile;
- setAccessoryView:aView;

- channelOrInterruptPicked:sender;
- showInfo:sender;

- rangeDidChange:sender;

@end
