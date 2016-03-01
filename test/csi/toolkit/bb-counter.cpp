#include <stdio.h>
#include <stdint.h>

extern "C" {

void __csi_bb_entry(uint32_t module_id, uint32_t bb_id) {
    printf("enter BB %d:%d\n", module_id, bb_id);
}

void __csi_bb_exit() {
    printf("exit BB\n");
}

}
