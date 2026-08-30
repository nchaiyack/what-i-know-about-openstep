#ifndef	_mach_host
#define	_mach_host

/* Module mach_host */

#include <mach/kern_return.h>
#include <mach/port.h>
#include <mach/message.h>

#ifndef	mig_external
#define mig_external extern
#endif

#include <mach/std_types.h>
#include <mach/mach_types.h>

/* Routine host_processors */
mig_external kern_return_t host_processors (
	host_priv_t host_priv,
	processor_array_t *processor_list,
	unsigned int *processor_listCnt);

/* Routine host_info */
mig_external kern_return_t host_info (
	host_t host,
	int flavor,
	host_info_t host_info_out,
	unsigned int *host_info_outCnt);

/* Routine processor_info */
mig_external kern_return_t processor_info (
	processor_t processor,
	int flavor,
	host_t *host,
	processor_info_t processor_info_out,
	unsigned int *processor_info_outCnt);

/* Routine processor_start */
mig_external kern_return_t processor_start (
	processor_t processor);

/* Routine processor_exit */
mig_external kern_return_t processor_exit (
	processor_t processor);

/* Routine processor_control */
mig_external kern_return_t processor_control (
	processor_t processor,
	processor_info_t processor_cmd,
	unsigned int processor_cmdCnt);

/* Routine processor_set_default */
mig_external kern_return_t processor_set_default (
	host_t host,
	processor_set_name_t *default_set);

/* Routine processor_set_create */
mig_external kern_return_t processor_set_create (
	host_t host,
	processor_set_t *new_set,
	processor_set_name_t *new_name);

/* Routine processor_set_destroy */
mig_external kern_return_t processor_set_destroy (
	processor_set_t set);

/* Routine processor_set_info */
mig_external kern_return_t processor_set_info (
	processor_set_name_t set_name,
	int flavor,
	host_t *host,
	processor_set_info_t info_out,
	unsigned int *info_outCnt);

/* Routine processor_assign */
mig_external kern_return_t processor_assign (
	processor_t processor,
	processor_set_t new_set,
	boolean_t wait);

/* Routine processor_get_assignment */
mig_external kern_return_t processor_get_assignment (
	processor_t processor,
	processor_set_name_t *assigned_set);

/* Routine thread_assign */
mig_external kern_return_t thread_assign (
	thread_t thread,
	processor_set_t new_set);

/* Routine thread_assign_default */
mig_external kern_return_t thread_assign_default (
	thread_t thread);

/* Routine thread_get_assignment */
mig_external kern_return_t thread_get_assignment (
	thread_t thread,
	processor_set_name_t *assigned_set);

/* Routine task_assign */
mig_external kern_return_t task_assign (
	task_t task,
	processor_set_t new_set,
	boolean_t assign_threads);

/* Routine task_assign_default */
mig_external kern_return_t task_assign_default (
	task_t task,
	boolean_t assign_threads);

/* Routine task_get_assignment */
mig_external kern_return_t task_get_assignment (
	task_t task,
	processor_set_name_t *assigned_set);

/* Routine host_kernel_version */
mig_external kern_return_t host_kernel_version (
	host_t host,
	kernel_version_t kernel_version);

/* Routine thread_priority */
mig_external kern_return_t thread_priority (
	thread_t thread,
	int priority,
	boolean_t set_max);

/* Routine thread_max_priority */
mig_external kern_return_t thread_max_priority (
	thread_t thread,
	processor_set_t processor_set,
	int max_priority);

/* Routine task_priority */
mig_external kern_return_t task_priority (
	task_t task,
	int priority,
	boolean_t change_threads);

/* Routine processor_set_max_priority */
mig_external kern_return_t processor_set_max_priority (
	processor_set_t processor_set,
	int max_priority,
	boolean_t change_threads);

/* Routine thread_policy */
mig_external kern_return_t thread_policy (
	thread_t thread,
	int policy,
	int data);

/* Routine processor_set_policy_enable */
mig_external kern_return_t processor_set_policy_enable (
	processor_set_t processor_set,
	int policy);

/* Routine processor_set_policy_disable */
mig_external kern_return_t processor_set_policy_disable (
	processor_set_t processor_set,
	int policy,
	boolean_t change_threads);

/* Routine processor_set_tasks */
mig_external kern_return_t processor_set_tasks (
	processor_set_t processor_set,
	task_array_t *task_list,
	unsigned int *task_listCnt);

/* Routine processor_set_threads */
mig_external kern_return_t processor_set_threads (
	processor_set_t processor_set,
	thread_array_t *thread_list,
	unsigned int *thread_listCnt);

/* Routine host_processor_sets */
mig_external kern_return_t host_processor_sets (
	host_t host,
	processor_set_name_array_t *processor_sets,
	unsigned int *processor_setsCnt);

/* Routine host_processor_set_priv */
mig_external kern_return_t host_processor_set_priv (
	host_priv_t host_priv,
	processor_set_name_t set_name,
	processor_set_t *set);

/* Routine thread_depress_abort */
mig_external kern_return_t thread_depress_abort (
	thread_t thread);

/* Routine host_set_time */
mig_external kern_return_t host_set_time (
	host_priv_t host_priv,
	time_value_t new_time);

/* Routine host_adjust_time */
mig_external kern_return_t host_adjust_time (
	host_priv_t host_priv,
	time_value_t new_adjustment,
	time_value_t *old_adjustment);

/* Routine host_get_time */
mig_external kern_return_t host_get_time (
	host_t host,
	time_value_t *current_time);

#endif	_mach_host
