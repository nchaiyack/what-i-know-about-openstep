#ifndef _BSD_HPPA_VARARGS_H_
#define _BSD_HPPA_VARARGS_H_

/* Indicate that this program uses <varargs.h>. */
#define	__VARARGS__

#ifdef __STRICT_ANSI__
#error <varargs.h> should not be included in an ANSI C program.
#endif /* __STRICT_ANSI__ */

/* If ansi/stdarg.h was included, this overrides */
#undef va_start
#undef va_end
#undef va_arg

/* Get the definition of `va_list'. */
#define _DEFINE_VA_LIST
#include <ansi/hppa/stdtypes.h>

#define va_dcl int va_alist;

#define __va_rounded_size(TYPE)  \
  ((sizeof (TYPE) + sizeof (int) - 1) & ~(sizeof(int)-1))

#define va_start(AP) \
    (void)((AP) = ((char *)__builtin_saveregs()))
#define va_end(AP) \
    (void)((AP) = (char *)0)
#define va_arg(AP, type) \
    (*(type *)((AP) = (va_list)((unsigned)((AP) -__va_rounded_size(type)) & ~(__va_rounded_size(type)-1))))

#endif	/* _BSD_HPPA_VARARGS_H_ */
