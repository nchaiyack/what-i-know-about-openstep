/*	math.h	4.6	9/11/85	*/

/* Copyright (c) 1988, 1992 NeXT Computer, Inc. */

#ifndef _ANSI_MATH_H
#define _ANSI_MATH_H

#include <standards.h>

#ifdef __STRICT_BSD__
extern int errno;
#elif defined(_NEXT_SOURCE)
#import <errno.h>
#endif

#ifdef _NEXT_SOURCE
/* Match definition in <sys/types.h>. */
#define	EDOM		33		/* Argument outside function domain. */
#define	ERANGE		34		/* Result unrepresentable as double. */
#endif /* _NEXT_SOURCE */

#ifndef __STRICT_ANSI__
extern double asinh(double x) __attribute__((const));
extern double acosh(double x) __attribute__((const));
extern double atanh(double x) __attribute__((const));
extern double hypot(double x, double y) __attribute__((const));
extern double cabs();	/* `cabs' can't be prototyped reasonably. */
extern double cbrt(double x) __attribute__((const));
extern double expm1(double x) __attribute__((const));
extern double log1p(double x) __attribute__((const));
extern double lgamma(double x) __attribute__((const));
extern double rint(double x);

/* Error functions. */
extern double erf(double x) __attribute__((const));
extern double erfc(double x) __attribute__((const));

/* Bessel functions. */
extern double j0(double x) __attribute__((const));
extern double j1(double x) __attribute__((const));
extern double jn(int n, double x) __attribute__((const));
extern double y0(double x) __attribute__((const));
extern double y1(double x) __attribute__((const));
extern double yn(int n, double x) __attribute__((const));

/* IEEE 754 support. */
extern double copysign(double x, double y);
extern double drem(double x, double y);
extern int finite(double x);
extern double logb(double x);
extern double scalb(double x, int n);
#endif	/* !__STRICT_ANSI__ */

#if defined(__STRICT_ANSI__) || defined(_NEXT_SOURCE)
extern double acos(double x) __attribute__((const));
extern double asin(double x) __attribute__((const));
extern double atan(double x) __attribute__((const));
extern double atan2(double y, double x) __attribute__((const));
extern double cos(double x) __attribute__((const));
extern double sin(double x) __attribute__((const));
extern double tan(double x) __attribute__((const));
extern double cosh(double x) __attribute__((const));
extern double sinh(double x) __attribute__((const));
extern double tanh(double x) __attribute__((const));
extern double exp(double x) __attribute__((const));
extern double frexp(double value, int *exp);
extern double ldexp(double x, int exp) __attribute__((const));
extern double log(double x) __attribute__((const));
extern double log10(double x) __attribute__((const));
extern double modf(double value, double *iptr);
extern double pow(double x, double y) __attribute__((const));
extern double sqrt(double x) __attribute__((const));
extern double ceil(double x) __attribute__((const));
extern double fabs(double x) __attribute__((const));
extern double floor(double x) __attribute__((const));
extern double fmod(double x, double y) __attribute__((const));
#endif /* __STRICT_ANSI__ || _NEXT_SOURCE */

/* Import architecture specific math definitions. */

#include <ansi/machine/math.h>

#endif /* _ANSI_MATH_H */
