/* Copyright (c) 1992 NeXT Computer, Inc. */

#import <stdio.h>
#import <standards.h>

#ifdef	__STRICT_BSD__
#import <strings.h>
#import	<varargs.h>
#else
#import <string.h>
#import <stdlib.h>
#import <time.h>
#import	<stdarg.h>
#endif

#import <sys/types.h>
#import <sys/wait.h>
#import <sys/time.h>
#import <sys/times.h>
#import <sys/resource.h>
#import <sys/param.h>
#import <signal.h>
#import <sys/time.h>
#import <sys/stat.h>
#import <sys/file.h>
#import <sys/socket.h>
#import <sys/vfs.h>
#import <sys/ioctl.h>
#import <netinet/in.h>
#import <arpa/inet.h>
#import <mach/machine/vm_types.h>
#import <mach/boolean.h>
#import <mach/kern_return.h>

/*
 * The above include files should be idempotent. We don't ifndef LIBC_H
 * around them to make sure that they are indeed idempotent.
 */
#ifndef LIBC_H
#define LIBC_H

extern char	**environ;
/*
 * UNIX system calls.
 */

extern int	sethostid(long hostid), gethostid(void);
extern int	sethostname(const char *, int), gethostname(char *, int);
extern int	setdomainname(const char *, int), getdomainname(char *, int);
extern int	vfork(void);
extern int	wait3(union wait *, int, struct rusage *);
extern int	wait4(int, union wait *, int, struct rusage *);
extern int	setreuid(int, int), setregid();
extern int	setgroups(int, int *);

#ifndef _POSIX_SOURCE
extern int	getpid(void);
extern int	fork(void);
extern int	execve (char *name, char **argv, char **envp);
extern int	wait(union wait *); 

extern uid_t	getuid(void), geteuid(void);
extern gid_t	getgid(void), getegid(void);
extern int	getgroups(int, int *),setgroups(int, int *);
extern int	getpgrp(int), setpgrp(int, int);
#endif	/* _POSIX_SOURCE */

extern int	setprivexec(int);

extern int	getpagesize(void);

extern int	sigvec(int , struct sigvec *, struct sigvec *);
extern int	sigblock(int), sigsetmask(int);
extern int	sigpause(int), sigstack(struct sigstack *, struct sigstack *);
extern int	killpg(int, int);
#ifndef _POSIX_SOURCE
extern int	kill(int, int);
#endif	/* _POSIX_SOURCE */

extern int	gettimeofday(struct timeval *, struct timezone *);
extern int	settimeofday(struct timeval *, struct timezone *);
extern int	getitimer(int, struct itimerval *);
extern int	setitimer(int, struct itimerval *, struct itimerval *);
extern int 	adjtime(struct timeval *, struct timeval *);

extern int	getdtablesize(void);
extern int	select(int, fd_set *, fd_set *, fd_set *, struct timeval *);
extern int	flock(int, int);
#ifndef _POSIX_SOURCE
extern int	fcntl(int, int, int);
extern int	dup(int), dup2(int, int), close(int);
#endif	/* _POSIX_SOURCE */

extern int	getpriority(int, int), setpriority(int, int, int);
extern int	getrusage(int, struct rusage *);
extern int	getrlimit(int, struct rlimit *), setrlimit(int, struct rlimit *);

extern int	unmount(const char *), mount(int, const char *, int, caddr_t);
extern int	sync(void), reboot(int);

#ifndef _POSIX_SOURCE
extern int	read(int, void *, int), write(int, const void *, int);
#endif	/* _POSIX_SOURCE */
extern int	readv(int, struct iovec *, int), writev(int, struct iovec *, int);
extern int	ioctl(int, long, ...);

extern int	getdirentries(int, char *, int, long *);
extern int	lstat(const char *, struct stat *);
extern int	fchown(int, int, int);
extern int	fchmod(int, int);
extern int	utimes(const char *, struct timeval [2]);
extern int	chroot(const char *);
extern int	symlink(const char *, const char *);
extern int	readlink(const char *, char *, int);
#ifndef _POSIX_SOURCE
extern int	rename(const char *, const char *);
#endif	/* _POSIX_SOURCE */
extern int	truncate(const char *, off_t), ftruncate(int, off_t);
extern int	statfs(const char *, struct statfs *), fstatfs(int, struct statfs *);
extern int	fsync(int);
#ifndef _POSIX_SOURCE
extern int	chdir(const char *); 

extern int	mkdir(const char *, int), rmdir(const char *);
extern int	creat(const char *, int), open(const char *, int, ...);
#endif	/* _POSIX_SOURCE */
extern int	mknod(const char *, int, int);
#ifndef _POSIX_SOURCE
extern int	unlink(const char *), stat(const char *, struct stat *);
extern int	fstat(int, struct stat *);
extern int	chown(const char *, int, int);
extern int	chmod(const char *, int); 

extern int	link(const char *, const char *); 

