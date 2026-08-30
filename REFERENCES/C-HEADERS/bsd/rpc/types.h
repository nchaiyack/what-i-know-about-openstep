/*	@(#)types.h	1.5 88/05/02 4.0NFSSRC SMI	*/

/* 
 * Copyright (c) 1988 by Sun Microsystems, Inc.
 *      @(#)types.h 1.20 88/02/08 SMI      
 */


/*
 * Rpc additions to <sys/types.h>
 */
#ifndef __TYPES_RPC_HEADER__
#define __TYPES_RPC_HEADER__

#define	bool_t	int
#define	enum_t	int
#define __dontcare__	-1

#ifndef FALSE
#	define	FALSE	(0)
#endif

#ifndef TRUE
#	define	TRUE	(1)
#endif

#ifndef NULL
#ifdef __STRICT_BSD__
#	define NULL 0
#else
#	define NULL ((void *)0)
#endif __STRICT_BSD__
#endif  NULL

#ifdef __STRICT_BSD__
extern char *malloc();
#else
#include <stdlib.h>
#endif __STRICT_BSD__
#define mem_alloc(bsize)	malloc(bsize)
#define mem_free(ptr, bsize)	free(ptr)

#include <sys/types.h>

#ifndef _TIME_
#include <sys/time.h>
#endif

#endif /* ndef __TYPES_RPC_HEADER__ */
