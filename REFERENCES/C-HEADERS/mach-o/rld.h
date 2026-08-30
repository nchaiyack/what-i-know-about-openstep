/*
 * This is the interface to the rld package as described in rld(3).
 */

#ifndef _MACHO_RLD_H_
#define _MACHO_RLD_H_

#import <streams/streams.h>
#import <mach-o/loader.h>

extern long rld_load(
    NXStream *stream,
    struct mach_header **header_addr,
    const char * const *object_filenames,
    const char *output_filename);

extern long rld_load_from_memory(
    NXStream *stream,
    struct mach_header **header_addr,
    const char *object_name,
    char *object_addr,
    long object_size,
    const char *output_filename);

extern long rld_unload(
    NXStream *stream);

extern long rld_lookup(
    NXStream *stream,
    const char *symbol_name,
    unsigned long *value);

extern long rld_forget_symbol(
    NXStream *stream,
    const char *symbol_name);

extern long rld_unload_all(
    NXStream *stream,
    long deallocate_sets);

extern long rld_load_basefile(
    NXStream *stream,
    const char *base_filename);

extern void rld_address_func(
    unsigned long (*func)(unsigned long size, unsigned long headers_size));

#endif /* _MACHO_RLD_H_ */
