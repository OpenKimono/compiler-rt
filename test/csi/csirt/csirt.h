#ifndef __CSIRT_H__
#define __CSIRT_H__

#include "../toolkit/csi.h"

EXTERN_C

char *__csirt_get_filename(const uint64_t csi_id);
int32_t __csirt_get_line_number(const uint64_t csi_id);

EXTERN_C_END

#endif  // __CSIRT_H__
