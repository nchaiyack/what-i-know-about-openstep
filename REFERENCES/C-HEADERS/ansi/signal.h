#ifndef _ANSI_SIGNAL_H
#define _ANSI_SIGNAL_H

#ifndef __STRICT_BSD__
typedef char sig_atomic_t;
#define SIG_ERR		(void (*)())-1
#ifdef __STDC__
extern int raise(int sig);
#else	/* !__STDC__ */
extern int raise();
#endif 	/* !__STDC__ */
#endif	/* !__STRICT_BSD__ */

#if (defined(__STRICT_ANSI__) && !defined(_POSIX_SOURCE))
#define SIG_DFL		(void (*)())0
#define SIG_IGN		(void (*)())1

#define SIGINT		2
#define SIGILL		4
#define SIGABRT		6
#define SIGFPE		8
#define SIGSEGV		11
#define SIGTERM		15

void (*signal(int sig, void (*func)(int)))(int);

#else	/* !__STRICT_ANSI__ || _POSIX_SOURCE */

#include <sys/signal.h>

#endif	/* !__STRICT_ANSI__ || _POSIX_SOURCE */
#endif	/* _ANSI_SIGNAL_H */
