#ifndef	_exc
#define	_exc

/* Module exc */

#include <mach/kern_return.h>
#include <mach/port.h>
#include <mach/message.h>

#ifndef	mig_external
#define mig_external extern
#endif

#include <mach/std_types.h>

/* Routine exception_raise */
mig_external kern_return_t exception_raise (
	port_t exception_port,
	port_t clear_port,
	port_t thread,
	port_t task,
	int exception,
	int code,
	int subcode);

#endif	_exc
