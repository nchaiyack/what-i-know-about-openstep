#ifndef	_kern_server_reply_handler
#define	_kern_server_reply_handler

/* Module kern_server_reply */

#include <mach/kern_return.h>
#include <mach/port.h>
#include <mach/message.h>

#ifndef	mig_external
#define mig_external extern
#endif

#include <mach/std_types.h>
#include <kernserv/kern_server_reply_types.h>

/*
 * Functions to call for handling returned messages.
 */
typedef struct kern_server_reply {
	void		*arg;		/* argument to pass to function */
	int		timeout;	/* timeout for RPC return msg_send */

	/* Routine panic */
	kern_return_t (*panic) (
		void *boot_port,
		panic_msg_t panic_msg);

	/* Routine section_by_name */
	kern_return_t (*section_by_name) (
		void *boot_port,
		macho_header_name_t segname,
		macho_header_name_t sectname,
		vm_address_t *addr,
		vm_size_t *size);

	/* SimpleRoutine log_data */
	kern_return_t (*log_data) (
		void *log_port,
		log_entry_array_t log,
		unsigned int logCnt);
} kern_server_reply_t;


#define	kern_server_replyMaxRequestSize	292
#define	kern_server_replyMaxReplySize	48

/* Handler kern_server_reply_handler */
mig_external kern_return_t kern_server_reply_handler (
	msg_header_t *InHeadP,
	kern_server_reply_t *kern_server_reply);

#endif	_kern_server_reply_handler
