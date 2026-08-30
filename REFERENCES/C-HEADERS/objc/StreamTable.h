/*
    StreamTable.h
    Copyright 1989-1996 NeXT Software, Inc.
    
    DEFINED AS:	A common class
    HEADER FILES:	objc/StreamTable.h

*/
 
#ifndef _OBJC_STREAMTABLE_H_
#define _OBJC_STREAMTABLE_H_

#import <objc/HashTable.h>

@interface StreamTable: HashTable 
	
/* Creating, freeing, and initializing */

- free;	
- freeObjects;	
- init;
- initKeyDesc:(const char *)aKeyDesc;

/* Manipulating */

- valueForStreamKey:(const void *)aKey;
- insertStreamKey:(const void *)aKey value:aValue;
- removeStreamKey:(const void *)aKey;

/* Iterating */

- (NXHashState)initStreamState;
- (BOOL)nextStreamState:(NXHashState *)aState key:(const void **)aKey 
	value:(id *)aValue;

/* Archiving */

- write:(NXTypedStream *)stream;
- read:(NXTypedStream *)stream;

/*
 * The following new... methods are now obsolete.  They remain in this 
 * interface file for backward compatibility only.  Use Object's alloc method 
 * and the init... methods defined in this class instead.
 */

+ new;
+ newKeyDesc:(const char *)aKeyDesc;

@end

#endif /* _OBJC_STREAMTABLE_H_ */
