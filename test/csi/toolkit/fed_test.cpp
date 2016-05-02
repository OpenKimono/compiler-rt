#include "csi.h"
#include "../csirt/csirt.h"
#include <stdio.h>

static inline void print_call(const char *const msg, const uint64_t csi_id) {
    printf("%s:%d -- %s\n",
            __csirt_get_filename(csi_id),
            __csirt_get_line_number(csi_id),
            msg);
}

void __csi_init(const char * const name) {
    printf("__csi_init %s\n", name);
}

void __csi_unit_init(const char *const file_name,
                     const uint64_t num_inst) {
    printf("__csi_unit_init: %s, %lu inst\n", file_name, num_inst);
}

void __csi_before_load(const uint64_t csi_id,
                       const void *addr,
                       const uint32_t num_bytes,
                       const uint64_t prop) {
    print_call("__csi_before_load", csi_id);
}

void __csi_after_load(const uint64_t csi_id,
                      const void *addr,
                      const uint32_t num_bytes,
                      const uint64_t prop) {
    print_call("__csi_after_load", csi_id);
}

void __csi_before_store(const uint64_t csi_id,
                        const void *addr,
                        const uint32_t num_bytes,
                        const uint64_t prop) {
    print_call("__csi_before_store", csi_id);
}

void __csi_after_store(const uint64_t csi_id,
                       const void *addr,
                       const uint32_t num_bytes,
                       const uint64_t prop) {
    print_call("__csi_after_store", csi_id);
}

void __csi_func_entry(const uint64_t csi_id,
                      const void * const function,
                      const void * const return_addr,
                      const char * const func_name) {
    print_call("__csi_func_entry", csi_id);
}

void __csi_func_exit(const uint64_t csi_id,
                     const void * const function,
                     const void * const return_addr,
                     const char * const func_name) {
    print_call("__csi_func_exit", csi_id);
}

void __csi_bb_entry(const uint64_t csi_id) {
    print_call("__csi_bb_entry", csi_id);
}

void __csi_bb_exit(const uint64_t csi_id) {
    print_call("__csi_bb_exit", csi_id);
}

void __csi_before_callsite(uint64_t csi_id, uint64_t func_id) {
    print_call("__csi_before_callsite", csi_id);
    if (__csirt_callsite_target_unknown(csi_id, func_id)) {
        printf("  (unknown target)\n");
    } else {
        printf("  target: %s:%d\n", __csirt_get_filename(func_id),
               __csirt_get_line_number(func_id));
    }
}
