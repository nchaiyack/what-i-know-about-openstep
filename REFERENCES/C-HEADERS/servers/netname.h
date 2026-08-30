#ifndef	_netname
#define	_netname

/* Module netname */

#include <mach/kern_return.h>
#include <mach/port.h>
#include <mach/message.h>

#ifndef	mig_external
#define mig_external extern
#endif

#include <servers/netname_defs.h>

/* Routine netname_check_in */
mig_external kern_return_t netname_check_in (
	port_t server_port,
	netname_name_t port_name,
	port_t signature,
	port_t port_id);

/* Routine netname_look_up */
mig_external kern_return_t netname_look_up (
	port_t server_port,
	netname_name_t host_name,
	netname_name_t port_name,
	port_t *port_id);

/* Routine netname_check_out */
mig_external kern_return_t netname_check_out (
	port_t server_port,
	netname_name_t port_name,
	port_t signature);

/* Routine netname_version */
mig_external kern_return_t netname_version (
	port_t server_port,
	netname_name_t version);

#endif	_netname
