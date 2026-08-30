/*
 * Copyright (c) 1993 NeXT Computer, Inc.
 *
 * Functions that deal with information about architectures.
 *
 * HISTORY
 *
 * 4 February 1993 Lennart Lovstrand <lennart@next.com>
 *	Redesigned to use NXArchInfo based names and signatures.
 *
 * Originally written by Kevin Enderby at NeXT, Inc.
 *
 */

#import <mach/machine.h>
#import <architecture/byte_order.h>

/* The NXArchInfo structs contain the architectures symbolic name
 * (such as "m68k"), its CPU type and CPU subtype as defined in
 * mach/machine.h, the byte order for the architecture, and a
 * describing string (such as "Motorola 680x0").
 * There will both be entries for specific CPUs (such as 68040) as
 * well as generic "family" entries (such as 680x0).
 */
typedef struct {
    const char *name;
    cpu_type_t cputype;
    cpu_subtype_t cpusubtype;
    enum NXByteOrder byteorder;
    const char *description;
} NXArchInfo;

/* NXGetAllArchInfos() returns a pointer to an array of all known
 * NXArchInfo structures.  The last NXArchInfo is marked by a NULL name.
 */
extern const NXArchInfo *NXGetAllArchInfos(void);

/* NXGetLocalArchInfo() returns the NXArchInfo for the local host, or NULL
 * if none is known. 
 */
extern const NXArchInfo *NXGetLocalArchInfo(void);

/* NXGetArchInfoFromName() and NXGetArchInfoFromCpuType() return the
 * NXArchInfo from the architecture's name or cputype/cpusubtype
 * combination.  A cpusubtype of CPU_SUBTYPE_MULTIPLE can be used
 * to request the most general NXArchInfo known for the given cputype.
 * NULL is returned if no matching NXArchInfo can be found.
 */
extern const NXArchInfo *NXGetArchInfoFromName(const char *name);
extern const NXArchInfo *NXGetArchInfoFromCpuType(cpu_type_t cputype,
						  cpu_subtype_t cpusubtype);

/* NXFindBestFatArch() is passed a cputype and cpusubtype and a set of
 * fat_arch structs and selects the best one that matches (if any) and returns
 * a pointer to that fat_arch struct (or NULL).  The fat_arch structs must be
 * in the host byte order and correct such that the fat_archs really points to
 * enough memory for nfat_arch structs.  It is possible that this routine could
 * fail if new cputypes or cpusubtypes are added and an old version of this
 * routine is used.  But if there is an exact match between the cputype and
 * cpusubtype and one of the fat_arch structs this routine will always succeed.
 */
extern struct fat_arch *NXFindBestFatArch(cpu_type_t cputype,
					  cpu_subtype_t cpusubtype,
					  struct fat_arch *fat_archs,
					  unsigned long nfat_archs);

/* NXCombineCpuSubtypes() returns the resulting cpusubtype when combining two
 * different cpusubtypes for the specified cputype.  If the two cpusubtypes
 * can't be combined (the specific subtypes are mutually exclusive) -1 is
 * returned indicating it is an error to combine them.  This can also fail and
 * return -1 if new cputypes or cpusubtypes are added and an old version of
 * this routine is used.  But if the cpusubtypes are the same they can always
 * be combined and this routine will return the cpusubtype pass in.
 */
extern cpu_subtype_t NXCombineCpuSubtypes(cpu_type_t cputype,
					  cpu_subtype_t cpusubtype1,
					  cpu_subtype_t cpusubtype2);

