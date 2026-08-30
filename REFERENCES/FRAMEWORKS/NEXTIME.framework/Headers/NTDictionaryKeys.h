//
//  NTDictionaryKeys.h
//
//
//	Popular keys reserved by NEXTIME, and API for constructing frequently
//	used dictionaries.
//
#import <Foundation/NSString.h>
#import <AppKit/NSGraphics.h>
#import "NTValueDictionary.h"
#import "typetags.h"

// In general, components are identified with a type and subtype name.
// All components with a specific type name have the same core API, which
// is defined by a protocol with that type name.  Component subtypes differ
// in the implementation of that API.  For example, there may be a number of
// components with the component type name of "NTMovieParser", but each
// subtype will be designed to parse a different format movie file (e.g., AVI,
// QuickTime, 'cdy', ... )

extern NSString * NTComponentTypeName;
extern NSString * NTComponentSubtypeName;

// Generic subtype
extern NSString * NTGeneric;

// The version indicates the API version the component works with,
// and should change infrequently, if at all.  The Revision Level
// may be bumped at any time, and is used to track which revision
// component was used to generate a movie.
extern NSString * NTComponentVersion;
extern NSString * NTComponentRevisionLevel;
extern NSString * NTVendor;

// Keys used in reporting a component description (localizable)
// These are intended for use in GUIs which support selection of a
// component from a list.
extern NSString * NTComponentName;
extern NSString * NTComponentDescription;
extern NSString * NTLocalizedComponentName;
extern NSString * NTLocalizedComponentDescription;

// Key to retreive the principal class of a component as a C string
extern NSString * NTComponentPrincipalClass;

// Key to define input and output formats for configuration
extern NSString * NTConfigurationKey;
extern NSString * NTSampleInput;
extern NSString * NTSampleOutput;

// Keys for sample description dictionaries
extern NSString * NTSampleDescriptionIndex;
extern NSString * NTSampleRate;
extern NSString * NTBitsPerChannel;
extern NSString * NTChannelsPerSample;

extern NSString * NTMediaType;
extern NSString * NTCodecName;
extern NSString * NTFormatType;
extern NSString * NTFormatSubtype;
extern NSString * NTFileSuffixArray;
extern NSString * NTCodecInstance;
extern NSString * NTCodecData;
extern NSString * NTEncodingKey;

extern NSString * NTHeight;
extern NSString * NTWidth;

extern NSString * NTPixelEncoding;
extern NSString * NTColorSpace;
extern NSString * NTBitsPerPixel;
extern NSString * NTBytesPerRow;
extern NSString * NTHasAlpha;
extern NSString * NTIsPlanar;

// Assorted video related odds and ends
extern NSString * NTTemporalQuality;
extern NSString * NTSpatialQuality;
extern NSString * NTHorizontalResolution;
extern NSString * NTVerticalResolution;
extern NSString * NTColorLookupTable;
extern NSString * NTColorLookupTableID;
extern NSString * NTPixelTransfer;
extern NSString * NTPrivateData;
extern NSString * NTHiQuality;

// TO DO: Define keys for members of current property list hierarchy
extern NSString * NTCompressor;
extern NSString * NTDecompressor;
extern NSString * NTMediaPlaybackHandler;
extern NSString * NTFile_Parser;
extern NSString * NTFile_Writer;
extern NSString * NTPasteboardMovie_Parser;

//
// Values for NTFormatType and NTFormatSubtype keys
//
// Predefined (but not all-inclusive!) NTFormatType names
extern NSString * NTRaw;
extern NSString * NTCompressed;
extern NSString * NTText;
extern NSString * NTVideoOut;
extern NSString * NTFilename;
extern NSString * NTSampleOut;
extern NSString * NTOutputDevice;

// Predefined (but not all-inclusive!) NTFormatSubtype names for
// NTMediaType "Sound" NTFormatType "NTRaw"
extern NSString * NTBiased;

// Predefined (but not all-inclusive!) NTFormatSubtype names for
// NTMediaType "Sound" NTFormatType "Compressed"
extern NSString * NTDeltaMulaw;
extern NSString * NTMulaw;

// Predefined (but not all-inclusive!) NTFormatSubtype names for
// NTMediaType "Video" NTFormatType "Compressed"
extern NSString * NTRoadPizza;
extern NSString * NTCinepak;
extern NSString * NT_MPEG1;
extern NSString * NT_JPEG1;
extern NSString * NTWavelet;
extern NSString * NTMicroWavelet;
extern NSString * NTSpaceTimeVQ;
extern NSString * NTRawQT;

// Predefined keys for video display device
extern NSString * NTDisplay;
extern NSString * NTViewID;

