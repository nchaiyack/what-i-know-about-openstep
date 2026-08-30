/*
 * Copyright (c) 1993 NeXT Computer, Inc.
 *
 * HPPA	External thread state.
 *
 */

#ifndef	_HPPA_THREAD_STATE_ 
#define	_HPPA_THREAD_STATE_

#import <mach/hppa/boolean.h>

#define	HPPA_INTEGER_THREAD_STATE     1
#define	HPPA_FRAME_THREAD_STATE     2
#define	HPPA_FP_THREAD_STATE     3
#define HPPA_MISC_THREAD_STATE     4

/*
 * Flow control information that can
 * be changed from user state (with
 * some restrictions on psw).
 */
struct hp_pa_frame_thread_state {
	unsigned long	ts_pcsq_front;	/* instruction address space front */
	unsigned long	ts_pcsq_back;	/* instruction address space back */
	unsigned long	ts_pcoq_front;	/* instruction offset space front */
	unsigned long	ts_pcoq_back;	/* instruction offset space back */
	unsigned long	ts_psw;		/* process status word */
	unsigned long	ts_unaligned_faults;	/* number of unaligned data references READ-ONLY */
	unsigned long	ts_fault_address;	/* address of failing page fault READ-ONLY */
/*
 * A step range is a range of address that
 * will be executed with out generating a single
 * step event. If both values are 0 no stepping
 * will occur. Otherwise the program will run while:
 *
 *	if (step_range_start <= step_range_stop)
 *		pcoq0 >= step_range_start && pcoq0 < step_range_stop 
 *	if (step_range_start > step_range_stop)
 *		pcoq0 < step_range_stop && pcoq0 >= step_range_start 
 *
 * notice that setting step_range_start and step_range_stop to the
 * same non-zero value will execute only one instruction due to action
 * of the pc queue. (Yes, nullified instructions count)
 */
	unsigned long	ts_step_range_start;
	unsigned long	ts_step_range_stop;

	/* Generate an exception when OS assists with an alignment fault */
	boolean_t	ts_alignment_trap_reflect;

	/* Generate an exception when OS assists with an FP fault */
	boolean_t	ts_execution_trap_reflect;
};

/*
 * The unsigned longeger state that may be changed by any
 * process in user space.
 */
typedef struct hp_pa_integer_thread_state {
	unsigned long	ts_gr1;		/* the user's general registers */
	unsigned long	ts_gr2;
	unsigned long	ts_gr3;
	unsigned long	ts_gr4;
	unsigned long	ts_gr5;
	unsigned long	ts_gr6;
	unsigned long	ts_gr7;
	unsigned long	ts_gr8;
	unsigned long	ts_gr9;
	unsigned long	ts_gr10;
	unsigned long	ts_gr11;
	unsigned long	ts_gr12;
	unsigned long	ts_gr13;
	unsigned long	ts_gr14;
	unsigned long	ts_gr15;
	unsigned long	ts_gr16;
	unsigned long	ts_gr17;
	unsigned long	ts_gr18;
	unsigned long	ts_gr19;
	unsigned long	ts_gr20;
	unsigned long	ts_gr21;
	unsigned long	ts_gr22;
	unsigned long	ts_gr23;
	unsigned long	ts_gr24;
	unsigned long	ts_gr25;
	unsigned long	ts_gr26;
	unsigned long	ts_gr27;
	unsigned long	ts_gr28;
	unsigned long	ts_gr29;
	unsigned long	ts_gr30;
	unsigned long	ts_gr31;
	unsigned long	ts_sr0;		/* the user's space registgers */
	unsigned long	ts_sr1;
	unsigned long	ts_sr2;
	unsigned long	ts_sr3;
	unsigned long	ts_sar;		/* the user's shift amount register */
} hp_pa_integer_thread_state_t;

/*
 * The floating point state that may be changed by any
 * process in user space.
 */
typedef struct hp_pa_fp_thread_state {
	double	ts_fp0;		/* all of the execution unit registers */
	double	ts_fp1;
	double	ts_fp2;
	double	ts_fp3;
	double	ts_fp4;
	double	ts_fp5;
	double	ts_fp6;
	double	ts_fp7;
	double	ts_fp8;
	double	ts_fp9;
	double	ts_fp10;
	double	ts_fp11;
	double	ts_fp12;
	double	ts_fp13;
	double	ts_fp14;
	double	ts_fp15;
	double	ts_fp16;
	double	ts_fp17;
	double	ts_fp18;
	double	ts_fp19;
	double	ts_fp20;
	double	ts_fp21;
	double	ts_fp22;
	double	ts_fp23;
	double	ts_fp24;
	double	ts_fp25;
	double	ts_fp26;
	double	ts_fp27;
	double	ts_fp28;
	double	ts_fp29;
	double	ts_fp30;
	double	ts_fp31;
} hp_pa_fp_thread_state_t;

/*
 * Everything else from pcb_entry_state.
 */
typedef struct hp_pa_misc_thread_state {
	unsigned long	ts_sr4;	
	unsigned long	ts_sr5;
	unsigned long	ts_sr6;
	unsigned long	ts_sr7;
	unsigned long	ts_recovery_counter;
	unsigned long	ts_eiem;
	unsigned long	ts_iir;
	unsigned long	ts_isr;
	unsigned long	ts_argument[6];
	unsigned long	ts_return_pointer;
	unsigned long	ts_static_link;
	unsigned long	ts_clean_up;
	unsigned long	ts_stub_return_pointer;
	unsigned long	ts_previous_stack;
} hp_pa_misc_thread_state_t;

#define	HPPA_INTEGER_THREAD_STATE_COUNT (sizeof(struct hp_pa_integer_thread_state) / sizeof(unsigned long))
#define	HPPA_FRAME_THREAD_STATE_COUNT (sizeof(struct hp_pa_frame_thread_state) / sizeof(unsigned long))
#define	HPPA_FP_THREAD_STATE_COUNT (sizeof(struct hp_pa_fp_thread_state) / sizeof(unsigned long))

#endif	/* _HPPA_THREAD_STATE_ */
