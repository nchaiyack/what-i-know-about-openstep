/*
 *	Stream implementation data structure definitions.
 *
 *	These definitions are not necessary if you only want to use
 *	the streams package. You will need these definitions if you 
 *	implement a stream.
 *
 */
 
#import "streams.h"
#import <objc/zone.h>
#if defined(WIN32)
#import <objc/objc-api.h>
#endif
#if !defined(NEXTPDO)
#define NEXTPDO extern
#endif

#ifndef STREAMS_IMPL_H
#define STREAMS_IMPL_H

#define NX_DEFAULTBUFSIZE	(16 * 1024)

/*
 *	Procedure declarations used in implementing streams.
 */

NEXTPDO NXStream *NXStreamCreate(int mode, int createBuf);
NEXTPDO NXStream *NXStreamCreateFromZone(int mode, int createBuf, NXZone *zone);
NEXTPDO void NXStreamDestroy(NXStream *stream);
NEXTPDO void NXChangeBuffer(NXStream *stream);
NEXTPDO int NXFill(NXStream *stream);
    /* NXFill should only be called when the buffer is empty */
    
NEXTPDO int NXDefaultWrite(NXStream *stream, const void *buf, int count);
NEXTPDO int NXDefaultRead(NXStream *stream, void *buf, int count);

#endif