extern off_t	lseek(int, off_t, int);
extern int	access(const char *, int);
#endif	/* _POSIX_SOURCE */

extern int	socket(int, int, int), bind(int, struct sockaddr *, int);
extern int	listen(int, int), accept(int, struct sockaddr *, int *);
extern int	connect(int, struct sockaddr *, int);
extern int	socketpair(int, int, int, int [2]);
extern int	sendto(int, void *, int, int, struct sockaddr *, int);
extern int	send(int, void *, int, int);
extern int	recvfrom(int, void *, int, int, struct sockaddr *, int *);
extern int	recv(int, void *, int, int);
extern int	sendmsg(int, struct msghdr *, int);
extern int	recvmsg(int, struct msghdr *, int);
extern int	shutdown(int, int);
extern int	setsockopt(int, int, int, void *, int);
extern int	getsockopt(int, int, int, void *, int *);
extern int	getsockname(int, struct sockaddr *, int *);
extern int	getpeername(int, struct sockaddr *, int *);
#ifndef _POSIX_SOURCE
extern int	pipe(int [2]);

extern int	umask(int);
extern void	_exit(int);
#endif	/* _POSIX_SOURCE */

extern kern_return_t map_fd(int fd, vm_offset_t offset, 
	vm_offset_t *addr, boolean_t find_space, vm_size_t numbytes);
extern int profil(char *, int, int, int);
extern int add_profil(char *, int, int, int);

/*
 *	Other libc entry points.
 */

extern void	syslog(int, const char *, ...);
extern void	vsyslog(int, const char *, va_list);

/*
 * Organize these respective to manpage in /usr/man/man3.
 */
extern int ruserok (char *rhost, int superuser, char *ruser, char *luser);

#ifndef __STRICT_ANSI__
extern void setbuf (FILE *stream, char *buf);
#endif	/* __STRICT_ANSI__ */
extern int setbuffer (FILE *stream, char *buf, int size);
extern int setlinebuf (FILE *stream);

/* abort(3) 	*/
#ifndef __STRICT_ANSI__
#ifdef	__GNUC__
extern void abort(void) __attribute__ ((noreturn));
#else
extern void	abort(void);
#endif	__GNUC__
#endif  /* __STRICT_ANSI__ */

/* abs(3)	*/
#ifndef __STRICT_ANSI__
extern int abs (int i);
#endif  /* __STRICT_ANSI__ */

#ifndef _POSIX_SOURCE
/* alarm(3c)	*/
extern int alarm (unsigned int seconds);
#endif /* _POSIX_SOURCE */

#ifndef __STRICT_ANSI__
/* atof(3)	*/
/* double atof (char *nptr); */
#ifdef	__STRICT_BSD__
extern int atoi (char *nptr);
extern long atol (char *nptr);
#endif	__STRICT_BSD__
#endif  /* __STRICT_ANSI__ */

int ffs (int i);

/* byteorder (3n) */

#ifndef htonl
extern unsigned long htonl (unsigned long hostlong);
#endif
#ifndef htons
extern unsigned short htons (unsigned short hostshort);
#endif
#ifndef ntohl
extern unsigned long ntohl (unsigned long netlong);
#endif
#ifndef ntohs
extern unsigned short ntohs (unsigned short netshort);
#endif

/* crypt(3)	*/
extern char *crypt (char *key, char *salt);
extern void setkey (char *key);
extern void encrypt (char *block, int edflag);
/* ecvt(3)	*/
extern char *ecvt (double value, int ndigit, int *decpt, int *sign);
extern char *fcvt (double value, int ndigit, int *decpt, int *sign);
extern char *gcvt (double value, int ndigit, char *buf);

/* execl(3)	*/
#ifndef _POSIX_SOURCE
extern int execv(const char *, const char **);
extern int execl(const char *, ...);
extern int execvp(const char *, const char **);
extern int execlp(const char *, ...);
extern int execle(const char *, ...);
#endif  /* _POSIX_SOURCE */ 

extern int exect(const char *, const char **, const char **);	

/* exit(3)	*/
#ifndef __STRICT_ANSI__
#ifdef	__STRICT_BSD__
extern void	exit(int);
#endif  /* __STRICT_BSD__ */
#endif  /* __STRICT_ANSI__ */

/* getenv(3)	*/
#ifndef _POSIX_SOURCE
#ifdef	__STRICT_BSD__
extern char *getenv (char *name);
#endif  /* __STRICT_BSD__ */
#endif  /* _POSIX_SOURCE */

/* system(3)	*/
#ifndef __STRICT_ANSI__
#ifdef	__STRICT_BSD__
extern int system (char *string);
#endif	__STRICT_BSD__
#endif  /* __STRICT_ANSI__ */

/* getlogin(3)	*/
#ifndef _POSIX_SOURCE
extern char *getlogin(void);
#endif  /* _POSIX_SOURCE */

