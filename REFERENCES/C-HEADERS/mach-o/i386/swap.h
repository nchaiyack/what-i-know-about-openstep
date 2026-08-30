#import <architecture/byte_order.h>
#import <mach/i386/thread_status.h>

extern void swap_i386_thread_state(
    i386_thread_state_t *cpu,
    enum NXByteOrder target_byte_order);

extern void swap_i386_thread_fpstate(
    i386_thread_fpstate_t *fpu,
    enum NXByteOrder target_byte_order);

extern void swap_i386_thread_exceptstate(
    i386_thread_exceptstate_t *exc,
    enum NXByteOrder target_byte_order);

extern void swap_i386_thread_cthreadstate(
    i386_thread_cthreadstate_t *user,
    enum NXByteOrder target_byte_order);
