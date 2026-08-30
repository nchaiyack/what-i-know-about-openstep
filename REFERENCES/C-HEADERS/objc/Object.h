/*
	Object.h
	Copyright 1988-1996 NeXT Software, Inc.
  
	DEFINED AS:	A common class
	HEADER FILES:	<objc/Object.h>

*/

#ifndef _OBJC_OBJECT_H_
#define _OBJC_OBJECT_H_

#import <objc/objc-class.h>
#import <objc/typedstream.h>
#import <objc/zone.h>

@class Protocol;

@interface Object
{
	Class isa;	/* A pointer to the instance's class structure */
}

/* Initializing classes and instances */

+ initialize;
- init;

/* Creating, copying, and freeing instances */

+ new;
+ free;
- free;
+ alloc;
- copy;
+ allocFromZone:(NXZone *)zone;
- copyFromZone:(NXZone *)zone;
- (NXZone *)zone;

/* Identifying classes */

+ class;
+ superclass;
+ (const char *) name;
- class;
- superclass;
- (const char *) name;

/* Identifying and comparing instances */

- self;
- (unsigned int) hash;
- (BOOL) isEqual:anObject;

/* Testing inheritance relationships */

- (BOOL) isKindOf: aClassObject;
- (BOOL) isMemberOf: aClassObject;
- (BOOL) isKindOfClassNamed: (const char *)aClassName;
- (BOOL) isMemberOfClassNamed: (const char *)aClassName;

/* Testing class functionality */

+ (BOOL) instancesRespondTo:(SEL)aSelector;
- (BOOL) respondsTo:(SEL)aSelector;

/* Testing protocol conformance */

- (BOOL) conformsTo: (Protocol *)aProtocolObject;
+ (BOOL) conformsTo: (Protocol *)aProtocolObject;

/* Obtaining method descriptors from protocols */

- (struct objc_method_description *) descriptionForMethod:(SEL)aSel;
+ (struct objc_method_description *) descriptionForInstanceMethod:(SEL)aSel;

/* Obtaining method handles */

- (IMP) methodFor:(SEL)aSelector;
+ (IMP) instanceMethodFor:(SEL)aSelector;

/* Sending messages determined at run time */

- perform:(SEL)aSelector;
- perform:(SEL)aSelector with:anObject;
- perform:(SEL)aSelector with:object1 with:object2;

/* Posing */

+ poseAs: aClassObject;

/* Enforcing intentions */
 
- subclassResponsibility:(SEL)aSelector;
- notImplemented:(SEL)aSelector;

/* Error handling */

- doesNotRecognize:(SEL)aSelector;
- error:(const char *)aString, ...;

/* Debugging */

- (void) printForDebugger:(NXStream *)stream;

/* Archiving */

- awake;
- write:(NXTypedStream *)stream;
- read:(NXTypedStream *)stream;
+ (int) version;
+ setVersion: (int) aVersion;

/* Forwarding */

- forward: (SEL)sel : (marg_list)args;
- performv: (SEL)sel : (marg_list)args;

@end

/* Abstract Protocol for Archiving */

@interface Object (Archiving)

- startArchiving: (NXTypedStream *)stream;
- finishUnarchiving;

@end

/* Abstract Protocol for Dynamic Loading */

#if !defined(NeXT_PDO)
@interface Object (DynamicLoading)

//+ finishLoading:(headerType *)header;
+ finishLoading:(struct mach_header *)header;
+ startUnloading;

@end
#endif

OBJC_EXPORT id object_dispose(Object *anObject);
OBJC_EXPORT id object_copy(Object *anObject, unsigned nBytes);
OBJC_EXPORT id object_copyFromZone(Object *anObject, unsigned nBytes, NXZone *);
OBJC_EXPORT id object_realloc(Object *anObject, unsigned nBytes);
OBJC_EXPORT id object_reallocFromZone(Object *anObject, unsigned nBytes, NXZone *);

#endif /* _OBJC_OBJECT_H_ */
