#ifndef _ANSI_HPPA_STDARG_H_
#define _ANSI_HPPA_STDARG_H_

#define _DEFINE_VA_LIST
#include <ansi/hppa/stdtypes.h>

/* Indicate that this program uses <stdarg.h>. */
#define __STDARG__

#define __stdarg_rounded_size(TYPE)  \
  ((sizeof (TYPE) + sizeof (int) - 1) & ~(sizeof(int)-1))

/* BSD compatibility: if `#include <varargs.h>' was encountered, don't
 * redefine the macros. */

#ifndef va_start
#define va_start(list,parmN) \
    (void)((list) = ((char *)__builtin_saveregs()))
#endif va_start

#ifndef va_end
#define va_end(list) \
    (void)((list) = (char *)0)
#endif va_end

#ifndef va_arg
#define va_arg(list, type) \
    (*(type *)((list) = (va_list)((unsigned)((list) -__stdarg_rounded_size(type)) & ~(__stdarg_rounded_size(type)-1))))
#endif va_arg


#endif	/* _ANSI_HPPA_STDARG_H_ */
