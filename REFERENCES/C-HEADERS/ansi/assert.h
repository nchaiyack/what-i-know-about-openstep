/* Copyright (c) 1988, 1992 NeXT Computer, Inc. */

#ifndef _ASSERT_H
#define _ASSERT_H
/* for BSD compatibility */
#define _assert(x) assert(x)
#endif /* _ASSERT_H */

/* Allow multiple inclusions of `assert.h' with different settings
 * of NDEBUG. */

#undef assert

#ifdef NDEBUG

#define assert(expression) ((void)0)

#else	/* !NDEBUG */

#ifdef __STRICT_BSD__
extern void abort(void);
#define assert(expression) \
  ((expression) ? (void)0 : \
   (fprintf (stderr, "Assertion failed: " #expression \
      ", file " __FILE__ ", line %d.\n", __LINE__), \
    abort ()))

#else	/* !__STRICT_BSD__ */

#ifdef __STDC__

extern void __eprintf(const char *, const char *, int, const char *);
#define assert(expression)  \
  ((void) ((expression) ? 0 : __assert(#expression, __FILE__, __LINE__)))

#else /* !__STDC__ */

extern void __eprintf();
#define assert(expression)  \
  ((void) ((expression) ? 0 : __assert("expression", __FILE__, __LINE__)))

#endif	/* !__STDC__ */

#define __assert(expression, file, line) \
  (__eprintf("%s:%u: failed assertion `%s'\n", file, line, expression), 0)

#endif	/* !__STRICT_BSD__ */
#endif	/* !NDEBUG */
