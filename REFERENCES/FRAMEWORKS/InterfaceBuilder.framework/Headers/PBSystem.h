
// System-dependent ProjectBuilder definitions
// Copyright 1996-1997 Apple Computer, Inc. (unpublished)

#if defined(__MACH__)

#define PB_EXTERN           extern
#define PRIVATE_EXTERN      __private_extern__

#elif defined(WIN32)

#ifndef BUILDING_PB_FRAMEWORK
#define WINDOWS_DLL_GOOP     __declspec(dllimport)
#else
#define WINDOWS_DLL_GOOP     __declspec(dllexport) 
#endif

#define PB_EXTERN           WINDOWS_DLL_GOOP extern
#define PRIVATE_EXTERN      extern

#elif defined(NeXT_PDO)

#define PB_EXTERN           extern
#define PRIVATE_EXTERN      __private_extern__

#endif
