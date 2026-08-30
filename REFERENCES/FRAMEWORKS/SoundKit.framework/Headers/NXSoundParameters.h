/*
 * NXSoundParameters.h
 *
 * Copyright (c) 1993, NeXT Computer, Inc.  All rights reserved. 
 */

#import <objc/HashTable.h>
#import <Foundation/Foundation.h>
#import <sound/soundstruct.h>
#import "NXSoundParameterTags.h"

@protocol NXSoundParameters
- (BOOL)boolValueForParameter:(NXSoundParameterTag)ptag;
- (int)intValueForParameter:(NXSoundParameterTag)ptag;
- (float)floatValueForParameter:(NXSoundParameterTag)ptag;
- (void)setParameter:(NXSoundParameterTag)ptag toBool:(BOOL)flag;
- (void)setParameter:(NXSoundParameterTag)ptag toInt:(int)value;
- (void)setParameter:(NXSoundParameterTag)ptag toFloat:(float)value;
- (void)removeParameter:(NXSoundParameterTag)ptag;
- (BOOL)isParameterPresent:(NXSoundParameterTag)ptag;
- (void)getParameters:(const NXSoundParameterTag **)list
    count:(unsigned int *)numParameters;
- (void)getValues:(const NXSoundParameterTag **)list
     count:(unsigned int *)numValues forParameter:(NXSoundParameterTag)ptag;
@end

@interface NXSoundParameters : NSObject <NXSoundParameters>
{
    HashTable		*_paramTable;
    NXSoundParameterTag *_paramList;
    int			_reserved;
}

+ (NSString *)localizedNameForParameter:(NXSoundParameterTag)ptag;
- (id)init;
- (id)initFromSound:(id)aSound;
- (id)initFromSoundStruct:(SNDSoundStruct *)soundStruct;
- (void)configureSoundStruct:(SNDSoundStruct *)soundStruct;
- (void)encodeWithCoder:(NSCoder *)stream;
- (id)initWithCoder:(NSCoder *)stream;
- (void)dealloc;

@end
