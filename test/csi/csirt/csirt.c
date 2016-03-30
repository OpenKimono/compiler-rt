#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "csirt.h"

typedef struct {
    char *filename;
    uint32_t line_number;
} fed_entry;

typedef struct {
    uint64_t num_units;
    fed_entry *entries;
} tix_entry;

static const int DEFAULT_FED_TABLE_LENGTH = 16;

#define ENTRY_OFFSET_BITS  32
#define UNIT_ID_FROM_CSI_ID(csi_id) ((csi_id) >> ENTRY_OFFSET_BITS)
#define ENTRY_OFFSET_FROM_CSI_ID(csi_id) ((csi_id) & ((1ULL << ENTRY_OFFSET_BITS) - 1))

// The sum of the num_units for each tix initialized. When a tix is initialized,
// we update their unit_base to the current value of units_seen, then add their
// number of units to units_seen, giving each tix a globally unique set of unit
// ids.
static uint64_t units_seen;

static tix_entry *fed_table;
static uint64_t fed_table_length, fed_table_max_length;

static inline void add_to_fed_table(tix_entry entry) {
    if (!fed_table) {
        fed_table_length = 0;
        fed_table_max_length = DEFAULT_FED_TABLE_LENGTH;
        fed_table = (tix_entry *)malloc(fed_table_max_length * sizeof(tix_entry));
    } else if (fed_table_length == fed_table_max_length) {
        fed_table_max_length *= 2;
        fed_table = (tix_entry *)realloc(fed_table, fed_table_max_length * sizeof(tix_entry));
    }

    fed_table[fed_table_length++] = entry;
}

EXTERN_C

void __csirt_tix_init(const char * const name,
                      uint64_t *tix_unit_base,
                      uint64_t num_units,
                      fed_entry *tix_entries) {
    tix_entry entry = {.num_units = num_units, .entries = tix_entries};
    add_to_fed_table(entry);

    *tix_unit_base = units_seen;
    units_seen += num_units;

    __csi_init(name, num_units);
}

EXTERN_C_END

static inline fed_entry *get_fed_entry(uint64_t csi_id) {
    uint64_t unit_id = UNIT_ID_FROM_CSI_ID(csi_id),
        offset = ENTRY_OFFSET_FROM_CSI_ID(csi_id);

    assert(offset < fed_table[unit_id].num_units);
    return &fed_table[unit_id].entries[offset];
}

char *__csi_get_filename(uint64_t csi_id) {
    return get_fed_entry(csi_id)->filename;
}

uint32_t __csi_get_line_number(uint64_t csi_id) {
    return get_fed_entry(csi_id)->line_number;
}
