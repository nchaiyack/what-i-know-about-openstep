#ifndef	_kern_serv_kern_serv
#define	_kern_serv_kern_serv

/* Module kern_serv */

#include <mach/kern_return.h>
#include <mach/port.h>
#include <mach/message.h>

#ifndef	mig_external
#define mig_external extern
#endif

#include <mach/std_types.h>
#include <kernserv/kern_server_types.h>

/* Routine kern_serv_instance_loc */
mig_external kern_return_t kern_serv_instance_loc (
	port_t server_port,
	vm_address_t instance_loc);

/* Routine kern_serv_boot_port */
mig_external kern_return_t kern_serv_boot_port (
	port_t server_port,
	port_t boot_port);

/* Routine kern_serv_wire_range */
mig_external kern_return_t kern_serv_wire_range (
	port_t server_port,
	vm_address_t addr,
	vm_size_t size);

/* Routine kern_serv_unwire_range */
mig_external kern_return_t kern_serv_unwire_range (
	port_t server_port,
	vm_address_t addr,
	vm_size_t size);

/* Routine kern_serv_port_proc */
mig_external kern_return_t kern_serv_port_proc (
	port_t server_port,
	port_all_t port,
	port_map_proc_t proc,
	int argument);

/* SimpleRoutine kern_serv_port_death_proc */
mig_external kern_return_t kern_serv_port_death_proc (
	port_t server_port,
	port_death_proc_t proc);

/* Routine kern_serv_call_proc */
mig_external kern_return_t kern_serv_call_proc (
	port_t server_port,
	call_proc_t proc,
	int argument);

/* SimpleRoutine kern_serv_shutdown */
mig_external kern_return_t kern_serv_shutdown (
	port_t server_port);

/* SimpleRoutine kern_serv_log_level */
mig_external kern_return_t kern_serv_log_level (
	port_t server_port,
	int log_level);

/* SimpleRoutine kern_serv_get_log */
mig_external kern_return_t kern_serv_get_log (
	port_t server_port,
	port_t reply_port);

/* Routine kern_serv_port_serv */
mig_external kern_return_t kern_serv_port_serv (
	port_t server_port,
	port_all_t port,
	port_map_proc_t proc,
	int argument);

/* Routine kern_serv_version */
mig_external kern_return_t kern_serv_version (
	port_t server_port,
	int version);

/* Routine kern_serv_load_objc */
mig_external kern_return_t kern_serv_load_objc (
	port_t server_port,
	vm_address_t addr);

#endif	_kern_serv_handler
