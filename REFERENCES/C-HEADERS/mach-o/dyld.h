#import "mach-o/loader.h"
#import <streams/streams.h>

#ifndef ENUM_BOOL
#define ENUM_BOOL
#undef FALSE
#undef TRUE
enum bool {
    FALSE,
    TRUE
};
#endif /* ENUM_BOOL */

/*
 * The high level NS... API.
 */

/* Object file image api */
typedef enum {
    NSObjectFileImageFailure, /* for this a message is printed on stderr */
    NSObjectFileImageSuccess,
    NSObjectFileImageInappropriateFile,
    NSObjectFileImageArch,
    NSObjectFileImageFormat, /* for this a message is printed on stderr */
    NSObjectFileImageAccess,
} NSObjectFileImageReturnCode;

typedef void * NSObjectFileImage;

/* limited implementation, only MH_BUNDLE files can be used */
extern NSObjectFileImageReturnCode NSCreateObjectFileImageFromFile(
    const char *pathName,
    NSObjectFileImage *objectFileImage);
/* not yet implemented */
extern NSObjectFileImageReturnCode NSCreateObjectFileImageFromMemory(
    void *address,
    unsigned long size, 
    NSObjectFileImage *objectFileImage);
/* not yet implemented */
extern enum bool NSDestroyObjectFileImage(
    NSObjectFileImage objectFileImage);
/*
 * Need api on NSObjectFileImage's for:
 *   "for Each Symbol Definition In Object File Image" (for Dynamic Bundles)
 *   Could have the same thing for references
 */
/* not yet implemented */
extern unsigned long NSSymbolDefinitionCountInObjectFileImage(
    NSObjectFileImage objectFileImage);
/* not yet implemented */
extern const char * NSSymbolDefinitionNameInObjectFileImage(
    NSObjectFileImage objectFileImage,
    unsigned long ordinal);
/* not yet implemented */
extern unsigned long NSSymbolReferenceCountInObjectFileImage(
    NSObjectFileImage objectFileImage);
/* not yet implemented */
extern const char * NSSymbolReferenceNameInObjectFileImage(
    NSObjectFileImage objectFileImage,
    unsigned long ordinal,
    enum bool *tentative_definition); /* can be NULL */
/*
 * Other needed api on NSObjectFileImage:
 *   "does Object File Image define symbol name X" (using sorted symbol table)
 *   a way to get the named objective-C section
 */
/* not yet implemented */
extern enum bool NSIsSymbolDefinedInObjectFileImage(
    NSObjectFileImage objectFileImage,
    const char *symbolName);
/* not yet implemented */
extern void * NSGetSectionDataInObjectFileImage(
    NSObjectFileImage objectFileImage,
    const char *segmentName,
    const char *sectionName);

/* module api */
typedef void * NSModule;
extern const char * NSNameOfModule(
    NSModule m); 
extern const char * NSLibraryNameForModule(
    NSModule m);

/* limited implementation, only MH_BUNDLE files can be linked */
extern NSModule NSLinkModule(
    NSObjectFileImage objectFileImage, 
    const char *moduleName, /* can be NULL */
    enum bool bindNow);
/* not yet implemented */
extern enum bool NSUnLinkModule(
    NSModule module, 
    enum bool keepMemoryMapped); 
/* not yet implemented */
extern NSModule NSReplaceModule(
    NSModule moduleToReplace,
    NSObjectFileImage newObjectFileImage, 
    enum bool keepMemoryMapped,
    enum bool preserveFunctionAddresses); 

/* symbol api */
typedef void * NSSymbol;
extern enum bool NSIsSymbolNameDefined(
    const char *symbolName);
extern NSSymbol NSLookupAndBindSymbol(
    const char *symbolName);
extern const char * NSNameOfSymbol(
    NSSymbol symbol);
extern void * NSAddressOfSymbol(
    NSSymbol symbol);
extern NSModule NSModuleForSymbol(
    NSSymbol symbol);

/* error handling api */
typedef enum {
    NSLinkEditFileAccessError,
    NSLinkEditFileFormatError,
    NSLinkEditMachResourceError,
    NSLinkEditUnixResourceError,
    NSLinkEditOtherError,
    NSLinkEditWarningError
} NSLinkEditErrors;

typedef struct {
     void     (*undefined)(const char *symbolName);
     NSModule (*multiple)(NSSymbol s, NSModule old, NSModule new_); 
     void     (*linkEdit)(NSLinkEditErrors c, int errorNumber,
                          const char *fileName, const char *errorString);
} NSLinkEditErrorHandlers;

extern void NSInstallLinkEditErrorHandlers(
    NSLinkEditErrorHandlers *handlers);

/* other api */
extern enum bool NSAddLibrary(
    const char *pathName);
extern long NSVersionOfRunTimeLibrary(
    const char *libraryName);
extern long NSVersionOfLinkTimeLibrary(
    const char *libraryName);

/*
 * The low level _dyld_... API.
 * (used by the objective-C runtime primarily)
 */
extern unsigned long _dyld_present(
    void);

extern unsigned long _dyld_image_count(
    void);
extern struct mach_header * _dyld_get_image_header(
    unsigned long image_index);
extern unsigned long _dyld_get_image_vmaddr_slide(
    unsigned long image_index);
extern char * _dyld_get_image_name(
    unsigned long image_index);

extern void _dyld_register_func_for_add_image(
    void (*func)(struct mach_header *mh, unsigned long vmaddr_slide));
extern void _dyld_register_func_for_link_module(
    void (*func)(NSModule module));
/* not yet implemented */
extern void _dyld_register_func_for_unlink_module(
    void (*func)(NSModule module));
/* not yet implemented */
extern void _dyld_register_func_for_replace_module(
    void (*func)(NSModule oldmodule, NSModule newmodule));
extern void _dyld_get_objc_module_sect_for_module(
    NSModule module,
    void **objc_module,
    unsigned long *size);
extern void _dyld_bind_objc_module(
    void *objc_module);
extern enum bool _dyld_bind_fully_image_containing_address(
    unsigned long *address);

extern void _dyld_moninit(
    void (*monaddition)(char *lowpc, char *highpc));
extern enum bool _dyld_launched_prebound(
    void);

extern void _dyld_lookup_and_bind(
    const char *symbol_name,
    unsigned long *address,
    void **module);
extern void _dyld_lookup_and_bind_objc(
    const char *symbol_name,
    unsigned long *address,
    void **module);
extern void _dyld_lookup_and_bind_fully(
    const char *symbol_name,
    unsigned long *address,
    void **module);

__private_extern__ int _dyld_func_lookup(
    const char *dyld_func_name,
    unsigned long *address);
