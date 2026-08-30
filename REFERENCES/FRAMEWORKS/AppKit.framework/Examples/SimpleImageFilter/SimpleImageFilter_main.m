/*
 * Filter service example.
 * This is a simple, NSUnixStdio type filter. 
 * Author: Ali T. Ozer, NeXT Software, Inc.
 * Written for 3.0, June 1, 1992.
 * Rewritten for OpenStep, May 11, 1996.
 *
 * You may freely copy, distribute and reuse the code in this example.
 * NeXT disclaims any warranty of any kind, expressed or implied, as to its
 * fitness for any particular use.
 */

#import <Foundation/Foundation.h>
#import <AppKit/AppKit.h>

extern NSBitmapImageRep *bitmapImageRepFromIFF(NSData *iffData);

int main (int argc, const char *argv[]) {
    NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
    NSArray *args = [[NSProcessInfo processInfo] arguments];
    NSData *data;
    NSBitmapImageRep *tiff;
    BOOL success = NO;

    if (args && ([args count] == 2) &&
        (data = [NSData dataWithContentsOfFile:[args objectAtIndex:1]]) &&
	(tiff = bitmapImageRepFromIFF(data)) &&
	(data = [tiff TIFFRepresentation])) {
	[[NSFileHandle fileHandleWithStandardOutput] writeData:data];
        success = YES;
    }

    [pool release];
    exit(success ? 0 : 1); 
    return 0;      // ...and make main fit the ANSI spec.
}
