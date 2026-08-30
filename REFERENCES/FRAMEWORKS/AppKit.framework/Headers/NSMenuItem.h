/*
        NSMenuItem.h
        Application Kit
        Copyright (c) 1995-1996, NeXT Software, Inc.
        All rights reserved.
*/

#import <Foundation/Foundation.h>
#import <AppKit/AppKitDefines.h>

@protocol NSMenuItem <NSCopying, NSCoding>

- (NSString *)title;
- (void)setTitle:(NSString *)aString;
- (BOOL)isEnabled;
- (void)setEnabled:(BOOL)flag;

- (id)target;
- (void)setTarget:(id)anObject;
- (SEL)action;
- (void)setAction:(SEL)aSelector;
- (int)tag;
- (void)setTag:(int)anInt;

- (NSString *)keyEquivalent;
- (void)setKeyEquivalent:(NSString *)aKeyEquivalent;
- (unsigned int)keyEquivalentModifierMask;
- (void)setKeyEquivalentModifierMask:(unsigned int)mask;

+ (void)setUsesUserKeyEquivalents:(BOOL)flag;
+ (BOOL)usesUserKeyEquivalents;

- (NSString *)userKeyEquivalent;

- (BOOL)hasSubmenu;

#ifndef STRICT_OPENSTEP
- (void)setMnemonicLocation:(unsigned)location;
- (unsigned)mnemonicLocation;
- (NSString *)mnemonic;
- (void)setTitleWithMnemonic:(NSString *)stringWithAmpersand;

- (id)representedObject;
- (void)setRepresentedObject:(id)anObject;
#endif STRICT_OPENSTEP

@end

#ifndef STRICT_OPENSTEP
@interface NSMenuItem : NSObject <NSMenuItem> {
    @private
    unsigned char _pad[64];
}
@end
#endif
