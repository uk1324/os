#pragma once

/**
 *	@file gdt.h
 *	@brief Function prototypes and structs for gdt
 *
 *  These structs are representing the gdt, gdt_ptr or a gdt_entry.
 *  The functions  are used to create an appropriate gdt and initialises it with correct values
 */

#include <stdint.h>

/**
 *  @brief Pointer struct which points to the gdt and holds it's length
 */
struct gdt_ptr {
	uint16_t size;         ///< size of the table subtracted by 1
	uint64_t offset;       ///< linear address to the table
}__attribute__((packed));

/**
 *  @brief Single entry of the gdt table as struct
 */
struct gdt_entry {
	uint16_t limit_lo;     ///< limit bits 0..15
	uint16_t base_lo;      ///< base address bits 0..15
	uint8_t  base_mid;     ///< base address bits 16..23
	uint8_t  access;       ///< Byte which holds informations about the segment
	uint8_t  limit_hi:4;   ///< limit bits 16..19
	uint8_t  flags:4;      ///< Holds granularity, size, long mode bit. Last bit is available to the programmer
	uint8_t  base_hi;      ///< base address bits 24..31
}__attribute__((packed));

/**
 *  @brief Task state segment, holds information about a task
 */
struct tss_entry {
    uint16_t length;       ///< Length of the tss segment
    uint16_t base_low16;   ///< base address bits 0..16
    uint8_t  base_mid8;    ///< Lower half of upper half of the base adress
    uint8_t  flags1;       ///<  
    uint8_t  flags2;       ///< 
    uint8_t  base_high8;   ///< 
    uint32_t base_upper32; ///< 
    uint32_t reserved;     ///< Reserved 4 bytes
} __attribute__((packed));

/**
 *  @brief GDT struct which holds five gdt_entries and one tss_entry
 */
struct GDT {
    struct gdt_entry entries[3]; ///< Entries of the gdt, which are a null descriptor, kernel code/data and user code/data
    // struct tss_entry tss;        ///< TSS Segment
} __attribute__((packed));

/**
 *  @brief Initializes the gdt table with the corrosponding values
 */
void gdt_init();

/**
 *  @brief Creates a gdt entry with the parameters as values
 *  @param limit The size of the segment in u32
 *  @param base base Adress where the segment starts
 *  @param access Holds the bits for writeable, executable and privilege level
 *  @param flags
 *  @return The gdt entry as struct, to be saved in an array
 */

struct gdt_entry gdt_create_entry(uint32_t limit, uint32_t base, uint8_t access, uint8_t flags);

/**
 *  @brief Loads the gdt table to memory
 */
void gdt_load();