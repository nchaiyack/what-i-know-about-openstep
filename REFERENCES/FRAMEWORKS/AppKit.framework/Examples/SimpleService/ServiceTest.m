/*
 * Services menu example. This file provides two services; one with no return value
 * (open a file), and the other that takes a string and returns a capitalized version.
 *
 * Author: Ali T. Ozer, NeXT Software, Inc.
 * Written Nov '96.
 *
 * You may freely copy, distribute and reuse the code in this example.
 * NeXT disclaims any warranty of any kind, expressed or implied, as to its
 * fitness for any particular use.
 */


#import "ServiceTest.h"

@implementation ServiceTest

/* This is an example of a service which doesn't return a value...
*/
- (void)doOpenFileService:(NSPasteboard *)pboard userData:(NSString *)data error:(NSString **)error {
    NSString *pboardString;
    NSArray *types;

    types = [pboard types];

    if (![types containsObject:NSStringPboardType] || !(pboardString = [pboard stringForType:NSStringPboardType])) {
        *error = NSLocalizedString(@"Error: Pasteboard doesn't contain a string.",
                   @"Pasteboard couldn't give string.");
        return;
    }

    if (![[NSWorkspace sharedWorkspace] openFile:pboardString]) {
        *error = [NSString stringWithFormat:NSLocalizedString(@"Error: Couldn't open file %@.",
                   @"Couldn't perform service operation."), pboardString];
        return;
    }

    return;
}

/* This service returns a value; simply the capitalized version of the provided string...
*/
- (void)doCapitalizeService:(NSPasteboard *)pboard userData:(NSString *)data error:(NSString **)error {
    NSString *pboardString;
    NSString *newString;
    NSArray *types;

    types = [pboard types];

    if (![types containsObject:NSStringPboardType] || !(pboardString = [pboard stringForType:NSStringPboardType])) {
        *error = NSLocalizedString(@"Error: Pasteboard doesn't contain a string.",
                   @"Pasteboard couldn't give string.");
        return;
    }

    newString = [pboardString capitalizedString];

    if (!newString) {
        *error = NSLocalizedString(@"Error: Couldn't capitalize string %@.",
                   @"Couldn't perform service operation.");
        return;
    }

    /* We now return the capitalized string... */
    types = [NSArray arrayWithObject:NSStringPboardType];
    [pboard declareTypes:types owner:nil];
    [pboard setString:newString forType:NSStringPboardType];

    return;
}

@end
