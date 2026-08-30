/*
 *  NTProgressMonitor.h
 * 	Copyright 1994, NeXT Computer, Inc.
 *	
 *	A set of protocols defining expected API in components used to
 *	report progress of time-consuming operations.
 *
 *	8 march 1994 mpaque Created.
 */
#import <Foundation/NSObject.h>

/*
 * Any controller that can perform time-consuming operations should support a
 * progress delegate.  The progress delegate is messaged at low priority during
 * time consuming operations, and can be used to clue the user in via the GUI
 * that something is really happening (i.e., update a progress pie, or move the
 * thumb on a MovieController slider).
 */
@protocol NTProgressMonitor <NSObject>
- (oneway void)object:(id)sender beganAt:(double)progress;
- (oneway void)object:(id)sender progressedTo:(double)progress;
- (oneway void)object:(id)sender endedAt:(double)progress;
@end
/*
 * Controllers  may be able to provide progress
 * monitoring services.
 */
@protocol NTProgressController <NSObject>
- (void) setProgressMonitor:(id <NTProgressMonitor>)monitor;
- (id <NTProgressMonitor>)progressMonitor;
@end

