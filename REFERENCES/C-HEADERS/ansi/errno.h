/* Copyright (c) 1992 NeXT Computer, Inc. */

#ifndef _ANSI_ERRNO_H
#define _ANSI_ERRNO_H

#include <standards.h>
#include <sys/errno.h>

#if !defined(ASSEMBLER) || defined(__STRICT_ANSI__)
extern int errno;
#endif /* ASSEMBLER || __STRICT_ANSI__ */

#endif	/* _ANSI_ERRNO_H */
