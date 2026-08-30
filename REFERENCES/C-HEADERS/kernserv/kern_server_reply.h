#ifndef	_kern_serv_kern_server_reply
#define	_kern_serv_kern_server_reply

/* Module kern_server_reply */

#include <mach/kern_return.h>
#include <mach/port.h>
#include <mach/message.h>

#ifndef	mig_external
#define mig_external extern
#endif

#include <mach/std_types.h>
#include <kernserv/kern_server_reply_types.h>

/* Routine kern_serv_panic */
mig_external kern_return_t kern_serv_panic (
	port_t boot_port,
	panic_msg_t panic_msg);

/* Routine kern_serv_section_by_name */
mig_external kern_return_t kern_serv_section_by_name (
	port_t boot_port,
	macho_header_name_t segname,
	macho_header_name_t sectname,
	vm_address_t *addr,
	vm_size_t *size);

/* SimpleRoutine kern_serv_log_data */
mig_external kern_return_t kern_serv_log_data (
	port_t log_port,
	log_entry_array_t log,
	unsigned int logCnt);

#endif	_kern_serv_kern_server_reply
