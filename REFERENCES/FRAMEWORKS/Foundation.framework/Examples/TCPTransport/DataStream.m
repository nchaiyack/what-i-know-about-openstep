/* DataStream.m created by blaine on Wed 03-Apr-1996 */

#import "DataStream.h"


@implementation DataStream

- init {
    array = [[NSMutableArray alloc] init];
    return self;
}

- (void)dealloc {
    [array release];
    [super dealloc];
}

- (void)appendData:(NSData *)item {
    if (!item) {
	NSLog(@"***no data item to append!!!!");
    	return;
    }
    [array addObject:item];
    length += [item length];
    //NSLog(@"appended %u bytes, length now %u", [item length], length);
}

- (unsigned int)length {
    return length;
}

- (BOOL)getBytes:(void *)bytes length:(unsigned)len {
    //NSLog(@"getting %u bytes, length %u", len, length);
    if (len > length) return NO;
    while (len) {
    	NSData *first = [array objectAtIndex:0];
	unsigned firstLen = [first length];
	unsigned available = firstLen - offset;
	
	if (available < len) {
	    memmove(bytes, (void *)[first bytes] + offset, available);
	    offset = 0;
	    [array removeObjectAtIndex:0];
	    bytes += available;
	    length -= available;
	    len -= available;
	}
	else {
	    memmove(bytes, (void *)[first bytes] + offset, len);
	    length -= len;
	    offset += len;
	    len -= len;
	    if (offset == firstLen) {
		offset = 0;
		[array removeObjectAtIndex:0];
	    }
	}
    }
    return YES;
}

- (void)fillData:(NSMutableData *)data length:(unsigned)len {

    //NSLog(@"filling %u bytes, length %u", len, length);
    if (len > length)
        [NSException raise:NSInvalidArgumentException format:@"asking for too much data"];
    while (len) {
        NSData *first = [array objectAtIndex:0];
        unsigned firstLen = [first length];
        unsigned available = firstLen - offset;

        if (available > len)
            available = len;
        [data appendBytes:[first bytes] + offset length:available];
        len -= available;
        offset += available;
        length -= available;
        if (offset >= firstLen) {
            [array removeObjectAtIndex:0];
            offset = 0;
        }
    }
}

@end
	    
