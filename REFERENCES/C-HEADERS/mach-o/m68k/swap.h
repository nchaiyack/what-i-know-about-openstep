#import <architecture/byte_order.h>
#import <mach/m68k/thread_status.h>

extern void swap_m68k_thread_state_regs(
    struct m68k_thread_state_regs *cpu,
    enum NXByteOrder target_byte_order);

extern void swap_m68k_thread_state_68882(
    struct m68k_thread_state_68882 *fpu,
    enum NXByteOrder target_byte_order);

extern void swap_m68k_thread_state_user_reg(
    struct m68k_thread_state_user_reg *user_reg,
    enum NXByteOrder target_byte_order);
