/*
 *  YapDocument.m
 *  Author: Ali Ozer
 *  Created: Mar 89 for 0.9
 *  Modified: Jan 96 for 4.0
 *
 *  You may freely copy, distribute and reuse the code in this example.
 *  NeXT disclaims any warranty of any kind, expressed or implied,
 *  as to its fitness for any particular use.
 */

#import "YapDocument.h"
#import "YapOutput.h"

@implementation YapDocument

- (void)setOutputView:(YapOutput *)view {
    outputView = view;
}

- (YapOutput *)outputView {
    return outputView;
}

- (void)execute:(id)sender {
    NSData *psData = [[[self textView] string] dataUsingEncoding:[NSString defaultCStringEncoding]];
    if (psData) {
        [[self outputView] executePostScriptData:psData];
    }
}

+ (NSArray *)fileTypes {
    static NSArray *types = nil;
    if (types == nil) types = [[NSArray alloc] initWithObjects:@"ps", @"eps", nil];
    return types;
}

@end
