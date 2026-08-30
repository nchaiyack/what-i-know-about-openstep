/*	@(#)setjmp.h 1.5 89/09/08 SMI; from UCB 4.1 83/05/03	*/

#ifndef	__sparc_setjmp_h
#define	__sparc_setjmp_h

/*
 * The jmp_buf is really a sigcontext followed by extra state we need to save.
 */
#define	_JBLEN	29

typedef	unsigned jmp_buf[_JBLEN];

/*
 * One extra word for the "signal mask saved here" flag.
 */
typedef	unsigned sigjmp_buf[_JBLEN+1];

#ifdef __STDC__
extern int	setjmp(jmp_buf env);
extern int	_setjmp(jmp_buf env);
extern int	sigsetjmp(sigjmp_buf env, int savemask);
extern void	longjmp(jmp_buf env, int val);
extern void	_longjmp(jmp_buf env, int val);
extern void	siglongjmp(sigjmp_buf env, int val);
#else
extern int	setjmp(/* jmp_buf env */);
extern int	_setjmp(/* jmp_buf env */);
extern int	sigsetjmp(/* sigjmp_buf env, int savemask */);
extern void	longjmp(/* jmp_buf env, int val */);
extern void	_longjmp(/* jmp_buf env, int val */);
extern void	siglongjmp(/* sigjmp_buf env, int val */);
#endif /*__STDC__*/

/*
 * Routines that call setjmp have strange control flow graphs,
 * since a call to a routine that calls resume/longjmp will eventually
 * return at the setjmp site, not the original call site.  This
 * utterly wrecks control flow analysis.
 */
#pragma unknown_control_flow(sigsetjmp, setjmp, _setjmp)

#endif	/* !__sparc_setjmp_h */
