/* Copyright (c) 1988, 1992 NeXT Computer, Inc. */

#ifndef _ANSI_LOCALE_H
#define _ANSI_LOCALE_H

#include <standards.h>

#ifdef	__STRICT_ANSI__
#ifndef NULL
#define NULL	((void *)0)
#endif
#endif

#if defined(__STRICT_ANSI__) || defined(_NEXT_SOURCE) 
#define LC_ALL 0
#define LC_COLLATE 1
#define LC_CTYPE 2
#define LC_MONETARY 3
#define LC_NUMERIC 4
#define LC_TIME 5

struct lconv {
	char *decimal_point;
	char *thousands_sep;
	char *grouping;
	char *int_curr_symbol;
	char *currency_symbol;
	char *mon_decimal_point;
	char *mon_thousands_sep;
	char *mon_grouping;
	char *positive_sign;
	char *negative_sign;
	char int_frac_digits;
	char frac_digits;
	char p_cs_precedes;
	char p_sep_by_space;
	char n_cs_precedes;
	char n_sep_by_space;
	char p_sign_posn;
	char n_sign_posn;
};

#ifdef __STDC__
extern char *setlocale(int category, const char *locale);
extern struct lconv *localeconv(void);
#else
extern char *setlocale();
extern struct lconv *localeconv();
#endif	/* __STDC__ */
#endif /* __STRICT_ANSI__ || _NEXT_SOURCE */
#endif /* _ANSI_LOCALE_H */
