/*
 Copyright (c) 1993 by NeXT Computer, Inc as an unpublished work.
 All rights reserved.

This file is included by all NEXTIME application source files for easy build.
Using this file is preferred over importing individual files because it will
use a precompiled version.
*/

#ifndef NEXTIME_H
#define NEXTIME_H

#import	"movies.h"
#import	"status.h"
#import	"NTExceptions.h"

#import "NTComponent.h"
#import "NTComponentManager.h"

#import "NTClient.h"
#import "NTContext.h"

/* Data description objects, associated with NTSample objects */
#import "NTValueDictionary.h"
#import "NTDictionaryKeys.h"

/* Data transport objects */
#import "NTSampleBuffer.h"

/* Sample processing API */
#import "NTSampleProcessorProtocol.h"

/* Built-in helper objects of various sorts */
#import "NTSampleFIFO.h"
#import "NTRealTimeClock.h"
#import "NTFileIO.h"

/* In-core abstract representations of stored movies */
#import "NTMovie.h"
#import "NTTrack.h"
#import "NTMedia.h"

/* Objects used to manage movie manipulation sessions. */
#import "NTProgressMonitor.h"
#import "NTErrorMonitor.h"
#import "NTMediaHandler.h"
#import "NTMediaController.h"
#import "NTFileParser.h"

/* High level client API objects */
#import "NTMovieDocument.h"
/* #import "NTMovieAttachment.h" FIXME: Temporary til ported to Nov 1995 API secondOfMinute*/
#import "NTMovieControlView.h"
#import "NTMovieScreenCell.h"
#import "NTMovieScreen.h"

#endif NEXTIME_H
