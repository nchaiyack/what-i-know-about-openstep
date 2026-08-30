/* Copyright 1993 NeXT Computer, Inc. - WMG */

#ifndef _UNISTD_H
#define _UNISTD_H

#include <standards.h>

#define STDIN_FILENO	0
#define STDOUT_FILENO	1
#define STDERR_FILENO	2

#ifdef _POSIX_SOURCE
	/* Execution-time implementation options. */
	#define _POSIX_VDISABLE			'\377'
#endif /* _POSIX_SOURCE */

#if defined(_POSIX_SOURCE) && !defined(POSIX_KERN)
	#include <sys/types.h>	/* for size_t and ssize_t */
	#include <stddef.h>	/* for NULL */
	#include <sys/fcntl.h>	/* for F_OK, X_OK, W_OK and R_OK */

	/* Initial values of file descriptors for
	 * stdin, stdout and stderr
	 */
	#define STDIN_FILENO	0
	#define STDOUT_FILENO	1
	#define STDERR_FILENO	2

	/* Symbolic constants for lseek() */
	#ifndef SEEK_SET
		#define SEEK_SET	0
	#endif	/* SEEK_SET */
	#ifndef SEEK_CUR	 
		#define SEEK_CUR	1
	#endif	/* SEEK_CUR */
	#ifndef SEEK_END	 
		#define SEEK_END	2
	#endif /* SEEK_END */

	/* Compile-time implementation options */
	#define _POSIX_JOB_CONTROL		1
	#define _POSIX_SAVED_IDS		1
	#define _POSIX_VERSION			199009L

	/* Execution-time implementation options. */
	#define _POSIX_CHOWN_RESTRICTED		1
	#define _POSIX_NO_TRUNC			1

	/* Values for sysconf() 	*/
	#define	_SC_ARG_MAX		0
	#define	_SC_CHILD_MAX		1
	#define	_SC_CLK_TCK		2
	#define	_SC_JOB_CONTROL		3
	#define	_SC_NGROUPS_MAX		4
	#define	_SC_OPEN_MAX		5
	#define	_SC_SAVED_IDS		6
	#define	_SC_STREAM_MAX		7
	#define	_SC_TZNAME_MAX		8
	#define	_SC_VERSION		9

	/* Values for pathconf() 	*/
	#define	_PC_CHOWN_RESTRICTED	0
	#define	_PC_LINK_MAX		1
	#define	_PC_MAX_CANON		2
	#define	_PC_MAX_INPUT		3
	#define	_PC_NAME_MAX		4
	#define	_PC_NO_TRUNC		5
	#define	_PC_PATH_MAX		6
	#define	_PC_PIPE_BUF		7
	#define	_PC_VDISABLE		8

	#ifdef __STDC__
		extern void _exit(int status);
		extern int access(const char *path, int amode);
		extern unsigned int alarm(unsigned int seconds);
		extern int chdir(const char *path);
		extern int chown(const char *path, uid_t owner,
			gid_t group);
		extern int close(int fildes);
		extern char *ctermid(char *s);
		extern int dup(int fildes);
		extern int dup2(int fildes, int fildes2);
		extern int execl(const char *path,
			const char *arg0, ...);
		extern int execle(const char *path,
			const char *arg0, ...); 
		extern int execlp(const char *file,
			const char *arg0, ...); 
		extern int execv(const char *path,
			char *const argv[]);
		extern int execve(const char *path,
			char *const argv[], char *const envp[]);
		extern int execvp(const char *file, char *const argv[]);
		extern pid_t fork(void);
		extern long fpathconf(int fildes, int name);
		extern char *getcwd(char *buf, size_t size);
		extern gid_t getegid(void);
		extern uid_t geteuid(void);
		extern gid_t getgid(void);
		extern int getgroups(int gidsetsize, gid_t *grouplist);
		extern char *getlogin(void);
		extern pid_t getpgrp(void);
		extern pid_t getpid(void);
		extern pid_t getppid(void);
		extern uid_t getuid(void);
		extern int isatty(int fildes);
		extern int link(const char *path1, const char *path2);
		extern off_t lseek(int fildes, off_t offset, int whence);
		extern long pathconf(const char *path, int name);
		extern int pause(void);
		extern int pipe(int fildes[2]);
		extern ssize_t read(int fildes, void *buf, size_t nbyte);
		extern int rmdir(const char *path);
		extern int setgid(gid_t gid);
		extern int setpgid(pid_t pid, pid_t pgid);
		extern pid_t setsid(void);
		extern int setuid(uid_t uid);
		extern unsigned int sleep(unsigned int seconds);
		extern long sysconf(int name);
		extern pid_t tcgetpgrp(int fildes);
		extern int tcsetpgrp(int fildes, pid_t pgrp_id);
		extern char *ttyname(int fildes);
		extern int unlink(const char *path);
		extern ssize_t write(int fildes, const void *buf,
			size_t nbyte); 
	#else
		extern void _exit();
		extern int access();
		extern unsigned int alarm();
		extern int chdir();
		extern int chown();
		extern int close();
		extern char *ctermid();
		extern int dup();
		extern int dup2();
		extern int execl();
		extern int execle(); 
		extern int execlp(); 
		extern int execv();
		extern int execve();
		extern int execvp();
		extern pid_t fork();
		extern long fpathconf();
		extern char *getcwd();
		extern gid_t getegid();
		extern uid_t geteuid();
		extern gid_t getgid();
		extern int getgroups();
		extern char *getlogin();
		extern pid_t getpgrp();
		extern pid_t getpid();
		extern pid_t getppid();
		extern uid_t getuid();
		extern int isatty();
		extern int link();
		extern off_t lseek();
		extern long pathconf();
		extern int pause();
		extern int pipe();
		extern ssize_t read();
		extern int rmdir();
		extern int setgid();
		extern int setpgid();
		extern pid_t setsid();
		extern int setuid();
		extern unsigned int sleep();
		extern long sysconf();
		extern pid_t tcgetpgrp();
		extern int tcsetpgrp();
		extern char *ttyname();
		extern int unlink();
		extern ssize_t write();
	#endif /* __STDC__ */
#endif /* _POSIX_SOURCE  && !POSIX_KERN */
#endif /* _UNISTD_H */
