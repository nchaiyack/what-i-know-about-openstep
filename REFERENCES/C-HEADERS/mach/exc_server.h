#ifndef	_catch_exc
#define	_catch_exc

/* Module exc */

#include <mach/kern_return.h>
#include <mach/port.h>
#include <mach/message.h>

#ifndef	mig_external
#define mig_external extern
#endif

#include <mach/std_types.h>

/* Routine catch_exception_raise */
mig_external kern_return_t catch_exception_raise (
	port_t exception_port,
	port_t thread,
	port_t task,
	int exception,
	int code,
	int subcode);

#define	excMaxRequestSize	64
#define	excMaxReplySize	32

/* Server exc_server */
mig_external boolean_t exc_server
	(msg_header_t *InHeadP, msg_header_t *OutHeadP);

#endif	_catch_exc
