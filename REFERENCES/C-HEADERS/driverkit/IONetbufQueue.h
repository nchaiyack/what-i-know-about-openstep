/*
 * Copyright (c) 1993 NeXT Computer, Inc.
 *
 * Class which implements a fifo queue of Netbufs.
 *
 * HISTORY
 *
 * 2 Feb 1993 David E. Bohman at NeXT
 *	Created.
 */

#ifdef	KERNEL

#import <objc/Object.h>
#import <bsd/net/netbuf.h>

/*
 * A request to enqueue a Netbuf
 * when there are already maxCount
 * Netbufs queued, causes the new
 * Netbuf to be freed without notice.
 *
 * Freeing an IONetbufQueue instance
 * causes any queued Netbufs to be freed.
 */
@interface IONetbufQueue:Object
{
@private
    struct _queueEntry {
	struct _queueEntry
				*_next;
    }		*_queueHead,
    		*_queueTail;
    unsigned	_queueCount;
    unsigned	_maxCount;
}

- initWithMaxCount:(unsigned)maxCount;

- (unsigned)count;		// returns number of Netbufs queued

- (unsigned)maxCount;

- (void)enqueue:(netbuf_t)nb;

- (netbuf_t)dequeue;

@end

#endif	KERNEL
