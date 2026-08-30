/*	NSObjCRuntime.h
	Language terminology and general utility
	Copyright 1994-1996, NeXT Software, Inc.  All rights reserved.
*/

#if defined(WIN32)
    #undef FOUNDATION_EXPORT
    #if defined(NSBUILDINGFOUNDATION)
	#define FOUNDATION_EXPORT __declspec(dllexport) extern
    #else
	#define FOUNDATION_EXPORT __declspec(dllimport) extern
    #endif
    #if !defined(FOUNDATION_IMPORT)
	#define FOUNDATION_IMPORT __declspec(dllimport) extern
    #endif
#endif

#if !defined(FOUNDATION_EXPORT)
    #define FOUNDATION_EXPORT extern
#endif

#if !defined(FOUNDATION_IMPORT)
    #define FOUNDATION_IMPORT extern
#endif

/***************	Types		***************/

#import <objc/objc.h>
#import <objc/zone.h>
#import <stdarg.h>

/***************	Functions		***************/

@class NSString;

FOUNDATION_EXPORT NSString *NSStringFromSelector(SEL aSelector);
FOUNDATION_EXPORT SEL NSSelectorFromString(NSString *aSelectorName);
FOUNDATION_EXPORT Class NSClassFromString(NSString *aClassName);
FOUNDATION_EXPORT NSString *NSStringFromClass(Class aClass);
FOUNDATION_EXPORT const char *NSGetSizeAndAlignment(const char *typePtr, unsigned int *sizep, unsigned int *alignp);

/***************	Logging		***************/

FOUNDATION_EXPORT void NSLog(NSString *format, ...);
FOUNDATION_EXPORT void NSLogv(NSString *format, va_list args);

/***************	Comparison and searching	***************/

typedef enum _NSComparisonResult {NSOrderedAscending = -1, NSOrderedSame, NSOrderedDescending} NSComparisonResult;

enum {NSNotFound = 0x7fffffff};

/***************	Constants		***************/

#if !defined(YES)
    #define YES	(BOOL)1
#endif

#if !defined(NO)
    #define NO	(BOOL)0
#endif

#if !defined(nil)
    #define nil	(id)0
#endif

#if !defined(Nil)
    #define Nil	(Class)0
#endif

/***************	MIN, MAX, ABS macros		***********/

#if defined(__GNUC__)

#if !defined(MIN)
    #define MIN(A,B)	({ typeof(A) __a = (A); typeof(B) __b = (B); __a < __b ? __a : __b; })
#endif

#if !defined(MAX)
    #define MAX(A,B)	({ typeof(A) __a = (A); typeof(B) __b = (B); __a < __b ? __b : __a; })
#endif

#if !defined(ABS)
    #define ABS(A)	({ typeof(A) __a = (A); __a < 0 ? -__a : __a; })
#endif

#else

#if !defined(MIN)
    #define MIN(A,B)	((A) < (B) ? (A) : (B))
#endif

#if !defined(MAX)
    #define MAX(A,B)	((A) > (B) ? (A) : (B))
#endif

#if !defined(ABS)
    #define ABS(A)	((A) < 0 ? (-(A)) : (A))
#endif

#endif	/* __GNUC__ */

