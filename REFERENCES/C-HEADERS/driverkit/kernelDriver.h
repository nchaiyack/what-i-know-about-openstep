/* 	Copyright (c) 1991 NeXT Computer, Inc.  All rights reserved. 
 *
 * kernelDriver.h - kernel-only driverkit functions.
 *
 * HISTORY
 * 12-Jul-91    Doug Mitchell at NeXT
 *      Created. 
 */

#ifdef	KERNEL

#import <objc/objc.h>
#import <driverkit/driverTypes.h>
#import <mach/mach_types.h>
#import <sys/buf.h>

/*
 * The functions defined here are not RPC's; they are functions available
 * only to drivers in the kernel.
 */
 
/*
 * Get id of specified IODeviceName.  Returns IO_R_NOTATTACHED if 
 * deviceName not found, else returns IO_R_SUCCESS.
 */
IOReturn IOGetObjectForDeviceName(
	IOString deviceName,
	id *deviceId);				// returned

/*
 * Returns the kernel's vm_task_t.
 */
vm_task_t IOVmTaskSelf();

/*
 * Returns the current task's vm_task_t.
 */
vm_task_t IOVmTaskCurrent();

/*
 * Returns vm_task_t associated with a struct buf. 
 */
vm_task_t IOVmTaskForBuf(struct buf *buffer);

/*
 * Set the current thread's UNIX errno.
 */
void IOSetUNIXError(int errno);

/* 
 * Convert between a port in a loadable kernel server's IPC space, an 
 * I/O task port, and a kernel internal port. 
 */
typedef enum {
	IO_Kernel,			// a kernel internal port
	IO_KernelIOTask,		// a port in the kernel I/O task
	IO_CurrentTask			// a port in a loadable kernel server
} IOIPCSpace;

/*
 * Returns PORT_NULL on error.
 */
port_t IOConvertPort(port_t inPort,	// to be converted
	IOIPCSpace from,		// IPC space of inPort
	IOIPCSpace to);			// IPC space of returned port

/*
 * Obtain the IOTask version of host_priv_self() (the privileged host port).
 */
port_t IOHostPrivSelf();

/*
 * Find a physical address (if any) for the specified virtual address.
 * Returns IO_R_INVALID_ARG if no virtual-to-physical mapping exists,
 * else returns IO_R_SUCCESS.
 * For IOTask virtual addresses, use IOVmTaskSelf() for the 'task'
 * argument. 
 * This function may block on some architectures.
 */
IOReturn IOPhysicalFromVirtual(vm_task_t task, 
	vm_address_t virtualAddress,
	unsigned *physicalAddress);

/*
 * Create a mapping in the IOTask address map
 * for the specified physical region.  Assumes
 * that the physical memory is already wired.
 */
IOReturn
IOMapPhysicalIntoIOTask(
    unsigned		physicalAddress,
    unsigned		length,
    vm_address_t	*virtualAddress);

/*
 * Destroy a mapping created by
 * IOTaskCreateVirtualFromPhysical()
 */
IOReturn
IOUnmapPhysicalFromIOTask(
    vm_address_t	virtualAddress,
    unsigned		length);

#endif	KERNEL
