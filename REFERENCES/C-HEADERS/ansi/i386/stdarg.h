#ifndef _ANSI_I386_STDARG_H_
#define _ANSI_I386_STDARG_H_

/* BSD compatibility: if #include <varargs.h> seen, don't redefine per ANSI */
#ifndef __VARARGS__

/* Indicate that this program uses <stdarg.h> */
#define	__STDARG__

#define _DEFINE_VA_LIST
#include <ansi/i386/stdtypes.h>

/* Amount of space required in an argument list for an arg of type TYPE.
   TYPE may alternatively be an expression whose type is used.  */

#define __va_rounded_size(TYPE)  \
  (((sizeof (TYPE) + sizeof (int) - 1) / sizeof (int)) * sizeof (int))

#define va_start(AP, LASTARG) 						\
 (AP = ((char *) __builtin_next_arg (LASTARG)))

void va_end (va_list);
#define va_end(AP)

#define va_arg(AP, TYPE)						\
 (AP += __va_rounded_size (TYPE),					\
  *((TYPE *) (AP - __va_rounded_size (TYPE))))

#endif	__VARARGS__

#endif	_ANSI_I386_STDARG_H_
