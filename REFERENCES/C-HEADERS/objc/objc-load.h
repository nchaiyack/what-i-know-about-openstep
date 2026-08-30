/*
 *	objc-load.h
 *	Copyright 1988-1996, NeXT Software, Inc.
 */

#ifndef _OBJC_LOAD_H_
#define _OBJC_LOAD_H_

#if !defined(NeXT_PDO)
#import <objc/objc-class.h>
#import <streams/streams.h>
#import <mach-o/loader.h>

/* dynamically loading Mach-O object files that contain Objective-C code */

OBJC_EXPORT long objc_loadModules (
	char *modlist[], 
	NXStream *errStream,
	void (*class_callback) (Class, Category),
	/*headerType*/ struct mach_header **hdr_addr,
	char *debug_file
);
OBJC_EXPORT long objc_unloadModules(
	NXStream *errorStream,				/* input (optional) */
	void (*unloadCallback)(Class, Category)		/* input (optional) */
);

OBJC_EXPORT void objc_register_header_name(
	char *name					/* input */
);

OBJC_EXPORT void objc_register_header(
	char *name					/* input */
);

#endif NeXT_PDO
#endif /* _OBJC_LOAD_H_ */
