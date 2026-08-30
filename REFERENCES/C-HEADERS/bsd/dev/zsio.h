/* Copyright (c) 1992 NeXT Computer, Inc.  All rights reserved.
 *
 *	Serial port ioctl definitions.
 */

#import	<sys/ioctl.h>


/*
 * Modem signals: for use with TIOCMGET, TIOCMBIS, TIOCMBIC, and TIOCMSET
 */
#define	DML_DSR		0000400		/* data set ready, not a real DM bit */
#define	DML_RNG		0000200		/* ring */
#define	DML_CAR		0000100		/* carrier detect */
#define	DML_CTS		0000040		/* clear to send */
#define	DML_SR		0000020		/* secondary receive */
#define	DML_ST		0000010		/* secondary transmit */
#define	DML_RTS		0000004		/* request to send */
#define	DML_DTR		0000002		/* data terminal ready */
#define	DML_LE		0000001		/* line enable */


/*
 * ioctl to change receiver silo delay
 */
#define	ZIOCTGET	_IOR('z', 0, int)	/* get silo delay */
#define	ZIOCTSET	_IOW('z', 1, int)	/* set silo delay */

/*
 * ioctl to get serial line features
 * (OR of supported features is returned)
 */
#define	ZIOCFGET	_IOR('z', 2, int)	/* get features */

#define	ZSFEATURE_HWFLOWCTRL	0x0001		/* CTS/RTS flow control */


