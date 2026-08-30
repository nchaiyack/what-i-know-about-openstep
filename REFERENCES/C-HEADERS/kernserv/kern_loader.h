#ifndef	_kern_loader_kern_loader
#define	_kern_loader_kern_loader

/* Module kern_loader */

#include <mach/kern_return.h>
#include <mach/port.h>
#include <mach/message.h>

#ifndef	mig_external
#define mig_external extern
#endif

#include <mach/std_types.h>
#include <mach/mach_types.h>
#include <kernserv/kern_loader_types.h>

/* Routine kern_loader_abort */
mig_external kern_return_t kern_loader_abort (
	port_t loader_port,
	port_t priv_port,
	boolean_t restart);

/* Routine kern_loader_load_server */
mig_external kern_return_t kern_loader_load_server (
	port_t loader_port,
	server_name_t server_name);

/* Routine kern_loader_unload_server */
mig_external kern_return_t kern_loader_unload_server (
	port_t loader_port,
	port_t task_port,
	server_name_t server_name);

/* Routine kern_loader_add_server */
mig_external kern_return_t kern_loader_add_server (
	port_t loader_port,
	port_t task_port,
	server_reloc_t server_reloc);

/* Routine kern_loader_delete_server */
mig_external kern_return_t kern_loader_delete_server (
	port_t loader_port,
	port_t task_port,
	server_name_t server_name);

/* Routine kern_loader_server_task_port */
mig_external kern_return_t kern_loader_server_task_port (
	port_t loader_port,
	port_t task_port,
	server_name_t server_name,
	port_t *server_task_port);

/* Routine kern_loader_server_com_port */
mig_external kern_return_t kern_loader_server_com_port (
	port_t loader_port,
	port_t task_port,
	server_name_t server_name,
	port_t *server_com_port);

/* SimpleRoutine kern_loader_status_port */
mig_external kern_return_t kern_loader_status_port (
	port_t loader_port,
	port_t listen_port);

/* SimpleRoutine kern_loader_ping */
mig_external kern_return_t kern_loader_ping (
	port_t loader_port,
	port_t ping_port,
	int id);

/* Routine kern_loader_log_level */
mig_external kern_return_t kern_loader_log_level (
	port_t loader_port,
	port_t server_com_port,
	int log_level);

/* Routine kern_loader_get_log */
mig_external kern_return_t kern_loader_get_log (
	port_t loader_port,
	port_t server_com_port,
	port_t reply_port);

/* Routine kern_loader_server_list */
mig_external kern_return_t kern_loader_server_list (
	port_t loader_port,
	server_name_array_t *servers,
	unsigned int *serversCnt);

/* Routine kern_loader_server_info_old */
mig_external kern_return_t kern_loader_server_info_old (
	port_t loader_port,
	port_t task_port,
	server_name_t server_name,
	server_state_t *server_state,
	vm_address_t *load_address,
	vm_size_t *load_size,
	server_reloc_t relocatable,
	server_reloc_t loadable,
	port_name_array_t *port_list,
	unsigned int *port_listCnt,
	port_name_string_array_t *names,
	unsigned int *namesCnt,
	boolean_array_t *advertised,
	unsigned int *advertisedCnt);

/* Routine kern_loader_server_info */
mig_external kern_return_t kern_loader_server_info (
	port_t loader_port,
	port_t task_port,
	server_name_t server_name,
	server_state_t *server_state,
	vm_address_t *load_address,
	vm_size_t *load_size,
	server_reloc_t relocatable,
	server_reloc_t loadable,
	port_array_t *port_list,
	unsigned int *port_listCnt,
	port_name_string_array_t *names,
	unsigned int *namesCnt,
	boolean_array_t *advertised,
	unsigned int *advertisedCnt);

#endif	_kern_loader_handler
