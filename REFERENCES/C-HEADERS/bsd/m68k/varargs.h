/*	varargs.h	4.1	83/05/03	*/

#ifndef _BSD_M68K_VARARGS_H_
#define _BSD_M68K_VARARGS_H_

/* Indicate that this program uses <varargs.h>. */
#define	__VARARGS__

#ifdef __STRICT_ANSI__
#error <varargs.h> should not be included in an ANSI C program.
#endif /* __STRICT_ANSI__ */

/* If ansi/stdarg.h was included, this overrides */
#ifdef __STDARG__
#undef va_start
#undef va_end
#undef va_arg

#else	/* !__STDARG__ */

/* Get the definition of `va_list'. */
#define _DEFINE_VA_LIST
#include <ansi/m68k/stdtypes.h>

#endif	/* !__STDARG__ */

# define va_dcl int va_alist;
# define va_start(list) list = (char *) &va_alist
# define va_end(list)
# define va_arg(list,mode) ((mode *)(list += sizeof(mode)))[-1]

#endif	/* _BSD_M68K_VARARGS_H_ */
