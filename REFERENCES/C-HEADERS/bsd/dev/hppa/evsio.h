/* 	Copyright (c) 1992 NeXT Computer, Inc.  All rights reserved. 
 *
 * evsio.h - Get/Set parameter calls for Event Status Driver.
 *
 *	CAUTION: Developers should stick to the API exported in
 *		<drivers/event_status_driver.h> to guarantee
 *		binary compatability of their applications in future
 *		releases.
 *
 * HISTORY
 * 30 Jul 93    Frank Rowand
 *      Created. 
 */

// NOTES:
// * This module defines system specific additions to the get/set
//   parameter set defined in the machine independent evsio.h module.
// * At the moment, there are no extensions, so we don't have anything
//   in here except an import of that mi interface.


#ifndef _HPPA_DEV_EVSIO_
#define _HPPA_DEV_EVSIO_

#import <bsd/dev/evsio.h>

//
// Device/architecture specific controls, implemented within
// Event Sources follow.
//


#endif _HPPA_DEV_EVSIO_
