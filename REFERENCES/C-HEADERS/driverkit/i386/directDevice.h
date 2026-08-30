/*
 * Copyright (c) 1993 NeXT Computer, Inc.
 *
 * ISA/EISA direct device interface.
 *
 * HISTORY
 *
 * 10Jan93 Brian Pinkerton at NeXT
 *	Created.
 *
 */
#import <driverkit/IODirectDevice.h>
#import <driverkit/i386/IOEISADeviceDescription.h>
#import <driverkit/i386/driverTypes.h>


@interface IODirectDevice(IOEISADirectDevice)


/*
 * Determine whether localChannel's DMA is complete.
 */
- (BOOL) isDMADone:(unsigned int) localChannel;

/*
 *  Methods to reserve and enable DMA channels.  Also, methods to obtain
 *  buffers for DMA, and do DMA using those buffers.
 */
- (IOReturn) enableChannel	: (unsigned int) localChannel;
- (void) disableChannel		: (unsigned int) localChannel;

/*
 * Specify basic DMA transfer mode.
 */
typedef enum {
	IO_Demand,
	IO_Single,
	IO_Block,
	IO_Cascade,
} IODMATransferMode;

- (IOReturn) setTransferMode	: (IODMATransferMode) mode 
		     forChannel : (unsigned int) localChannel;

/*
 * Enable/disable autoinitialize DMA mode. Default is 
 * disabled.
 */
- (IOReturn)setAutoinitialize  	: (BOOL)flag
                    forChannel 	: (unsigned)localChannel;

/*
 * Set DMA address increment/decrement mode.
 * Default is IO_Increment.
 */
typedef enum {
	IO_Increment,
	IO_Decrement,
} IOIncrementMode;

- (IOReturn)setIncrementMode   	: (IOIncrementMode)mode
                    forChannel 	: (unsigned)localChannel;

/*
 *  Returns a DMA buffer for the contents of physical memory starting at
 *  addr and continuing for length bytes.  If the physical address changed
 *  to accommodate the ISA bus, the new physical address is returned in
 *  place.  The IOEISADMABuffer is an opaque type.
 */
- (IOEISADMABuffer) createDMABufferFor:(unsigned int *) physAddr
			 length	: (unsigned int) length
			   read : (BOOL) isRead
		 needsLowMemory : (BOOL) lowerMem
		      limitSize : (BOOL) limitSize;

/*
 *  Complete DMA on, and free, the given DMABuffer.  If the DMA was a read,
 *  and the buffer relocated the original physical memory, then the relocated
 *  memory is copied to the source in this step.
 */
- (void) freeDMABuffer		: (IOEISADMABuffer) buffer;

/*
 *  Like -freeDMABuffer, except it doesn't copy the memory.
 */
- (void) abortDMABuffer		: (IOEISADMABuffer) buffer;

/*
 *  Perform host-master DMA using the given DMABuffer on the given DMA channel.
 */
- (IOReturn) startDMAForBuffer	: (IOEISADMABuffer) buffer
			channel : (unsigned int) localChannel;

/*
 * Return localChannel's current address and count.
 */
- (unsigned)currentAddressForChannel : (unsigned)localChannel; 
- (unsigned)currentCountForChannel   : (unsigned)localChannel;

/*
 *  Methods to reserve resources.  You don't normally need to call these, as
 *  they're called automatically when IOEISADirectDevice is initialized with
 *  the -initFromDeviceDescription method.
 */
- (IOReturn) reservePortRange	: (unsigned int) localPortRange;
- (void) releasePortRange	: (unsigned int) localPortRange;

- (IOReturn) reserveInterrupt	: (unsigned int)localInterrupt;
- (void) releaseInterrupt	: (unsigned int) localInterrupt;

- (IOReturn) reserveChannel	: (unsigned int) localChannel;
- (void) releaseChannel		: (unsigned int) localChannel;

/*
 * Reserve and release exclusive DMA lock. Use is optional; provides
 * exclusion between mutually incompatible DMA devices.
 */
- (void)reserveDMALock;
- (void)releaseDMALock;

/*
 * Determine whether or not the associated device is connected to an EISA 
 * bus. Returns YES if so, else returns NO.
 */
- (BOOL)isEISAPresent;

/*
 * Get the EISA id for the specified slot.
 * Returns YES if slot is valid, else returns NO.
 */
- (BOOL)getEISAId: (unsigned int *) _id  forSlot: (int) slot;

/*
 * Support for the extended mode register (EISA only).
 */

/*
 * Select transfer width. Default is IO_8Bit.
 */
typedef enum {
	IO_8Bit,			// 8  bit I/O, count by bytes
	IO_16BitWordCount,		// 16 bit I/O, count by words
					//   (not currently supported)
	IO_16BitByteCount,		// 16 bit I/O, count by bytes
	IO_32Bit,			// 32 bit I/O, count by bytes
} IOEISADMATransferWidth;


- (IOReturn)setDMATransferWidth	: (IOEISADMATransferWidth)width
                     forChannel : (unsigned)localChannel;
- (IOReturn)getDMATransferWidth	: (IOEISADMATransferWidth *)width_p
                     forChannel : (unsigned)localChannel;

/*
 * Select DMA Timing. Default is IO_Compatible. 
 */
typedef enum {
	IO_Compatible,	
	IO_TypeA,
	IO_TypeB,
	IO_Burst,	
} IOEISADMATiming;

- (IOReturn)setDMATiming	: (IOEISADMATiming)timing
                     forChannel : (unsigned)localChannel;

/*
 * Select whether EOP pin is output (default) or input.
 */
- (IOReturn)setEOPAsOutput	: (BOOL)flag
                     forChannel	: (unsigned)localChannel;

/*
 * Enable Stop register. Default is disabled.
 */
typedef enum {
	IO_StopRegisterEnable,
	IO_StopRegisterDisable,
} IOEISAStopRegisterMode;

- (IOReturn)setStopRegisterMode : (IOEISAStopRegisterMode)mode
                    forChannel 	: (unsigned)localChannel;

@end
