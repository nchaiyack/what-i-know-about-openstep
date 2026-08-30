#import <AppKit/AppKit.h>
#import "Document.h"

@class YapOutput;

@interface YapDocument : Document {
    YapOutput *outputView;
}

- (void)setOutputView:(YapOutput *)view;
- (YapOutput *)outputView;
- (void)execute:(id)sender;

@end
