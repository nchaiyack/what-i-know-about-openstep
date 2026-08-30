/*	NXPropertyList.h
	Basic protocol for property lists
  	Copyright 1991-1996, NeXT Software, Inc.
	Bertrand, August 1991
*/

#import <objc/NXString.h>
#import <objc/hashtable2.h>
#import <objc/maptable.h>
#import <objc/List.h>
 
/********	The basic property list protocol		********/

@protocol NXPropertyList
- (unsigned)count;
- (BOOL)member:(NXString *)key;
- get:(NXString *)key;
    /* returns nil or value */
- insert:(NXString *)key value:value;
    /* returns nil or previous value; 
    caller is responsible for freing previous value */
- remove:(NXString *)key;
    /* returns nil or previous value; 
    caller is responsible for freing previous value */
- empty;
- (NXMapState)initEnumeration;
    /* To enumerate use something like:
	NXMapState	state = [self initEnumeration];
        NXString	*key;
	id		value;
	while ([self enumerate:&state key:&key value:&value]) {
		...
	}
    */
- (BOOL)enumerate:(NXMapState *)state key:(NXString **)refKey value:(id *)refValue;
    
@end

/********	A class implementing it		********/

@interface NXPropertyList:Object <NXPropertyList> {
    NXMapTable	*table;
}
@end

/********	Basic ASCII read/write of property lists	********/

@interface NXPropertyList (Basic_IO)
- initFromStream:(NXStream *)stream;
- initFromPath:(NXString *)path;
    /* all init methods must be called just after alloc; 
	they may return nil in case of inexistant file or syntax error;  
	Only syntax errors are logged on console */

- (void)writeToStream:(NXStream *)stream;
- (BOOL)writeToPath:(NXString *)path safely:(BOOL)safe;
    /* uses a temporary ~ file, and then atomically moves the file */
- (BOOL)writeToPath:(NXString *)path;
    /* All basic write function do indenting;
	BOOL returned indicates success */
    
@end

/********	A list that really frees its elements	********/

@interface NXCleanList:List
- free;
    /* sends free to each of its objects */
@end

/********	Fancy ASCII read/write of property lists	********/

typedef struct _NXPropertyListReadContext {
    unsigned	line; 		/* for error messages */
    NXMutableString *buffer;	/* for efficiency */
    id	keyFactory;		/* e.g. [NXCollectedString class] */
    id	stringValueFactory;	/* e.g. [NXReadOnlyString class] */
    id	listValueFactory;	/* e.g. [List class]; nil OK */
    id	propertyListValueFactory; /* e.g. [NXPropertyList class]; nil OK */
    BOOL	noValueIsSame;	/* if = missing, either key or nil */
    NXZone	*zone;		/* zone used for reading; may be NULL */
    NXHashTable	*uniquingTable;	/* used to unique strings */
} NXPropertyListReadContext;

typedef struct _NXPropertyListWriteContext {
    unsigned	indentDelta;		/* 0 => dont add white spaces */
    unsigned	indent;			/* current number of spaces */
    BOOL	topLevelBrackets;	/* the outer {} */
    const char	*pairSeparator;		/* after each pair (after the ';') */
    // not an NXString because bug cc!
} NXPropertyListWriteContext;

@protocol NXPropertyListFancyIO
- initFromStream:(NXStream *)stream context:(NXPropertyListReadContext *)context;
- (void)writeToStream:(NXStream *)stream context:(NXPropertyListWriteContext *)context;
@end

@interface NXPropertyList (Fancy_IO)
- initFromStream:(NXStream *)stream context:(NXPropertyListReadContext *)context; //?? use protocol when possible in ObjC
- (void)writeToStream:(NXStream *)stream context:(NXPropertyListWriteContext *)context; //?? use protocol when possible in ObjC
- initFromPath:(NXString *)path context:(NXPropertyListReadContext *)context;
@end

@interface NXCleanList (Fancy_IO)
- initFromStream:(NXStream *)stream context:(NXPropertyListReadContext *)context; //?? use protocol when possible in ObjC
- (void)writeToStream:(NXStream *)stream context:(NXPropertyListWriteContext *)context; //?? use protocol when possible in ObjC
@end

@interface NXString (Fancy_IO)
- initFromStream:(NXStream *)stream context:(NXPropertyListReadContext *)context; //?? use protocol when possible in ObjC
- (void)writeToStream:(NXStream *)stream context:(NXPropertyListWriteContext *)context; //?? use protocol when possible in ObjC
@end

