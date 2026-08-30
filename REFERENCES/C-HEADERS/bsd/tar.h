/* Copyright 1993 NeXT Computer, Inc - WMG */

#ifndef _TAR_H
#define _TAR_H

#include <standards.h>

#ifdef _POSIX_SOURCE

	#define TMAGIC		"ustar"	/* ustar and a null */
	#define TMAGLEN		6		  
	#define TVERSION	"00"	/* 00 and no null */
	#define TVERSLEN	2

	/* Values used in typeflag field */
	#define REGTYPE		'0'	/* regular file */
	#define AREGTYPE	'\0'	/* regular file */
	#define LNKTYPE		'1'	/* line         */
	#define SYMTYPE		'2'	/* reserved     */
	#define CHRTYPE		'3'	/* character special */
	#define BLKTYPE 	'4'	/* block special */
	#define DIRTYPE		'5'	/* directory */
	#define FIFOTYPE	'6'	/* FIFO special */
	#define CONTTYPE	'7'	/* reserved */

	/* Bits used in the mode field - values in octal */
	#define TSUID		04000	/* set UID on execution */
	#define TSGID		02000	/* set GID on execution */
	#define TSVTX		01000	/* reserved 	   	*/
	#define TUREAD		00400	/* read by owner	*/
	#define TUWRITE		00200	/* write by owner	*/
	#define TUEXEC		00100	/* execute/search by owner */
	#define TGREAD		00040	/* read by group 	*/
	#define TGWRITE		00020	/* write by group 	*/
	#define TGEXEC		00010	/* execute/search by group */
	#define TOREAD		00004	/* read by other 	*/
	#define TOWRITE		00002	/* write by other 	*/
	#define	TOEXEC		00001	/* execute/search by other */
#endif /* _POSIX_SOURCE */

#endif /* _H_TAR */
