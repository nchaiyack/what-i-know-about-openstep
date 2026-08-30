/*	@(#)ldd.h	2.0	03/20/90	(c) 1990 NeXT	
 *
 * kernserv/prototypes.h - kernel prototypes used by loadable device drivers
 *
 * HISTORY
 * 22-May-91	Gregg Kellogg (gk) at NeXT
 *	Split out public interface.  KERNEL_FEATURES is used to not conflict
 *	with within-KERNEL definitions.
 *
 * 16-Aug-90  Gregg Kellogg (gk) at NeXT
 *	Removed a lot of stuff that's defined in other header files. 
 *	Eventually this file should either go away or contain only imports of
 *	other files.
 *
 * 20-Mar-90	Doug Mitchell at NeXT
 *	Created.
 *
 */

#ifndef	_KERN_INTERNAL_PROTOTYPES_
#define _KERN_INTERNAL_PROTOTYPES_

#import <sys/types.h>
#import <kernserv/printf.h>
#import <sys/kernel.h>
#import <sys/buf.h>
#import <sys/uio.h>
#ifdef	m68k
#import <bsd/dev/m68k/autoconf.h>
#endif	m68k
#import <kernserv/machine/us_timer.h>
#import <kernserv/lock.h>

/* Copy or initialize data: */
int copyin(const void *p1, void *p2, unsigned int size);
int copyout(const void *p1, void *p2, unsigned int size);
void bcopy(const void *src, void *dest, int length);
void bzero(void *bp, int size);

#ifdef	KERNEL
#import <kernserv/kalloc.h>
#import <mach/message.h>

/* Cause a thread to sleep or wakeup: */
void	assert_wait(int event, boolean_t interruptible);
void	biodone(struct buf *bp);
void	biowait(struct buf *bp);
void	clear_wait(thread_t thread, int result, boolean_t interrupt_only);
void	thread_block(void);
void	thread_set_timeout(int ticks);
void	thread_sleep(int event, simple_lock_t lock, boolean_t interruptible);

/* Get information about this thread or task: */

#ifdef	MACH_USER_API
extern task_t 	current_task_EXTERNAL();
extern thread_t	current_thread_EXTERNAL();
#define current_task()	 current_task_EXTERNAL()
#define current_thread() current_thread_EXTERNAL()
#endif	MACH_USER_API

task_t	(current_task)(void);
int	thread_wait_result(void);
extern  task_t task_self();
extern 	thread_t thread_self();

/* Create or kill a thread: */
thread_t	kernel_thread(task_t task, void (*start)());
void		thread_halt_self(void);

/* Send a message: */
extern msg_return_t msg_send_from_kernel(
    msg_header_t *msgptr,
    msg_option_t option,
    msg_timeout_t tout
);
#endif	KERNEL

/* Get or test a virtual address that corresponds to a hardware address: */
caddr_t	map_addr(caddr_t address, int size);
int	probe_rb(void *address);

/* Kill the loadable kernel server: */
#if	defined(KERNEL) && !defined(KERNEL_BUILD) && !defined(ASSERT)
#if	DEBUG
#define	ASSERT(e) \
	if ((e) == 0) { \
		printf ("ASSERTION " #e " failed at line %d in %s\n", \
		    __LINE__, __FILE__); \
		panic ("assertion failed"); \
	}
#else	DEBUG
#define ASSERT(e)
#endif	DEBUG
#endif	defined(KERNEL) && defined(KERNEL_BUILD) && !defined(ASSERT)

/* Modify or inspect a string: */
char *	strcat(char *string1, const char *string2);
int 	strcmp(const char *string1, const char *string2);
int 	strncmp(const char *string1, const char *string2, unsigned long len);
char *	strcpy(char *to, const char *from);
char *  strncpy(char *to, const char *from, unsigned long len);
size_t 	strlen(const char *string);

/* In a UNIX-style server, determine whether the user has root privileges: */
int	suser(void);

#endif	_KERN_INTERNAL_PROTOTYPES_
