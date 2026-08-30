/*
    Storage.h
    Copyright 1988-1996 NeXT Software, Inc.

    DEFINED AS:	A common class
    HEADER FILES:	objc/Storage.h
*/

#ifndef _OBJC_STORAGE_H_
#define _OBJC_STORAGE_H_

#import <objc/Object.h>
#import <objc/typedstream.h>

@interface Storage : Object
{
@public
    void	*dataPtr;	/* Data of the Storage object */
    const char	*description;	/* Encoded data type of the stored elements */
    unsigned	numElements;	/* Number of elements actually in the array */
    unsigned	maxElements;	/* Total allocated elements */
    unsigned	elementSize;	/* Size of each element in the array */
}

/* Creating, freeing, initializing, and emptying */

- init;
- initCount:(unsigned)count elementSize:(unsigned)sizeInBytes 
	description:(const char *)descriptor;
- free; 
- empty;
- copyFromZone:(NXZone *)zone;
  
/* Manipulating the elements */

- (BOOL)isEqual: anObject;
- (const char *)description; 
- (unsigned)count; 
- (void *)elementAt:(unsigned)index; 
- replaceElementAt:(unsigned)index with:(void *)anElement;
- setNumSlots:(unsigned)numSlots; 
- setAvailableCapacity:(unsigned)numSlots;
- addElement:(void *)anElement; 
- removeLastElement; 
- insertElement:(void *)anElement at:(unsigned)index; 
- removeElementAt:(unsigned)index; 

/* Archiving */

- write:(NXTypedStream *)stream;
- read:(NXTypedStream *)stream;

/*
 * The following new... methods are now obsolete.  They remain in this 
 * interface file for backward compatibility only.  Use Object's alloc method 
 * and the init... methods defined in this class instead.
 */

+ new; 
+ newCount:(unsigned)count elementSize:(unsigned)sizeInBytes 
	description:(const char *)descriptor; 

@end

typedef struct {
    @defs(Storage)
} NXStorageId;

#endif /* _OBJC_STORAGE_H_ */
