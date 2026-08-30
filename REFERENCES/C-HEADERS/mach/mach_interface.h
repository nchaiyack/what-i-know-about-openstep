#ifndef	_mach
#define	_mach

/* Module mach */

#include <mach/kern_return.h>
#include <mach/port.h>
#include <mach/message.h>

#ifndef	mig_external
#define mig_external extern
#endif

#include <mach/std_types.h>
#include <mach/mach_types.h>

/* Routine task_create */
mig_external kern_return_t task_create (
	task_t target_task,
	boolean_t inherit_memory,
	task_t *child_task);

/* Routine task_terminate */
mig_external kern_return_t task_terminate (
	task_t target_task);

/* Routine task_threads */
mig_external kern_return_t task_threads (
	task_t target_task,
	thread_array_t *thread_list,
	unsigned int *thread_listCnt);

/* Routine thread_terminate */
mig_external kern_return_t thread_terminate (
	thread_t target_thread);

/* Routine vm_allocate */
mig_external kern_return_t vm_allocate (
	vm_task_t target_task,
	vm_address_t *address,
	vm_size_t size,
	boolean_t anywhere);

/* Routine vm_deallocate */
mig_external kern_return_t vm_deallocate (
	vm_task_t target_task,
	vm_address_t address,
	vm_size_t size);

/* Routine vm_protect */
mig_external kern_return_t vm_protect (
	vm_task_t target_task,
	vm_address_t address,
	vm_size_t size,
	boolean_t set_maximum,
	vm_prot_t new_protection);

/* Routine vm_inherit */
mig_external kern_return_t vm_inherit (
	vm_task_t target_task,
	vm_address_t address,
	vm_size_t size,
	vm_inherit_t new_inheritance);

/* Routine vm_read */
mig_external kern_return_t vm_read (
	vm_task_t target_task,
	vm_address_t address,
	vm_size_t size,
	pointer_t *data,
	unsigned int *dataCnt);

/* Routine vm_write */
mig_external kern_return_t vm_write (
	vm_task_t target_task,
	vm_address_t address,
	pointer_t data,
	unsigned int dataCnt);

/* Routine vm_copy */
mig_external kern_return_t vm_copy (
	vm_task_t target_task,
	vm_address_t source_address,
	vm_size_t size,
	vm_address_t dest_address);

/* Routine vm_region */
mig_external kern_return_t vm_region (
	vm_task_t target_task,
	vm_address_t *address,
	vm_size_t *size,
	vm_prot_t *protection,
	vm_prot_t *max_protection,
	vm_inherit_t *inheritance,
	boolean_t *is_shared,
	memory_object_name_t *object_name,
	vm_offset_t *offset);

/* Routine vm_statistics */
mig_external kern_return_t vm_statistics (
	vm_task_t target_task,
	vm_statistics_data_t *vm_stats);

/* Routine task_by_unix_pid */
mig_external kern_return_t task_by_unix_pid (
	task_t target_task,
	int process_id,
	task_t *result_task);

/* Routine unix_pid */
mig_external kern_return_t unix_pid (
	task_t target_task,
	int *process_id);

/* Routine netipc_listen */
mig_external kern_return_t netipc_listen (
	port_t request_port,
	int src_addr,
	int dst_addr,
	int src_port,
	int dst_port,
	int protocol,
	port_t ipc_port);

/* Routine netipc_ignore */
mig_external kern_return_t netipc_ignore (
	port_t request_port,
	port_t ipc_port);

/* Routine xxx_host_info */
mig_external kern_return_t xxx_host_info (
	port_t target_task,
	machine_info_data_t *info);

/* Routine xxx_slot_info */
mig_external kern_return_t xxx_slot_info (
	task_t target_task,
	int slot,
	machine_slot_data_t *info);

/* Routine xxx_cpu_control */
mig_external kern_return_t xxx_cpu_control (
	task_t target_task,
	int cpu,
	boolean_t running);

/* Routine task_suspend */
mig_external kern_return_t task_suspend (
	task_t target_task);

/* Routine task_resume */
mig_external kern_return_t task_resume (
	task_t target_task);

/* Routine task_get_special_port */
mig_external kern_return_t task_get_special_port (
	task_t task,
	int which_port,
	port_t *special_port);

/* Routine task_set_special_port */
mig_external kern_return_t task_set_special_port (
	task_t task,
	int which_port,
	port_t special_port);

/* Routine task_info */
mig_external kern_return_t task_info (
	task_t target_task,
	int flavor,
	task_info_t task_info_out,
	unsigned int *task_info_outCnt);

/* Routine thread_create */
mig_external kern_return_t thread_create (
	task_t parent_task,
	thread_t *child_thread);

