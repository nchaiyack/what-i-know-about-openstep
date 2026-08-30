#ifndef _DYLD_DEBUG_
#define _DYLD_DEBUG_

#import <mach/mach.h>
/*
 * The dyld debugging API.
 */
enum dyld_debug_return {
    DYLD_SUCCESS,
    DYLD_INCONSISTENT_DATA,
    DYLD_INVALID_ARGUMENTS,
    DYLD_FAILURE
};

struct dyld_debug_module {
    struct mach_header *header;
    unsigned long vmaddr_slide;
    unsigned long module_index;
};

enum dyld_event_type {
    DYLD_IMAGE_ADDED,
    DYLD_MODULE_BOUND,
    DYLD_MODULE_REMOVED,
    DYLD_MODULE_REPLACED,
    DYLD_PAST_EVENTS_END
};

struct dyld_event {
    enum dyld_event_type type;
    struct dyld_debug_module arg[2];
};

extern enum dyld_debug_return _dyld_debug_defining_module(
    task_t target_task,
    unsigned long send_timeout,
    unsigned long rcv_timeout,
    boolean_t inconsistent_data_ok,
    char *name,
    struct dyld_debug_module *module);

extern enum dyld_debug_return _dyld_debug_is_module_bound(
    task_t target_task,
    unsigned long send_timeout,
    unsigned long rcv_timeout,
    boolean_t inconsistent_data_ok,
    struct dyld_debug_module module,
    boolean_t *bound);

extern enum dyld_debug_return _dyld_debug_bind_module(
    task_t target_task,
    unsigned long send_timeout,
    unsigned long rcv_timeout,
    boolean_t inconsistent_data_ok,
    struct dyld_debug_module module);

extern enum dyld_debug_return _dyld_debug_module_name(
    task_t target_task,
    unsigned long send_timeout,
    unsigned long rcv_timeout,
    boolean_t inconsistent_data_ok,
    struct dyld_debug_module module,
    char **image_name,
    unsigned long *image_nameCnt,
    char **module_name,
    unsigned long *module_nameCnt);

extern enum dyld_debug_return _dyld_debug_subscribe_to_events(
    task_t target_task,
    unsigned long send_timeout,
    unsigned long rcv_timeout,
    boolean_t inconsistent_data_ok,
    void (*dyld_event_routine)(struct dyld_event event));

/*
 * _dyld_debug_add_event_subscriber() uses the mig interface functions below
 * to dispatch the dyld event messages from the subscriber port specified.
 */
extern enum dyld_debug_return _dyld_debug_add_event_subscriber(
    task_t target_task,
    unsigned long send_timeout,
    unsigned long rcv_timeout,
    boolean_t inconsistent_data_ok,
    port_t subscriber);
/*
 * These structures should be produced by mig(1) from the mig generated files
 * but they are not.  These are really only needed so the correct size of the
 * request and reply messages can be allocated.
 */
struct _dyld_event_message_request {
    msg_header_t head;
    msg_type_t eventType;
    struct dyld_event event;
};
struct _dyld_event_message_reply {
    msg_header_t head;
    msg_type_t RetCodeType;
    kern_return_t RetCode;
};
#ifndef	mig_internal
/*
 * _dyld_event_server() is the mig generated routine to dispatch dyld event
 * messages.
 */
extern boolean_t _dyld_event_server(
    struct _dyld_event_message_request *request,
    struct _dyld_event_message_reply *reply);
#endif
#ifndef SHLIB
/*
 * _dyld_event_server_callback() is the routine called by _dyld_event_server()
 * that must be written by users of _dyld_event_server().
 */
extern void _dyld_event_server_callback(
    port_t subscriber,
    struct dyld_event event);
#endif

/*
 * This is the state of the target task while we are sending a message to it.
 */
struct _dyld_debug_task_state {
    port_t	   debug_port;
    thread_t       debug_thread;
    unsigned int   debug_thread_resume_count;
    unsigned int   task_resume_count;
    thread_array_t threads;
    unsigned int   thread_count;
};

/*
 * _dyld_debug_make_runnable() is called before sending messages to the
 * dynamic link editor.  Basically it assures that the debugging
 * thread is the only runnable thread in the task to receive the
 * message.  It also assures that the debugging thread is indeed
 * runnable if it was suspended.  The function will make sure each 
 * thread in the remote task is suspended and resumed the same number
 * of times, so in the end the suspend count of each individual thread
 * is the same.
 */
extern enum dyld_debug_return _dyld_debug_make_runnable(
    task_t target_task,
    struct _dyld_debug_task_state *state);

/*
 * _dyld_debug_restore_runnable() is called after sending messages to the
 * dynamic link editor.  It undoes what _dyld_debug_make_runnable() did to the
 * task and put it back the way it was.
 */
extern enum dyld_debug_return _dyld_debug_restore_runnable(
    task_t target_task,
    struct _dyld_debug_task_state *state);

#endif /* _DYLD_DEBUG_ */
