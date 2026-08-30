/* Copyright (c) 1992 NeXT Computer, Inc.  All rights reserved.
 *
 *	File:	<ansi/hppa/math.h>
 */

/*
 * Constants.
 */

#define HUGE_VAL (1e999)

#ifndef __STRICT_ANSI__
#define HUGE	HUGE_VAL
#define NAN	(HUGE/HUGE)

#define MAXCHAR ((char)0x7f)
#define MAXSHORT ((short)0x7fff)
#define MAXINT	((int)0x7fffffff)	/* max pos 32-bit int */
#define MAXLONG ((long)0x7fffffff)

#define MINCHAR ((char)0x80)
#define MINSHORT ((short)0x8000)
#define MININT 	((int)0x80000000)	/* max negative 32-bit integer */
#define MINLONG ((long)0x80000000)

#define MAXFLOAT ((float)3.4028234663852886e38)
#define MINFLOAT ((float)1.4012984643248171e-45)
#define MAXDOUBLE ((double)1.7976931348623157e308)
#define MINDOUBLE ((double)4.9406564584124654e-324)

#define LN_MAXFLOAT ((float)8.872283935546875e1)
#define LN_MINFLOAT ((float)-1.032789306640625e2)
#define LN_MAXDOUBLE ((double)7.0978271289338397e2)
#define LN_MINDOUBLE ((double)-7.4444007192138122e2)

#define M_E	2.7182818284590452354
#define M_LOG2E	1.4426950408889634074
#define M_LOG10E	0.43429448190325182765
#define M_LN2	0.69314718055994530942
#define M_LN10	2.30258509299404568402
#define M_PI	3.14159265358979323846
#define M_PI_2	1.57079632679489661923
#define M_PI_4	0.78539816339744830962
#define M_1_PI	0.31830988618379067154
#define M_2_PI	0.63661977236758134308
#define M_2_SQRTPI	1.12837916709551257390
#define M_SQRT2	1.41421356237309504880
#define M_SQRT1_2	0.70710678118654752440
#endif /* __STRICT_ANSI__ */