/* getmachheaders(3)	*/
extern struct mach_header **getmachheaders(void);
/* getopt(3)	*/
extern int getopt (int argc, char **argv, char *optstring);
extern char *optarg;
extern int optind;
/* getpass(3)	*/
extern char *getpass (char *prompt);
/* getpw(3)	*/
extern char getpw(int uid, char *buf);
/* getsecbyname(3)	*/
extern const struct section *getsectbyname(
	const char *segname, 
	const char *sectname);
extern char *getsectdata(
	const char *segname, 
	const char *sectname, 
	int *size);
extern const struct section *getsectbynamefromheader(
	const struct mach_header *mhp,
	const char *segname,
	const char *sectname);
extern char *getsectdatafromheader(
	const struct mach_header *mhp,
	const char *segname,
	const char *sectname,
	int *size);
extern char *getsectdatafromlib(
	const char *libname, 
	const char *segname, 
	const char *sectname,
	int *size);
/* getsegbyname(3)	*/
extern const struct segment_command *getsegbyname(const char *segname);
/* getusershell(3)	*/
extern char *getusershell(void);
extern void setusershell(void);
extern void endusershell(void);
/* getwd(3)	*/
extern char *getwd (char *pathname);
/* initgroups(3)	*/
extern int initgroups (char *name, int basegid);
/* insque (3)	*/
struct qelem {
	struct qelem *q_forw;
	struct qelem *q_back;
	char *q_data;
};
extern void insque (struct qelem *elem, struct qelem *pred);
extern void remque (struct qelem *elem);
/* mktemp(3)	*/
extern int mkstemp (char *template_);
extern char *mktemp (char *template_);
/* monitor(3)	*/
extern void monitor (char *lowpc, char *highpc, char *buf, int bufsiz, int cntsiz);
extern void monstartup (char *lowpc, char *highpc);
extern void moncontrol (int mode);
extern void moninit (void);
extern void monaddition (char *lowpc, char *highpc);
extern void moncount (char *frompc, char *selfpc);
extern void monreset (void);
extern void monoutput (const char *filename);
/* nice(3)	*/
extern int nice(int incr);

/* pause(3)	*/
#ifndef _POSIX_SOURCE
extern void pause(void);
#endif  /* _POSIX_SOURCE */

/* perror(3)	*/
#ifndef __STRICT_ANSI__
extern void perror (const char *s);
#endif  /* __STRICT_ANSI__ */

/* psignal(3)	*/
extern void psignal (unsigned int sig, char *string);
/* */
extern int putpwpasswd (char *login, char *cleartext, char *encrypted);

/* rand(3c)	*/
#ifndef __STRICT_ANSI__
extern int rand(void);
#endif  /* __STRICT_ANSI__ */

/* random(3)	*/
extern long random(void);
extern void srandom (int seed);
extern char *initstate (unsigned int seed, char *state, int n);
extern char *setstate (char *state);
/* rcmd(3)	*/
extern int rcmd (char **ahost, int inport, char *locuser, char *remuser,
	  char *cmd, int *fd2p);
extern int rresvport (int *port);
extern int ruserok (char *rhost, int superuser, char *ruser, char *luser);
/* rexec(3)	*/
extern int rexec (char **ahort, int inport, char *user, char *passwd, 
	   char *cmd, int *fd2p);

/* setuid(3)	*/
#ifndef _POSIX_SOURCE
extern int setuid (uid_t uid);
#endif	/* _POSIX_SOURCE */
extern int seteuid (uid_t euid);
extern int setruid (uid_t ruid);
#ifndef _POSIX_SOURCE
extern int setgid (gid_t gid);
#endif	/* _POSIX_SOURCE */
extern int setegid (gid_t egid);
extern int setrgid (gid_t rgid);

/* siginterrupt(3) */
extern int siginterrupt (int sig, int flag);

/* sleep(3)	*/
#ifndef _POSIX_SOURCE
extern int	sleep(unsigned int seconds);
#endif	/* _POSIX_SOURCE */
extern int	usleep(unsigned int useconds);

/* stty(3c)	*/
extern int stty (int fd, struct sgttyb *buf);
extern int gtty (int fd, struct sgttyb *buf);
/* swab(3)	*/
extern void swab (char *from, char *to, int nbytes);

/* time(3c)	*/
#ifndef _POSIX_SOURCE
extern long time (long *tloc);
/* times(3c)	*/
extern int times (struct tms *buffer);
#endif	/* _POSIX_SOURCE */

/* ttyname(3)	*/
extern int ttyslot (void);
#ifndef _POSIX_SOURCE
extern int isatty (int filedes);
extern char *ttyname (int filedes);
#endif	/* _POSIX_SOURCE */

/* ualarm(3)	*/
extern unsigned ualarm (unsigned value, unsigned interval);

/* utime(3c)	*/
#ifndef _POSIX_SOURCE
extern int utime (char *file, time_t timep[2]);
#endif	/* _POSIX_SOURCE */

/* valloc(3c)	*/
/* vlimit(3c)	*/
extern int vlimit(int resource, int value);
 
#endif  /* _LIBC_H */