// Predefined keys for sound device
extern NSString * NTSoundContextID;

// Keys used with I/O devices (Sound or graphics input or output)
extern NSString * NTDeviceName;
extern NSString * NTDeviceType;

// Predefined (but not all-inclusive!) NTDeviceType names
extern NSString * NTSoundOut;
extern NSString * NTSoundIn;

// Predefined (but not all-inclusive!) NTMediaType names
extern NSString * NTVideo;
extern NSString * NTSound;

// Keys used with NTSoundIn and  NTSoundOut dictionaries
//
// NTSampleRates keys a NTStorage object full of doubles.
// NTAvailableBitsPerChannel keys a NTStorage object full of
// integer bits per sample values.
//
extern NSString * NTAvailableBitsPerChannel;
extern NSString * NTSampleRates;
extern NSString * NTMinimumSampleRate;
extern NSString * NTMaximumSampleRate;
extern NSString * NTMaximumChannels;

// Predefined NTPixelEncoding names
extern NSString * NTPixel_RGBX8888;
extern NSString * NTPixel_XRGB8888;
extern NSString * NTPixel_XBGR8888;
extern NSString * NTPixel_RGBX4444;
extern NSString * NTPixel_XRGB1555;
extern NSString * NTPixel_W8;
extern NSString * NTPixel_C8;

// Keys for NTMediaHandler objects
extern NSString * NTReserveSystemOverhead;

// Error reporting keys
extern NSString * NTErrorTitle;
extern NSString * NTErrorMessage;
extern NSString * NTErrorDetails;
extern NSString * NTErrorCode;

// User Dictionary keys, as used in movie, track, and media user dictionaries
extern NSString * NTMovieCopyright;
extern NSString * NTMovieDate;
extern NSString * NTMovieDirector;
extern NSString * NTMovieEditDesc1;
extern NSString * NTMovieEditDesc2;
extern NSString * NTMovieEditDesc3;
extern NSString * NTMovieEditDesc4;
extern NSString * NTMovieEditDesc5;
extern NSString * NTMovieEditDesc6;
extern NSString * NTMovieEditDesc7;
extern NSString * NTMovieEditDesc8;
extern NSString * NTMovieEditDesc9;
extern NSString * NTMovieFormat;
extern NSString * NTMovieInformation;
extern NSString * NTMovieProducer;
extern NSString * NTMoviePerformers;
extern NSString * NTMovieRequirements;
extern NSString * NTMovieSourceCredits;
extern NSString * NTMovieWriters;

// NSThread threadDictionary keys
extern NSString * NTThreadContext;

// Misc keys
extern NSString * NTFileType;

// Keys to support inspector panel, used in currentMovieParameters dict
extern NSString * NTMovieDataSize;
extern NSString * NTMovieDataRate;
extern NSString * NTMovieVideoBitsPerPixel;
extern NSString * NTMovieVideoFrameRate;
extern NSString * NTMovieUserDictionary;
extern NSString * NTMovieReferencedFiles;

@interface NSMutableDictionary (NEXTIME_CannedDictionaries)
//
// Sample description dictionaries:
//
//	All sample data within NEXTIME is stamped with a sample size in bytes,
//	a sample time, sample duration, and a count.  A dictionary may also be
//	associated with a sample to provide additional descriptive information.
//	The initializers in this module provide a convenient means of
//	constructing dictionaries containing supplementary information for
//	specific sample types.

- initSoundDescriptionWithFormat:(int)format
		sampleRate	:(double)rate
		bitsPerChannel	:(int)nbits
		channelCount	:(int)nchannels;

- initEncodedDescriptionWithSampleType:(NTTypeTag)sampleType
		codecName :(NSString *)codecName
		formatType :(NSString *)codecType
		formatSubtype :(NSString *)subType
		codecInstance :(id)codec;

- initBitmapDescriptionWithFormatType: (NSString *) type
                subtype: (NSString *) subtype
                width: (int) width
                height: (int) height;

//
// the following is obsolete -- pixel encodings are completely described
// by their pixel encoding (format subtype).
//  
- initBitmapDescriptionWithColorSpace:(NSString *)cSpace
		pixelsWide	:(int)width
		pixelsHigh	:(int)height
		bitsPerChannel	:(int)bpc
		channelsPerPixel:(int)cpp
		bitsPerPixel	:(int)pBits
		bytesPerRow	:(int)rBytes
		hasAlpha	:(BOOL)alpha
		isPlanar	:(BOOL)is_planar;

//
// Components may be requested from the Component Manager by passing
// in a dictionary of key/value pairs to be matched.
//
- initComponentRequestForType :(NSString *)componentType subtype :(NSString *)componentSubtype;

@end
