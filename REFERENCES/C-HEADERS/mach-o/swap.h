#import <architecture/byte_order.h>
#import <mach-o/fat.h>
#import <mach-o/loader.h>
#import <mach-o/nlist.h>
#import <mach-o/reloc.h>
#import <bsd/ranlib.h>

extern void swap_fat_header(
    struct fat_header *fat_header,
    enum NXByteOrder target_byte_order);

extern void swap_fat_arch(
    struct fat_arch *fat_archs,
    unsigned long nfat_arch,
    enum NXByteOrder target_byte_order);

extern void swap_mach_header(
    struct mach_header *mh,
    enum NXByteOrder target_byte_order);

extern void swap_load_command(
    struct load_command *lc,
    enum NXByteOrder target_byte_order);

extern void swap_segment_command(
    struct segment_command *sg,
    enum NXByteOrder target_byte_order);

extern void swap_section(
    struct section *s,
    unsigned long nsects,
    enum NXByteOrder target_byte_order);

extern void swap_symtab_command(
    struct symtab_command *st,
    enum NXByteOrder target_byte_order);

#if 0
extern void swap_dysymtab_command(
    struct dysymtab_command *dyst,
    enum NXByteOrder target_byte_sex);
#endif  /* temp backoff the fix */

extern void swap_symseg_command(
    struct symseg_command *ss,
    enum NXByteOrder target_byte_order);

extern void swap_fvmlib_command(
    struct fvmlib_command *fl,
    enum NXByteOrder target_byte_order);

extern void swap_fvmfile_command(
    struct fvmfile_command *ff,
    enum NXByteOrder target_byte_order);

extern void swap_thread_command(
    struct thread_command *ut,
    enum NXByteOrder target_byte_order);

extern void swap_ident_command(
    struct ident_command *ident,
    enum NXByteOrder target_byte_order);

extern void swap_nlist(
    struct nlist *symbols,
    unsigned long nsymbols,
    enum NXByteOrder target_byte_order);

extern void swap_ranlib(
    struct ranlib *ranlibs,
    unsigned long nranlibs,
    enum NXByteOrder target_byte_order);

extern void swap_relocation_info(
    struct relocation_info *relocs,
    unsigned long nrelocs,
    enum NXByteOrder target_byte_order);
