/*      Copyright (c) 1991 NeXT Computer, Inc.  All rights reserved. 
 *
 * scsiTypes.h - Exported API of SCSIController class.
 *
 * HISTORY
 * 14-Jun-95	Doug Mitchell at NeXT
 *	Added SCSI-3 support.
 * 11-Feb-91    Doug Mitchell at NeXT
 *      Created. 
 */
 
#import <objc/objc.h>
#import <driverkit/driverTypes.h>
#import <kernserv/clock_timer.h>
#import <bsd/dev/scsireg.h>

/*
 * Buffers aligned to IO_SCSI_DMA_ALIGNMENT (both start and end addresses) are
 * guaranteed to be legal.
 */
#define IO_SCSI_DMA_ALIGNMENT      64

/*
 * Argument to executeRequest:buffer:client method.
 */
typedef struct {

        /*** inputs ***/
        
        unsigned char		target;         /* SCSI target ID */
        unsigned char		lun;            /* logical unit */
        cdb_t			cdb;            /* command descriptor block - 
                                                 * one of four formats */
        BOOL			read;     	/* expected DMA direction 
						 * (YES if read) */
        int			maxTransfer;    /* maximum number of bytes to
                                                 * transfer */
        int			timeoutLength;  /* I/O timeout in seconds */
        unsigned		disconnect:1;   /* OK to disconnect */
	unsigned		cmdQueueDisable:1;
						/* disable command queueing */
	unsigned		syncDisable:1;	/* disable synchronous transfer
						 * negotiation */
	unsigned		ignoreChkcond:1;/* to disable issuing of chk.
						   cond. cmd  */
				
        unsigned		pad:24;	
	unsigned		cdbLength:4;	/* length of CDB in bytes
						 * (optional) */
           
        /*** outputs ***/
        
        sc_status_t		driverStatus;   /* driver status */
        unsigned char		scsiStatus;     /* SCSI status byte */
        int			bytesTransferred; /* actual number of bytes 
                                                 * transferred by DMA */
	ns_time_t		totalTime;	/* total execution time */
	ns_time_t		latentTime;	/* disconnect time */
	esense_reply_t	 	senseData;	/* extended sense if
						 * driverStatus = SR_IOST_CHKSV
						 */

} IOSCSIRequest;

/*
 * Argument to executeSCSI3Request:buffer:client method.
 */
typedef struct {

        /*** inputs ***/
        
        unsigned long long	target;         /* SCSI target ID */
        unsigned long long	lun;            /* logical unit */
        scsi3_cdb_t		cdb;            /* command descriptor block - 
                                                 * one of five formats */
        BOOL			read;     	/* expected DMA direction 
						 * (YES if read) */
        int			maxTransfer;    /* maximum number of bytes to
                                                 * transfer */
        int			timeoutLength;  /* I/O timeout in seconds */
        unsigned		disconnect:1;   /* OK to disconnect */
	unsigned		cmdQueueDisable:1;
						/* disable command queueing */
	unsigned		syncDisable:1;	/* disable synchronous transfer
						 * negotiation */
				
        unsigned		pad:25;
	unsigned		cdbLength:4;	/* length of CDB in bytes
						 * (optional) */
           
        /*** outputs ***/
        
        sc_status_t		driverStatus;   /* driver status */
        unsigned char		scsiStatus;     /* SCSI status byte */
        int			bytesTransferred; /* actual number of bytes 
                                                 * transferred by DMA */
	ns_time_t		totalTime;	/* total execution time */
	ns_time_t		latentTime;	/* disconnect time */
	esense_reply_t	 	senseData;	/* extended sense if
						 * driverStatus = SR_IOST_CHKSV
						 */
	unsigned char		pad2[4];

} IOSCSI3Request;


/*
 * Exported protocol for SCSIController object.
 */
@protocol IOSCSIControllerExported

/*
 * Attempt to reserve specified target and lun for calling device. Returns
 * non-zero if device already reserved.
 */
- (int)reserveTarget 		: (unsigned char)target
			    lun : (unsigned char)lun
		       forOwner : owner;

- (void)releaseTarget 		: (unsigned char)target
			    lun : (unsigned char)lun
		       forOwner : owner;

/*
 * SCSI-3 versions of same.
 */
- (int)reserveSCSI3Target	: (unsigned long long)target
			    lun : (unsigned long long)lun
		       forOwner : owner;

- (void)releaseSCSI3Target	: (unsigned long long)target
			    lun : (unsigned long long)lun
		       forOwner : owner;


/*
 * Returns the number of SCSI targets supported.
 * FIXME - should this return an unsigned long long?
 */
- (int)numberOfTargets;

/*
 * Standard I/O methods.
 *
 * executeRequest requires buffers aligned to IO_SCSI_DMA_ALIGNMENT.
 */
- (sc_status_t) executeRequest 	: (IOSCSIRequest *)scsiReq
			 buffer : (void *)buffer 	/* data destination */
		 	 client : (vm_task_t)client;
	
/*
 * SCSI-3 version, allows 64-bit target/lun and 16-byte CDB.
 */
- (sc_status_t) executeSCSI3Request : (IOSCSI3Request *)scsiReq
			     buffer : (void *)buffer 	/* data destination */
		 	     client : (vm_task_t)client;

- (sc_status_t) resetSCSIBus;			/* reset the bus */

/*
 * Convert an sc_status_t to an IOReturn.
 */
- (IOReturn)returnFromScStatus	: (sc_status_t)sc_status;

/*
 * Determine maximum DMA which can be peformed in a single call to 
 * executeRequest:buffer:client:.
 */
- (unsigned)maxTransfer;

/*
 * Return required DMA alignment for current architecture.
 */
- (void)getDMAAlignment		: (IODMAAlignment *)alignment;

/*
 * Allocate some well-aligned memory.
 * Usage:
 * 
 * void *freePtr;
 * void *alignedPtr;
 * unsigned freeCnt;
 * 
 * alignedPtr = [controllerId allocateBufferOfLength:someLength
 *			actualStart:&freePtr
 *			actualLength:&freeCnt];
 * ...
 * when done...
 *
 * IOFree(freePtr, freeCnt);
 */

- (void *)allocateBufferOfLength: (unsigned)length
	actualStart : (void **)actualStart
	actualLength : (unsigned *)actualLength;

@end

/*
 * Public IONamedValue arrays.
 */
extern IONamedValue IOScStatusStrings[];
extern IONamedValue IOSCSISenseStrings[];
extern IONamedValue IOSCSIOpcodeStrings[];

