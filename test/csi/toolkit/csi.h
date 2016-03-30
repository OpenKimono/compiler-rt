#ifndef __CSI_H__
#define __CSI_H__

#include <stdint.h>

#ifdef __cplusplus
#define EXTERN_C extern "C" {
#define EXTERN_C_END }
#else
#define EXTERN_C
#define EXTERN_C_END
#include <stdbool.h> // for C99 bool type
#endif

#define WEAK __attribute__((weak))

// API function signatures
EXTERN_C

WEAK void __csi_init(const char * const name,
                     const uint32_t num_units);
WEAK void __csi_unit_init(const char * const file_name,
                          const uint64_t num_basic_blocks);

WEAK void __csi_before_load(const void *addr, const uint32_t num_bytes, const uint64_t prop);
WEAK void __csi_after_load(const void *addr, const uint32_t num_bytes, const uint64_t prop);
WEAK void __csi_before_store(const void *addr, const uint32_t num_bytes, const uint64_t prop);
WEAK void __csi_after_store(const void *addr, const uint32_t num_bytes, const uint64_t prop);

WEAK void __csi_func_entry(const void * const function,
                           const void * const return_addr,
                           const char * const func_name);
WEAK void __csi_func_exit(const void * const function,
                          const void * const return_addr,
                          const char * const func_name);

WEAK void __csi_bb_entry(const uint64_t bb_id);
WEAK void __csi_bb_exit(const uint64_t bb_id);

EXTERN_C_END

#endif
