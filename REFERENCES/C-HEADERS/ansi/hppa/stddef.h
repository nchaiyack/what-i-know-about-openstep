#ifndef _ANSI_HPPA_STDDEF_H
#define _ANSI_HPPA_STDDEF_H

#define _DEFINE_NULL
#define _DEFINE_SIZE_T
#define _DEFINE_WCHAR_T
#include <ansi/hppa/stdtypes.h>

/* The signed integral type of the result of subtracting two pointers. */

typedef long ptrdiff_t;

/* An integral constant expression that has type `size_t', the value of
 * which is the offset in bytes to the structure member `identifier' from
 * the beginning of the structure `type'. */

#define offsetof(type,identifier) ((size_t)&((type *)0)->identifier)

#endif /* _ANSI_HPPA_STDDEF_H */
