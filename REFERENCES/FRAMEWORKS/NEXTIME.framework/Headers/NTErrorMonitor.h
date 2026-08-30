/*
 *  NTErrorMonitor.h
 * 	Copyright 1994, NeXT Computer, Inc.
 *	
 *	A set of protocols defining expected API in components which process
 *	or generate error messages.
 *
 *	29 April 1994 mpaque Created.
 */
#import <Foundation/NSObject.h>
#import "NTValueDictionary.h"
/*
 * Errors are reported in a dictionary, with C strings under the
 * following keys (at a minimum):
 *	
 *	NTErrorTitle
 *	NTErrorMessage
 *
 * Optional detail string:
 *	NTErrorDetails
 *
 * Optional int value:
 *	NTErrorCode
 */
@protocol NTErrorMonitor <NSObject>
- (oneway void)errorReport:(bycopy NSDictionary *)report;
@end
/*
 * Controllers  may be able to provide progress
 * monitoring services.
 */
@protocol NTErrorGenerator <NSObject>
- (void) setErrorMonitor:(id <NTErrorMonitor>)monitor;
- (id <NTErrorMonitor>)errorMonitor;
@end

