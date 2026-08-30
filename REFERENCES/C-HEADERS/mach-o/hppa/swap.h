#import <architecture/byte_order.h>
#import <mach/hppa/thread_status.h>

extern void swap_hppa_integer_thread_state(
    struct hp_pa_integer_thread_state *regs,
    enum NXByteOrder target_byte_order);

extern void swap_hppa_frame_thread_state(
  struct hp_pa_frame_thread_state *frame,
  enum NXByteOrder target_byte_order);