/* Routine thread_suspend */
mig_external kern_return_t thread_suspend (
	thread_t target_thread);

/* Routine thread_resume */
mig_external kern_return_t thread_resume (
	thread_t target_thread);

/* Routine thread_abort */
mig_external kern_return_t thread_abort (
	thread_t target_thread);

/* Routine thread_get_state */
mig_external kern_return_t thread_get_state (
	thread_t target_thread,
	int flavor,
	thread_state_t old_state,
	unsigned int *old_stateCnt);

/* Routine thread_set_state */
mig_external kern_return_t thread_set_state (
	thread_t target_thread,
	int flavor,
	thread_state_t new_state,
	unsigned int new_stateCnt);

/* Routine thread_get_special_port */
mig_external kern_return_t thread_get_special_port (
	thread_t thread,
	int which_port,
	port_t *special_port);

/* Routine thread_set_special_port */
mig_external kern_return_t thread_set_special_port (
	thread_t thread,
	int which_port,
	port_t special_port);

/* Routine thread_info */
mig_external kern_return_t thread_info (
	thread_t target_thread,
	int flavor,
	thread_info_t thread_info_out,
	unsigned int *thread_info_outCnt);

/* Routine port_names */
mig_external kern_return_t port_names (
	task_t task,
	port_name_array_t *port_names_p,
	unsigned int *port_names_pCnt,
	port_type_array_t *port_types,
	unsigned int *port_typesCnt);

/* Routine port_type */
mig_external kern_return_t port_type (
	task_t task,
	port_name_t port_name,
	port_type_t *port_type_p);

/* Routine port_rename */
mig_external kern_return_t port_rename (
	task_t task,
	port_name_t old_name,
	port_name_t new_name);

/* Routine port_allocate */
mig_external kern_return_t port_allocate (
	task_t task,
	port_name_t *port_name);

/* Routine port_deallocate */
mig_external kern_return_t port_deallocate (
	task_t task,
	port_name_t port_name);

/* Routine port_set_backlog */
mig_external kern_return_t port_set_backlog (
	task_t task,
	port_name_t port_name,
	int backlog);

/* Routine port_status */
mig_external kern_return_t port_status (
	task_t task,
	port_name_t port_name,
	port_set_name_t *enabled,
	int *num_msgs,
	int *backlog,
	boolean_t *ownership,
	boolean_t *receive_rights);

/* Routine port_set_allocate */
mig_external kern_return_t port_set_allocate (
	task_t task,
	port_set_name_t *set_name);

/* Routine port_set_deallocate */
mig_external kern_return_t port_set_deallocate (
	task_t task,
	port_set_name_t set_name);

/* Routine port_set_add */
mig_external kern_return_t port_set_add (
	task_t task,
	port_set_name_t set_name,
	port_name_t port_name);

/* Routine port_set_remove */
mig_external kern_return_t port_set_remove (
	task_t task,
	port_name_t port_name);

/* Routine port_set_status */
mig_external kern_return_t port_set_status (
	task_t task,
	port_set_name_t set_name,
	port_name_array_t *members,
	unsigned int *membersCnt);

/* Routine port_insert_send */
mig_external kern_return_t port_insert_send (
	task_t task,
	port_t my_port,
	port_name_t his_name);

/* Routine port_extract_send */
mig_external kern_return_t port_extract_send (
	task_t task,
	port_name_t his_name,
	port_t *his_port);

/* Routine port_insert_receive */
mig_external kern_return_t port_insert_receive (
	task_t task,
	port_all_t my_port,
	port_name_t his_name);

/* Routine port_extract_receive */
mig_external kern_return_t port_extract_receive (
	task_t task,
	port_name_t his_name,
	port_all_t *his_port);

/* Routine port_set_backup */
mig_external kern_return_t port_set_backup (
	task_t task,
	port_name_t port_name,
	port_t backup,
	port_t *previous);

/* Routine vm_machine_attribute */
mig_external kern_return_t vm_machine_attribute (
	vm_task_t target_task,
	vm_address_t address,
	vm_size_t size,
	vm_machine_attribute_t attribute,
	vm_machine_attribute_val_t *value);

/* Routine vm_synchronize */
mig_external kern_return_t vm_synchronize (
	vm_task_t target_task,
	vm_address_t address,
	vm_size_t size);

/* Routine vm_set_policy */
mig_external kern_return_t vm_set_policy (
	vm_task_t target_task,
	vm_address_t address,
	vm_size_t size,
	int policy);

/* Routine vm_deactivate */
mig_external kern_return_t vm_deactivate (
	vm_task_t target_task,
	vm_address_t address,
	vm_size_t size,
	int when);

#endif	_mach
