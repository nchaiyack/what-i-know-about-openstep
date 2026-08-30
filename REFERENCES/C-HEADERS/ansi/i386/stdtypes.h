/* Definitions of standard types. */

/* An implementation-defined null pointer constant. */

#ifdef _DEFINE_NULL
#ifndef NULL
#define NULL ((void *)0)
#endif
#undef _DEFINE_NULL
#endif

/* The unsigned integral type of the result of the `sizeof' operator. */

#ifdef _DEFINE_SIZE_T
#ifndef _SIZE_T
#define _SIZE_T
typedef unsigned long size_t;
#endif
#undef _DEFINE_SIZE_T
#endif

/* An integral type whose range of values can represent distinct codes for
 * all members of the largest extended character set specified among the
 * supported locales. */

#ifdef _DEFINE_WCHAR_T
#ifndef _WCHAR_T
#define _WCHAR_T
typedef unsigned short wchar_t;
#endif
#undef _DEFINE_WCHAR_T
#endif

#ifdef _DEFINE_VA_LIST
#ifndef _VA_LIST
#define _VA_LIST
typedef char *va_list;
#endif
#undef _DEFINE_VA_LIST
#endif
