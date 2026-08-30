/* stdarg.h -	SPARC version */

#ifndef _ANSI_SPARC_STDARG_H
#define _ANSI_SPARC_STDARG_H

#define _DEFINE_VA_LIST
#include <ansi/sparc/stdtypes.h>

/* Indicate that this program uses <stdarg.h>. */
#define __STDARG__

#define NEW_VARARGS

#define __va_rounded_size(TYPE)  \
  (((sizeof (TYPE) + sizeof (int) - 1) / sizeof (int)) * sizeof (int))

#define va_alist  __builtin_va_alist

#ifndef va_start
#ifdef NEW_VARARGS
#define va_start(AP, LASTARG) ((AP) = ((char *) __builtin_saveregs()))
#else
#define va_start(AP) \
  (__builtin_saveregs(), (AP) = ((char *) __builtin_next_arg()))
#endif
#endif va_start

#ifndef va_end
void va_end (va_list list);		/* Defined in libgcc.a */
#define va_end(pvar)
#endif va_end

/* RECORD_TYPE args passed using the C calling convention are
   passed by invisible reference.  ??? RECORD_TYPE args passed
   in the stack are made to be word-aligned; for an aggregate that is
   not word-aligned, we advance the pointer to the first non-reg slot.  */
/* We don't declare the union member `d' to have type TYPE
   because that would lose in C++ if TYPE has a constructor.  */
/* We cast to void * and then to TYPE * because this avoids
   a warning about increasing the alignment requirement.
   The casts to char * avoid warnings about invalid pointer arithmetic.  */
#ifndef va_arg
#define va_arg(pvar,TYPE)					\
__extension__							\
({ TYPE __va_temp;						\
   ((__builtin_classify_type (__va_temp) >= 12)			\
    ? ((pvar) = (char *)(pvar) + __va_rounded_size (TYPE *),	\
       **(TYPE **) (void *) ((char *)(pvar) - __va_rounded_size (TYPE *))) \
    : __va_rounded_size (TYPE) == 8				\
    ? ({ union {char __d[sizeof (TYPE)]; int __i[2];} __u;	\
	 __u.__i[0] = ((int *) (void *) (pvar))[0];		\
	 __u.__i[1] = ((int *) (void *) (pvar))[1];		\
	 (pvar) = (char *)(pvar) + 8;				\
	 *(TYPE *) (void *) __u.__d; })				\
    : ((pvar) = (char *)(pvar) + __va_rounded_size (TYPE),	\
       *((TYPE *) (void *) ((char *)(pvar) - __va_rounded_size (TYPE)))));})
#endif va_arg

#endif /* _ANSI_SPARC_STDARG_H */
