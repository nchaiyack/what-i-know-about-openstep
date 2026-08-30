/* Copyright (c) 1988, 1992 NeXT Computer, Inc. */

#ifndef _ANSI_STRING_H
#define _ANSI_STRING_H

#include <standards.h>

#ifdef __STRICT_BSD__

#import <strings.h>
extern char *strcpyn();
extern char *strcatn();
extern int strcmpn();
extern char *strchr();
extern char *strrchr();
extern char *strpbrk();
extern int strspn();
extern int strcspn();
extern char *strtok();

#else /* ! __STRICT_BSD__ */

#ifdef __STRICT_ANSI__
#ifndef _SIZE_T
#define _SIZE_T
typedef unsigned long size_t;
#endif /* _SIZE_T */

#ifndef NULL
#define NULL ((void *)0)
#endif /* NULL */

#endif	/* __STRICT_ANSI__ */

#ifdef _NEXT_SOURCE
#import <stddef.h>
#endif

#ifdef __STDC__

extern void *memcpy(void *s1, const void *s2, size_t n);
extern void *memmove(void *s1, const void *s2, size_t n);
extern char *strcpy(char *s1, const char *s2);
extern char *strncpy(char *s1, const char *s2, size_t n);
extern char *strcat(char *s1, const char *s2);
extern char *strncat(char *s1, const char *s2, size_t n);
extern int memcmp(const void *s1, const void *s2, size_t n);
extern int strcmp(const char *s1, const char *s2);
#ifdef __STRICT_ANSI__
extern int strcoll(char *to, size_t maxsize, const char *from);
#else	/* !__STRICT_ANSI__ */
extern size_t strcoll(char *to, size_t maxsize, const char *from);
#endif	/* !__STRICT_ANSI__ */
extern int strncmp(const char *s1, const char *s2, size_t n);
#ifdef __STRICT_ANSI__
size_t strxfrm(char *s1, const char *s2, size_t n);
#endif  /* __STRICT_ANSI__ */
extern void *memchr(const void *s, int c, size_t n);
extern char *strchr(const char *s, int c);
extern size_t strcspn(const char *s1, const char *s2);
extern char *strpbrk(const char *s1, const char *s2);
extern char *strrchr(const char *s, int c);
extern size_t strspn(const char *s1, const char *s2);
extern char *strstr(const char *s1, const char *s2);
extern char *strtok(char *s1, const char *s2);
extern void *memset(void *s, int c, size_t n);
extern char *strerror(int errnum);
extern size_t strlen(const char *s);

#else	/* !__STDC__ */

extern void *memcpy();
extern void *memmove();
extern char *strcpy();
extern char *strncpy();
extern char *strcat();
extern char *strncat();
extern int memcmp();
extern int strcmp();
#ifdef __STRICT_ANSI__
extern int strcoll();
#else	/* !__STRICT_ANSI__ */
extern size_t strcoll();
#endif	/* !__STRICT_ANSI__ */
extern int strncmp();
#ifdef __STRICT_ANSI__
size_t strxfrm();
#endif  /* __STRICT_ANSI__ */
extern void *memchr();
extern char *strchr();
extern size_t strcspn();
extern char *strpbrk();
extern char *strrchr();
extern size_t strspn();
extern char *strstr();
extern char *strtok();
extern void *memset();
extern char *strerror();
extern size_t strlen();

#endif	/* !__STDC__ */

#ifdef _NEXT_SOURCE
extern int strncasecmp(const char *s1, const char *s2, size_t n);
extern int strcasecmp(const char *s1, const char *s2);
#endif /* _NEXT_SOURCE */

#ifndef __STRICT_ANSI__
/* added for BSD compatibility */
extern char *index(const char *s, int c);
extern char *rindex(const char *s, int c);

#undef bcopy
#define bcopy(from,to,len) ((void)memmove(to,from,len))

#undef bcmp
#define bcmp(s1,s2,len) memcmp(s1,s2,len)

#undef bzero
#define bzero(b,len) memset(b,0,len)

/* obsolete trash, for BSD compatibility */
extern char *strcpyn();
extern char *strcatn();
extern int strcmpn();
#endif	/* !__STRICT_ANSI__ */

#endif	/* !__STRICT_BSD__ */

#endif	/* _ANSI_STRING_H */
