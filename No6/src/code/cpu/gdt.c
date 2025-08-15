#include "header/cpu/gdt.h"
#include "header/cpu/interrupt.h"

struct GlobalDescriptorTable global_descriptor_table = {
    .table = {
        {
            .segment_low=0x0, .base_low=0x0, .base_mid=0x0, .type_bit=0x0, .non_system=0x0, .privilege=0x0, .segment_present=0x0, .segment_high=0x0, .long_mode=0x0, .opr_32_bit=0x0, .granularity=0x0, .base_high=0x0
        },
        {
            .segment_low=0xFFFF, .base_low=0x0, .base_mid=0x0, .type_bit=0xA, .non_system=0x1, .privilege=0x0, .segment_present=0x1, .segment_high=0xF, .long_mode=0x0, .opr_32_bit=0x1, .granularity=0x1, .base_high=0x0
        },
        {
            .segment_low=0xFFFF, .base_low=0x0, .base_mid=0x0, .type_bit=0x2, .non_system=0x1, .privilege=0x0, .segment_present=0x1, .segment_high=0xF, .long_mode=0x0, .opr_32_bit=0x1, .granularity=0x1, .base_high=0x0
        },
        {
            .segment_low=0xFFFF, .base_low=0x0, .base_mid=0x0, .type_bit=0xA, .non_system=0x1, .privilege=0x3, .segment_present=0x1, .segment_high=0xF, .long_mode=0x0, .opr_32_bit=0x1, .granularity=0x1, .base_high=0x0
        },
        {
            .segment_low=0xFFFF, .base_low=0x0, .base_mid=0x0, .type_bit=0x2, .non_system=0x1, .privilege=0x3, .segment_present=0x1, .segment_high=0xF, .long_mode=0x0, .opr_32_bit=0x1, .granularity=0x1, .base_high=0x0
        },
        {
            .segment_high      = (sizeof(struct TSSEntry) & (0xF << 16)) >> 16,
            .segment_low       = sizeof(struct TSSEntry),
            .base_high         = 0,
            .base_mid          = 0,
            .base_low          = 0,
            .non_system        = 0,    // S bit
            .type_bit          = 0x9,
            .privilege         = 0,    // DPL
            .segment_present         = 1,    // P bit
            .opr_32_bit        = 1,    // D/B bit
            .long_mode         = 0,    // L bit
            .granularity       = 0,    // G bit
        },
        {0}
    }
};

/**
 * _gdt_gdtr, predefined system GDTR. 
 * GDT pointed by this variable is already set to point global_descriptor_table above.
 * From: https://wiki.osdev.org/Global_Descriptor_Table, GDTR.size is GDT size minus 1.
 */
struct GDTR _gdt_gdtr = {
    .size = sizeof(global_descriptor_table)-1,
    .address = &global_descriptor_table //what
};

void gdt_install_tss(void) {
    uint32_t base = (uint32_t) &_interrupt_tss_entry;
    global_descriptor_table.table[5].base_high = (base & (0xFF << 24)) >> 24;
    global_descriptor_table.table[5].base_mid  = (base & (0xFF << 16)) >> 16;
    global_descriptor_table.table[5].base_low  = base & 0xFFFF;
}