#ifndef _ANSI_I386_SETJMP_H
#define _ANSI_I386_SETJMP_H

#import <bsd/i386/signal.h>

typedef struct sigcontext jmp_buf[1];

#ifdef __STDC__
	extern int setjmp(jmp_buf env);
	extern int _setjmp(jmp_buf env);
	extern void longjmp(jmp_buf env, int val);
	extern void _longjmp(jmp_buf env, int val);
#else
	extern int setjmp();
	extern int _setjmp();
	extern void longjmp();
	extern void _longjmp();
#endif /* __STDC__ */

#ifdef _POSIX_SOURCE
typedef int sigjmp_buf[sizeof(struct sigcontext)+1];
	#ifdef __STDC__
		extern void siglongjmp(sigjmp_buf env, int val);
		extern int sigsetjmp(sigjmp_buf env, int savemask);
	#else
		extern void siglongjmp();
		extern int sigsetjmp();
	#endif /* __STDC__ */
#endif /* _POSIX_SOURCE */

#endif /* _ANSI_I386_SETJMP_H */
