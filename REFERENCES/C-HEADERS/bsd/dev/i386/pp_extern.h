/*	@(#)pp_extern.h	
 *
 * pp_extern.h -- Externally used data structures and constants for Parallel 
 *		Port driver
 *
 * KERNEL VERSION
 *
 * HISTORY
 * 03-Mar-93	Phillip Dibner and John Immordino at NeXT
 *	Created.
 *
 */

#ifndef	_PPEXTERN_
#define _PPEXTERN_

#import <sys/types.h>
#import <sys/ioctl.h>

/*
 * ioctl's specific to parallel port
 */

#define	PPIOCSW		_IOR('p',0,int)		/* status word */
#define PPIOCINIT	_IO('p',1)		/* initialize printer */
#define PPIOCSETTIMO	_IOW('p',2, int)	/* set timeout period (secs) */

/* No _IO('p',3) for now */

/*
 * Status word mask defines
 */
#define PP_ST_INITIALIZED	0x0001
#define PP_ST_BUSY		0x0002
#define PP_ST_NOPAPER		0x0004
#define PP_ST_NOTSELECTED	0x0008
#define PP_ST_TIMEOUT		0x0010
#define PP_ST_ERROR		0x0020		/* "Error" bit was set */

/*
 * Setting timeout to -1 causes the parallel port to wait indefinitely if
 * printer is offline or out of paper.
 */
#define PP_WAIT_FOREVER		-1

#ifdef DRIVER_PRIVATE

#define PPIOCGIHDELAY	_IOR('p',4,int)	/* get int handler delay (usec) */	
#define PPIOCSIHDELAY	_IOW('p',5,int)	/* set int handler delay (usec) */
#define PPIOCGIOTDELAY	_IOR('p',6,int)	/* get IOTask thread delay (usec) */		
#define PPIOCSIOTDELAY	_IOW('p',7,int)	/* set IOTask thread  delay (usec) */
#define PPIOCGMINPHYS	_IOR('p',8,int)	/* get max chunk size */	
#define PPIOCSMINPHYS	_IOW('p',9,int)	/* set max chunk size */
#define PPIOCGBSIZE	_IOR('p',10,int)	/* get block size */	
#define PPIOCSBSIZE	_IOW('p',11,int)	/* set block size */
#define PPIOCGRINTERVAL	_IOR('p',12,int)	/* get busy retry interval */	
#define PPIOCSRINTERVAL	_IOW('p',13,int)	/* set busy retry interval */
#define PPIOCGRETRIES	_IOR('p',14,int)	/* get max busy retries */	
#define PPIOCSRETRIES	_IOW('p',15,int)	/* set max busy retries */
#define PPIOCGSREG	_IOR('p',16,int)	/* get status register */
#define PPIOCGCREG	_IOR('p',17,int)	/* get control register */
#define PPIOCGCREGDEF	_IOR('p',18,int)	/* get ctl reg defaults */

#endif DRIVER_PRIVATE		
#endif	_PPEXTERN_

