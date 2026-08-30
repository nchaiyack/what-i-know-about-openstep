/*
 *	objc-runtime.h
 *	Copyright 1988-1996, NeXT Software, Inc.
 */

#ifndef _OBJC_RUNTIME_H_
#define _OBJC_RUNTIME_H_

#import <objc/objc.h>
#import <objc/objc-class.h>
#import <objc/hashtable2.h>
#import <objc/Object.h>

typedef struct objc_symtab *Symtab;

struct objc_symtab {
	unsigned long 	sel_ref_cnt;
	SEL 		*refs;		
	unsigned short 	cls_def_cnt;
	unsigned short 	cat_def_cnt;
#ifdef NeXT_PDO
	arith_t        obj_defs;
	arith_t        proto_defs;
#endif
	void  		*defs[1];	/* variable size */
};

typedef struct objc_module *Module;

struct objc_module {
	unsigned long	version;
	unsigned long	size;
	const char	*name;
	Symtab 		symtab;	
};

struct objc_super {
	id receiver;
#ifdef __cplusplus
	Class theClass;
#else
	Class class;
#endif
};

/* kernel operations */

OBJC_EXPORT id objc_getClass(const char *name);
OBJC_EXPORT id objc_getMetaClass(const char *name);
OBJC_EXPORT id objc_msgSend(id self, SEL op, ...);
OBJC_EXPORT id objc_msgSendSuper(struct objc_super *super, SEL op, ...);

/* forwarding operations */

OBJC_EXPORT id objc_msgSendv(id self, SEL op, unsigned arg_size, marg_list arg_frame);

/* 
   iterating over all the classes in the application...
  
   NXHashTable *class_hash = objc_getClasses();
   NXHashState state = NXInitHashState(class_hash);
   Class class;
  
   while (NXNextHashState(class_hash, &state, &class)
     ...;
 */
OBJC_EXPORT NXHashTable *objc_getClasses(void);
OBJC_EXPORT Module *objc_getModules(void);
OBJC_EXPORT id objc_lookUpClass(const char *name);
OBJC_EXPORT void objc_addClass(Class myClass);

/* customizing the error handling for objc_getClass/objc_getMetaClass */

OBJC_EXPORT void objc_setClassHandler(int (*)(const char *));

/* Making the Objective-C runtime thread safe. */
OBJC_EXPORT void objc_setMultithreaded (BOOL flag);

/* overriding the default object allocation and error handling routines */

OBJC_EXPORT id	(*_alloc)(Class, unsigned int);
OBJC_EXPORT id	(*_copy)(Object *, unsigned int);
OBJC_EXPORT id	(*_realloc)(Object *, unsigned int);
OBJC_EXPORT id	(*_dealloc)(Object *);
OBJC_EXPORT id	(*_zoneAlloc)(Class, unsigned int, NXZone *);
OBJC_EXPORT id	(*_zoneRealloc)(Object *, unsigned int, NXZone *);
OBJC_EXPORT id	(*_zoneCopy)(Object *, unsigned int, NXZone *);

#if defined(NeXT_PDO)
    OBJC_EXPORT void   (*_error)();
#else
    OBJC_EXPORT void	(*_error)(Object *, const char *, va_list);
#endif

#if defined(WIN32)
/* This seems like a strange place to put this, but there's really
   no very appropriate place! */
OBJC_EXPORT const char* NSRootDirectory(void);
#endif 

#endif /* _OBJC_RUNTIME_H_ */
