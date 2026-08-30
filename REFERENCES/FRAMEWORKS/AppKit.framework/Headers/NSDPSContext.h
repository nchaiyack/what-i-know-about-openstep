/*
    NSDPSContext.h

    A DPSContext Object
    Copyright (c) 1994-1996, NeXT Software, Inc.
    All rights reserved.
*/

#import <Foundation/Foundation.h>
#import <AppKit/dpsclient.h>
#import <AppKit/AppKitDefines.h>

/* NSRunLoop mode used when DPS is waiting for return vals or pings */
APPKIT_EXTERN NSString *NSDPSRunLoopMode;

@class NSDPSContext;

/* method used for asynchronous ping notification */
@protocol NSDPSContextNotification
- (void)contextFinishedExecuting:(NSDPSContext *)context;
@end

@interface NSDPSContext : NSObject {
  /* standard DPSContext fields */
    char *priv;
    DPSSpace space;
    DPSProgramEncoding programEncoding;
    DPSNameEncoding nameEncoding;
    struct _t_DPSProcsRec const *procs;
    void (*textProc)();
    void (*errorProc)();
    DPSResults resultTable;
    unsigned int resultTableLength;
    DPSContext chainParent, chainChild;

  /* the output data */
    NSMutableData *_outData;
  /* the output stream */
    void *_outStream;
    struct {
      /* length of curr seq % 4 */
	unsigned int BOSLengthMod4:8;
      /* Did we create the output stream?  If so, make sure we close it */
	unsigned int ownOutputStream:1;
      /* YES if the context draws to the screen (server context) */
	unsigned int drawingToScreen:1;
      /* makes trace output nicer for debugging */
	unsigned int debugging:1;
      /* ping after every wrap? */
	unsigned int syncMode:1;
      /* have we written since pinging? */
	unsigned int stuffToPing:1;
      /* have we written since flushing? */
	unsigned int stuffToFlush:1;
	unsigned int _PAD:18;
    } _ctxtFlags;
  /* amount of current binArray left */
    unsigned int _binArrayLeft;
  /* a chained context being used for tracing */
    NSDPSContext *_traceCtxt;
  /* state for converting binary object sequences to ascii */
    char *_asciiBuffer;
    char *_asciiBufCurr;
  /* a list of the offsets of any numstrings in the wrap */
    int *_numStrings;
    int _numNumStrings;
    unsigned int _reservedDPSContext;
}

+ (void)setAllContextsSynchronized:(BOOL)flag;
+ (BOOL)areAllContextsSynchronized;
+ (void)setAllContextsOutputTraced:(BOOL)flag;
+ (BOOL)areAllContextsOutputTraced;

+ (NSDPSContext *)currentContext;
+ (void)setCurrentContext:(NSDPSContext *)context;

+ (NSString *)stringForDPSError:(const DPSBinObjSeqRec *)error;

- initWithMutableData:(NSMutableData *)data forDebugging:(BOOL)debug languageEncoding:(DPSProgramEncoding)langEnc nameEncoding:(DPSNameEncoding)nameEnc textProc:(DPSTextProc)tProc errorProc:(DPSErrorProc)errorProc;
- (NSMutableData *)mutableData;

/* returns the corresponding DPSContext */
- (DPSContext)DPSContext;

/* drawing status */
- (BOOL)isDrawingToScreen;

/* methods for the standard DPS API */

/* methods used by pswrap generated functions to emit binary PS */
- (void)writeBinaryObjectSequence:(const void *)data length:(unsigned int)bytes;
- (void)writeBOSArray:(const void *)data count:(unsigned int)items ofType:(DPSDefinedType)type;
- (void)writeBOSString:(const void *)data length:(unsigned int)bytes;
- (void)writeBOSNumString:(const void *)data length:(unsigned int)count ofType:(DPSDefinedType)type scale:(int)scale;
- (void)awaitReturnValues;
- (void)updateNameMap;

/* methods to send raw data */
- (void)writeData:(NSData *)buf;
- (void)writePostScriptWithLanguageEncodingConversion:(NSData *)buf;
- (void)printFormat:(NSString *)format, ...;
- (void)printFormat:(NSString *)format arguments:(va_list)argList;

/* methods to control the context */
- (void)flush;
- (void)resetCommunication;
    /* only partially implemented in NEXTSTEP */
- (void)interruptExecution;
    /* not implemented in NEXTSTEP */
- (void)wait;
- (void)notifyObjectWhenFinishedExecuting:(id <NSDPSContextNotification>)object;

/* methods to control text and error procs */
- (void)setTextProc:(DPSTextProc)proc;
- (DPSTextProc)textProc;
- (void)setErrorProc:(DPSErrorProc)proc;
- (DPSErrorProc)errorProc;

/* setting and getting the chained context */
- (void)chainChildContext:(NSDPSContext *)child;
- (void)unchainContext;
- (NSDPSContext *)childContext;
- (NSDPSContext *)parentContext;

#ifndef STRICT_OPENSTEP
/* controling the wait cursor.  These are NOP's for contexts that don't draw to the screen */
- (void)startWaitCursorTimer;
- (void)setWaitCursorEnabled:(BOOL)flag;
- (BOOL)isWaitCursorEnabled;
#endif STRICT_OPENSTEP

/* debugging aids */
- (void)setSynchronized:(BOOL)flag;
- (BOOL)isSynchronized;
- (void)setOutputTraced:(BOOL)flag;
- (BOOL)isOutputTraced;

@end

/* converts from a DPSContext to a NSDPSContext object */
APPKIT_EXTERN NSDPSContext *DPSContextObject(DPSContext ctxt);
