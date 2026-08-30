/*
 * Copyright 1994 NeXT Computer, Inc.
 * All rights reserved.
 */

#import <objc/Object.h>
#import <driverkit/driverTypes.h>

@interface IOPCMCIATuple : Object
{
@private
        void		*_private;
}

- (unsigned char) code;
- (unsigned) length;
- (unsigned char *) data;

@end