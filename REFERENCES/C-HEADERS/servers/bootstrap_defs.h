/*
 * bootstrap -- fundamental service initiator and port server
 * Mike DeMoney, NeXT, Inc.
 * Copyright, 1990.  All rights reserved.
 *
 * bootstrap_defs.h -- bootstrap service data types and constants
 * See bootstrap.defs for description of bootstrap services.
 */

#ifndef _BOOTSTRAP_DEFS_
#define	_BOOTSTRAP_DEFS_
#import <mach/mach.h>

#define	BOOTSTRAP_MAX_NAME_LEN			128
#define	BOOTSTRAP_MAX_CMD_LEN			512

typedef char name_t[BOOTSTRAP_MAX_NAME_LEN];
typedef char cmd_t[BOOTSTRAP_MAX_CMD_LEN];
typedef name_t *name_array_t;
typedef boolean_t *bool_array_t;

#define	BOOTSTRAP_MAX_LOOKUP_COUNT		20

#define	BOOTSTRAP_SUCCESS				0
#define	BOOTSTRAP_NOT_PRIVILEGED			1100
#define	BOOTSTRAP_NAME_IN_USE				1101
#define	BOOTSTRAP_UNKNOWN_SERVICE			1102
#define	BOOTSTRAP_SERVICE_ACTIVE			1103
#define	BOOTSTRAP_BAD_COUNT				1104
#define	BOOTSTRAP_NO_MEMORY				1105

/*
 * Compatibility, this gets subsumed by bootstrap_subset().
 */
extern kern_return_t bootstrap_get_unpriv_port(
	port_t	bootstrap_port,
	port_t	*unpriv_port);
#endif _BOOTSTRAP_DEFS_
