#ifndef INCLUDED_CILKTOOL_DOT_H
#define INCLUDED_CILKTOOL_DOT_H

typedef struct __cilkrts_stack_frame __cilkrts_stack_frame;

// Function properties
const unsigned int IS_MAIN = 0x1;

#ifdef __cplusplus
#define EXTERN_C extern "C" {
#define EXTERN_C_END }
#else
#define EXTERN_C
#define EXTERN_C_END
#endif

EXTERN_C

void cilk_tool_init(void);
void cilk_tool_destroy(void);
void cilk_tool_print(void);

void cilk_tool_c_function_enter(unsigned int prop, void* this_fn, void* rip);
void cilk_tool_c_function_leave(void* rip);

void cilk_enter_begin (unsigned int prop, __cilkrts_stack_frame* sf, void* this_fn, void* rip);
void cilk_enter_helper_begin(__cilkrts_stack_frame* sf, void* this_fn, void* rip);
void cilk_enter_end (__cilkrts_stack_frame* sf, void* rsp);
void cilk_spawn_prepare (__cilkrts_stack_frame* sf);
void cilk_spawn_or_continue (int in_continuation);
void cilk_detach_begin (__cilkrts_stack_frame* parent);
void cilk_detach_end (void);
void cilk_sync_begin (__cilkrts_stack_frame* sf);
void cilk_sync_end (__cilkrts_stack_frame* sf);
void cilk_leave_begin (__cilkrts_stack_frame *sf);
void cilk_leave_end (void);

EXTERN_C_END

#endif  // INCLUDED_CILKTOOL_DOT_H
