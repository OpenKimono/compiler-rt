#ifndef __CSIRT_H__
#define __CSIRT_H__

#include "csi.h"

char *__csi_get_filename(uint64_t csi_id);
uint32_t __csi_get_line_number(uint64_t csi_id);

#endif  // __CSIRT_H__
