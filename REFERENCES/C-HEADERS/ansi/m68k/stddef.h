#ifndef _ANSI_M68K_STDDEF_H
#define _ANSI_M68K_STDDEF_H

#define _DEFINE_NULL
#define _DEFINE_SIZE_T
#define _DEFINE_WCHAR_T
#include <ansi/m68k/stdtypes.h>

typedef long ptrdiff_t;

#define offsetof(type,identifier) ((size_t)&((type *)0)->identifier)

#endif /* _ANSI_M68K_STDDEF_H */
