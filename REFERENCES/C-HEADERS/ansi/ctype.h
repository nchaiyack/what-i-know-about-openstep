/*	ctype.h	4.2	85/09/04	*/

/* Copyright (c) 1988 NeXT, Inc. - 9/13/88 CCH */
/* Copyright (c) 1992 NeXT Computer, Inc. - 11/14/92 WMG */

#ifndef _ANSI_CTYPE_H
#define _ANSI_CTYPE_H

#if defined(__STRICT_ANSI__) || defined(_NEXT_SOURCE)
#ifdef __STDC__
extern int isalnum(int c);
extern int isalpha(int c);
extern int iscntrl(int c);
extern int isdigit(int c);
extern int isgraph(int c);
extern int islower(int c);
extern int isprint(int c);
extern int ispunct(int c);
extern int isspace(int c);
extern int isupper(int c);
extern int isxdigit(int c);
extern int tolower(int c);
extern int toupper(int c);
#else
extern int isalnum();
extern int isalpha();
extern int iscntrl();
extern int isdigit();
extern int isgraph();
extern int islower();
extern int isprint();
extern int ispunct();
extern int isspace();
extern int isupper();
extern int isxdigit();
extern int tolower();
extern int toupper();
#endif /* __STDC__ */
#endif /* __STRICT_ANSI__ || _NEXT_SOURCE */

#define	_U	01
#define	_L	02
#define	_N	04
#define	_S	010
#define _P	020
#define _C	040
#define _X	0100
#define	_B	0200

extern const char _ctype_[];

#define isalnum(c)	((int)((_ctype_+1)[c]&(_U|_L|_N)))
#define	isalpha(c)	((int)((_ctype_+1)[c]&(_U|_L)))
#define iscntrl(c)	((int)((_ctype_+1)[c]&_C))
#define	isdigit(c)	((int)((_ctype_+1)[c]&_N))
#define isgraph(c)	((int)((_ctype_+1)[c]&(_P|_U|_L|_N)))
#define	islower(c)	((int)((_ctype_+1)[c]&_L))
#define isprint(c)	((int)((_ctype_+1)[c]&(_P|_U|_L|_N|_B)))
#define ispunct(c)	((int)((_ctype_+1)[c]&_P))
#define	isspace(c)	((int)((_ctype_+1)[c]&_S))
#define	isupper(c)	((int)((_ctype_+1)[c]&_U))
#define	isxdigit(c)	((int)((_ctype_+1)[c]&(_N|_X)))

#define _tolower(c)	((int)((c)-'A'+'a'))
#define _toupper(c)	((int)((c)-'a'+'A'))

#ifdef __STRICT_BSD__
#define tolower(c)	_tolower(c)
#define toupper(c)	_toupper(c)
#define isascii(c)	((unsigned)(c)<=0177)
#define toascii(c)	((int)((c)&0177))
#else	/* !__STRICT_BSD__ */
#ifndef __STRICT_ANSI__
#define tolower(c)	({int _c=(c); isupper(_c) ? _tolower(_c) : _c;})
#define toupper(c)	({int _c=(c); islower(_c) ? _toupper(_c) : _c;})
#define isascii(c)	((unsigned)(c)<=0177)
#define toascii(c)	((int)((c)&0177))
#endif /* !__STRICT_ANSI__ */
#endif /* !__STRICT_BSD__ */

#endif /* _ANSI_CTYPE_H */
