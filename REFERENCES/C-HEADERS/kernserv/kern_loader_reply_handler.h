#ifndef	_kern_loader_reply_handler
#define	_kern_loader_reply_handler

/* Module kern_loader_reply */

#include <mach/kern_return.h>
#include <mach/port.h>
#include <mach/message.h>

#ifndef	mig_external
#define mig_external extern
#endif

#include <mach/std_types.h>
#include <kernserv/kern_loader_types.h>

/*
 * Functions to call for handling returned messages.
 */
typedef struct kern_loader_reply {
	void		*arg;		/* argument to pass to function */
	int		timeout;	/* timeout for RPC return msg_send */

	/* SimpleRoutine string */
	kern_return_t (*string) (
		void *reply_port,
		printf_data_t string,
		unsigned int stringCnt,
		int level);

	/* SimpleRoutine ping */
	kern_return_t (*ping) (
		void *reply_port,
		int id);

	/* SimpleRoutine log_data */
	kern_return_t (*log_data) (
		void *reply_port,
		printf_data_t log_data,
		unsigned int log_dataCnt);
} kern_loader_reply_t;


#define	kern_loader_replyMaxRequestSize	48
#define	kern_loader_replyMaxReplySize	32

/* Handler kern_loader_reply_handler */
mig_external kern_return_t kern_loader_reply_handler (
	msg_header_t *InHeadP,
	kern_loader_reply_t *kern_loader_reply);

#endif	_kern_loader_reply_handler
