/*
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)gmon.h	5.1 (Berkeley) 5/30/85
 */

/*
 * Histogram counters are unsigned shorts (according to the kernel).
 */
#define	HISTCOUNTER	unsigned short

/*
 * Fraction of text space to allocate for histogram counters here, 1/2
 */
#define	HISTFRACTION	2

/*
 * Fraction of text space to allocate for from hash buckets.
 * The value of HASHFRACTION is based on the minimum number of bytes
 * of separation between two subroutine call points in the object code.
 * Given MIN_SUBR_SEPARATION bytes of separation the value of
 * HASHFRACTION is calculated as:
 *
 * 	HASHFRACTION = MIN_SUBR_SEPARATION / (2 * sizeof(short) - 1);
 *
 * For the VAX,
 *	the shortest two call sequence is:
 * 		calls	$0,(r0)
 *		calls	$0,(r0)
 * 	which is separated by only three bytes, thus HASHFRACTION is 
 *	calculated as:
 *		HASHFRACTION = 3 / (2 * 2 - 1) = 1
 *
 * For the m68k,
 *	the shortest two call sequence is:
 * 		jsr	a0
 *		jsr	a0
 * 	which is separated by only four bytes, thus HASHFRACTION is 
 *	calculated as:
 *		HASHFRACTION = 4 / (2 * 2 - 1) = 1
 *
 * For all RISC machines
 *	the shortest two call sequence is 2 32-bit instructions,
 * 	which is separated by only four bytes, thus HASHFRACTION is 
 *	calculated as:
 *		HASHFRACTION = 4 / (2 * 2 - 1) = 1
 *
 * For the i386,
 *	the shortest two call sequence is:
 * 		call	%eax
 *		call	%eax
 * 	which is separated by only two bytes, thus HASHFRACTION is 
 *	calculated as:
 *		HASHFRACTION = 2 / (2 * 2 - 1) = 0
 *	So on the i386 we use a HASHFRACTION of 1 instead and it can fail
 *	to determine that two call sites are different.  But since all
 *	the call site address in gprof(1) is currently used for is
 *	to determine which routine was doing the calling it works for now.
 *
 * Note that the division above rounds down, thus if MIN_SUBR_FRACTION
 * is less than three, this algorithm will not work!
 */
#define	HASHFRACTION	1

/*
 * percent of text space to allocate for tostructs with a minimum.
 */
#define ARCDENSITY	4
#define MINARCS		50

#ifndef ASSEMBLER
/*
 * The tostruct is used internal to the monitor library routines to implement
 * the recording of calls via mcount().
 */
struct tostruct {
    char		*selfpc;
    long		count;
    unsigned short	link;
    unsigned short	order;
};

/*
 * The phdr (profile header) structure is what appears at the beginning of a
 * mon.out (cc(1) -p) and gmon.out (cc(1) -pg) file and describes the histogram
 * counters.  The histogram counters are unsigned shorts which follow after the
 * header for ncnt - sizeof(struct phdr) bytes.
 */
struct phdr {
    char	*lpc; 	/* low program counter */
    char	*hpc; 	/* high program counter */
    int		ncnt;	/* number of bytes of histogram counters minius
			   sizeof(struct phdr) that follow */
};

/*
 * In a gmon.out (cc(1) -pg) file what follows the above histogram counters are
 * the raw arcs.  A raw arc contains pointers to the calling site, the called
 * site and a count.  These repeat in the gmon.out file after the histogram
 * counters to the end of the file.
 */
struct rawarc {
    unsigned long	raw_frompc;
    unsigned long	raw_selfpc;
    unsigned long	raw_count;
};

/*
 * In order to support more information than in the original mon.out and
 * gmon.out files there is an alternate gmon.out file format.  The alternate
 * gmon.out file format starts with a magic number then separates the
 * information with gmon_data structs.
 */
#define GMON_MAGIC 0xbeefbabe
struct gmon_data {
    unsigned long type; /* constant for type of data following this struct */
    unsigned long size; /* size in bytes of the data following this struct */
};

/*
 * The GMONTYPE_SAMPLES gmon_data.type is for the histogram counters described
 * above and has a struct phdr followed by the counters.
 */
#define GMONTYPE_SAMPLES	1
/*
 * The GMONTYPE_RAWARCS gmon_data.type is for the raw arcs described above.
 */
#define GMONTYPE_RAWARCS	2
/*
 * The GMONTYPE_ARCS_ORDERS gmon_data.type is for the raw arcs with a call
 * order field.  The order is the order is a sequence number for the order each
 * call site was executed.  Raw_order values start at 1 not zero.  Other than
 * the raw_order field this is the same information as in the struct rawarc.
 */
#define GMONTYPE_ARCS_ORDERS	3
struct rawarc_order {
    unsigned long	raw_frompc;
    unsigned long	raw_selfpc;
    unsigned long	raw_count;
    unsigned long	raw_order;
};
/*
 * The GMONTYPE_RLD_STATE gmon_data.type is for the rld_load()'ed state of the
 * program.
 * The informations starts with an unsigned long with the count of states:
 *	rld_nloaded_states
 * Then each state follows in the file.  The state is made up of 
 *	header_addr (where rld loaded this set of objects)
 *	nobjectfiles (the number of objects in this set)
 *		offsets into the string table (one for each object in the set)
 *	nbytes of string table
 *		the file name strings null terminated.
 */
#define GMONTYPE_RLD_STATE	4
/*
 * The GMONTYPE_DYLD_STATE gmon_data.type is for the dynamic link editor state
 * of the program.
 * The informations starts with an unsigned long with the count of states:
 *      image_count
 * Then each state follows in the file.  The state is made up of 
 *      image_header (the address where dyld loaded this image)
 *      vmaddr_slide (the amount dyld slid this image from it's vmaddress)
 *      name (the file name dyld loaded this image from)
 */
#define GMONTYPE_DYLD_STATE     5
#endif !ASSEMBLER

/*
 * general rounding functions.
 */
#define ROUNDDOWN(x,y)	(((x)/(y))*(y))
#define ROUNDUP(x,y)	((((x)+(y)-1)/(y))*(y))
