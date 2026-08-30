#import <AppKit/AppKit.h>

@interface YapOutput : NSView {
    NSWindow *cache;
}

- (void)executePostScriptData:(NSData *)data;
- (void)drawRect:(NSRect)rect;
- (NSWindow *)cacheWindow;
- (void)updateSizeFromPreferences;

@end




