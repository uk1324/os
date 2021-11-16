#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include <LibCpp/Cstring.h>
#include <Kernel/IoBus.h>
#include <Kernel/VgaTerminal.h>
#include <Kernel/Serial.h>

#include <LibCpp/HeapAllocator.h>

#include <Kernel/kstdio.h>
#include <Kernel/Assertions.h>

// static inline unsigned long native_save_fl(void)
// {
//     unsigned long flags;

//      /*
//       * "=rm" is safe here, because "pop" adjusts the stack before
//       * it evaluates its effective address -- this is part of the
//       * documented behavior of the "pop" instruction.
//       */
//      asm volatile("# __raw_save_flags\n\t"
//               "pushf ; pop %0"
//               : "=rm" (flags)
//               : /* no input */
//               : "memory");

//      return flags;
// }

// typedef struct {
// 	uint16_t    isr_low;      // The lower 16 bits of the ISR's address
// 	uint16_t    kernel_cs;    // The GDT segment selector that the CPU will load into CS before calling the ISR
// 	uint8_t     reserved;     // Set to zero
// 	uint8_t     attributes;   // Type and attributes; see the IDT page
// 	uint16_t    isr_high;     // The higher 16 bits of the ISR's address
// } __attribute__((packed)) idt_entry_t;

// // __attribute__((aligned(0x10))) 
// // static idt_entry_t idt[256]; // Create an array of IDT entries; aligned for performance
// static idt_entry_t* idt = reinterpret_cast<idt_entry_t*>(65504);

// typedef struct {
// 	uint16_t	limit;
// 	uint32_t	base;
// } __attribute__((packed)) idtr_t;

// static idtr_t idtr;

// void idt_set_descriptor(uint8_t vector, void* isr, uint8_t flags);
// void idt_set_descriptor(uint8_t vector, void* isr, uint8_t flags) {
//     idt_entry_t* descriptor = &idt[vector];
 
//     descriptor->isr_low        = (uint32_t)isr & 0xFFFF;
//     descriptor->kernel_cs      = 0x08; // this value can be whatever offset your kernel code selector is in your GDT
//     descriptor->attributes     = flags;
//     descriptor->isr_high       = (uint32_t)isr >> 16;
//     descriptor->reserved       = 0;
// }

// extern void* isr_stub_table[];
 
// void idt_init(void);
// void idt_init() {
//     idtr.base = (uintptr_t)&idt[0];
//     // idtr.limit = (uint16_t)sizeof(idt_entry_t) * 255 - 1;
// 	idtr.limit = (uint16_t)sizeof(idt_entry_t) * 32 - 1;
 
//     for (uint8_t vector = 0; vector < 32; vector++) {
//         idt_set_descriptor(vector, isr_stub_table[vector], 0x8E);
//         // vectors[vector] = true;
//     }
 
//     asm volatile ("lidt %0" : : "memory"(idtr)); // load the new IDT
//     asm volatile ("sti"); // set the interrupt flag
// }

// extern "C"
// void exception_handler(int n);
// void exception_handler(int n) {
// 	kprintf("What %d\n", n);
// 	// kprintf("What\n");
//     // asm volatile ("cli \n\t hlt"); // Completely hangs the computer
// 	// while (true)
// 	// {
// 	// 	/* code */
// 	// }
// 	// while (true)
// }

// // Each define here is for a specific flag in the descriptor.
// // Refer to the intel documentation for a description of what each one does.
// #define SEG_DESCTYPE(x)  ((x) << 0x04) // Descriptor type (0 for system, 1 for code/data)
// #define SEG_PRES(x)      ((x) << 0x07) // Present
// #define SEG_SAVL(x)      ((x) << 0x0C) // Available for system use
// #define SEG_LONG(x)      ((x) << 0x0D) // Long mode
// #define SEG_SIZE(x)      ((x) << 0x0E) // Size (0 for 16-bit, 1 for 32)
// #define SEG_GRAN(x)      ((x) << 0x0F) // Granularity (0 for 1B - 1MB, 1 for 4KB - 4GB)
// #define SEG_PRIV(x)     (((x) &  0x03) << 0x05)   // Set privilege level (0 - 3)
 
// #define SEG_DATA_RD        0x00 // Read-Only
// #define SEG_DATA_RDA       0x01 // Read-Only, accessed
// #define SEG_DATA_RDWR      0x02 // Read/Write
// #define SEG_DATA_RDWRA     0x03 // Read/Write, accessed
// #define SEG_DATA_RDEXPD    0x04 // Read-Only, expand-down
// #define SEG_DATA_RDEXPDA   0x05 // Read-Only, expand-down, accessed
// #define SEG_DATA_RDWREXPD  0x06 // Read/Write, expand-down
// #define SEG_DATA_RDWREXPDA 0x07 // Read/Write, expand-down, accessed
// #define SEG_CODE_EX        0x08 // Execute-Only
// #define SEG_CODE_EXA       0x09 // Execute-Only, accessed
// #define SEG_CODE_EXRD      0x0A // Execute/Read
// #define SEG_CODE_EXRDA     0x0B // Execute/Read, accessed
// #define SEG_CODE_EXC       0x0C // Execute-Only, conforming
// #define SEG_CODE_EXCA      0x0D // Execute-Only, conforming, accessed
// #define SEG_CODE_EXRDC     0x0E // Execute/Read, conforming
// #define SEG_CODE_EXRDCA    0x0F // Execute/Read, conforming, accessed
 
// #define GDT_CODE_PL0 SEG_DESCTYPE(1) | SEG_PRES(1) | SEG_SAVL(0) | \
//                      SEG_LONG(0)     | SEG_SIZE(1) | SEG_GRAN(1) | \
//                      SEG_PRIV(0)     | SEG_CODE_EXRD
 
// #define GDT_DATA_PL0 SEG_DESCTYPE(1) | SEG_PRES(1) | SEG_SAVL(0) | \
//                      SEG_LONG(0)     | SEG_SIZE(1) | SEG_GRAN(1) | \
//                      SEG_PRIV(0)     | SEG_DATA_RDWR
 
// #define GDT_CODE_PL3 SEG_DESCTYPE(1) | SEG_PRES(1) | SEG_SAVL(0) | \
//                      SEG_LONG(0)     | SEG_SIZE(1) | SEG_GRAN(1) | \
//                      SEG_PRIV(3)     | SEG_CODE_EXRD
 
// #define GDT_DATA_PL3 SEG_DESCTYPE(1) | SEG_PRES(1) | SEG_SAVL(0) | \
//                      SEG_LONG(0)     | SEG_SIZE(1) | SEG_GRAN(1) | \
//                      SEG_PRIV(3)     | SEG_DATA_RDWR
 
// uint64_t
// create_descriptor(uint32_t base, uint32_t limit, uint16_t flag)
// {
//     uint64_t descriptor;
 
//     // Create the high 32 bit segment
//     descriptor  =  limit       & 0x000F0000;         // set limit bits 19:16
//     descriptor |= (flag <<  8) & 0x00F0FF00;         // set type, p, dpl, s, g, d/b, l and avl fields
//     descriptor |= (base >> 16) & 0x000000FF;         // set base bits 23:16
//     descriptor |=  base        & 0xFF000000;         // set base bits 31:24
 
//     // Shift by 32 to allow for low part of segment
//     descriptor <<= 32;
 
//     // Create the low 32 bit segment
//     descriptor |= base  << 16;                       // set base bits 15:0
//     descriptor |= limit  & 0x0000FFFF;               // set limit bits 15:0
 
//     // printf("0x%.16llX\n", descriptor);
// 	return descriptor;
// }

// typedef struct {
// 	uint16_t	limit;
// 	uint32_t	base;
// } __attribute__((packed)) abc;

// static abc intt;

// static uint64_t* gdt = reinterpret_cast<uint64_t*>(60000);

/* Defines a GDT entry. We say packed, because it prevents the
*  compiler from doing things that it thinks is best: Prevent
*  compiler "optimization" by packing */
struct gdt_entry
{
    unsigned short limit_low;
    unsigned short base_low;
    unsigned char base_middle;
    unsigned char access;
    unsigned char granularity;
    unsigned char base_high;
} __attribute__((packed));

/* Special pointer which includes the limit: The max bytes
*  taken up by the GDT, minus 1. Again, this NEEDS to be packed */
struct gdt_ptr
{
    unsigned short limit;
    unsigned int base;
} __attribute__((packed));

/* Our GDT, with 3 entries, and finally our special GDT pointer */
struct gdt_entry gdt[3];
struct gdt_ptr gp;

/* This will be a function in start.asm. We use this to properly
*  reload the new segment registers */
extern "C" void gdt_flush();

/* Setup a descriptor in the Global Descriptor Table */
void gdt_set_gate(int num, unsigned long base, unsigned long limit, unsigned char access, unsigned char gran)
{
    /* Setup the descriptor base address */
    gdt[num].base_low = (base & 0xFFFF);
    gdt[num].base_middle = (base >> 16) & 0xFF;
    gdt[num].base_high = (base >> 24) & 0xFF;

    /* Setup the descriptor limits */
    gdt[num].limit_low = (limit & 0xFFFF);
    gdt[num].granularity = ((limit >> 16) & 0x0F);

    /* Finally, set up the granularity and access flags */
    gdt[num].granularity |= (gran & 0xF0);
    gdt[num].access = access;
}

/* Should be called by main. This will setup the special GDT
*  pointer, set up the first 3 entries in our GDT, and then
*  finally call gdt_flush() in our assembler file in order
*  to tell the processor where the new GDT is and update the
*  new segment registers */
void gdt_install()
{
    /* Setup the GDT pointer and limit */
    gp.limit = (sizeof(struct gdt_entry) * 3) - 1;
    gp.base = (unsigned int)&gdt;

    /* Our NULL descriptor */
    gdt_set_gate(0, 0, 0, 0, 0);

    /* The second entry is our Code Segment. The base address
    *  is 0, the limit is 4GBytes, it uses 4KByte granularity,
    *  uses 32-bit opcodes, and is a Code Segment descriptor.
    *  Please check the table above in the tutorial in order
    *  to see exactly what each value means */
    gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);

    /* The third entry is our Data Segment. It's EXACTLY the
    *  same as our code segment, but the descriptor type in
    *  this entry's access byte says it's a Data Segment */
    gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF);

    /* Flush out the old GDT and install the new changes! */
    gdt_flush();
}

/* Defines an IDT entry */
struct idt_entry
{
    unsigned short base_lo;
    unsigned short sel;        /* Our kernel segment goes here! */
    unsigned char always0;     /* This will ALWAYS be set to 0! */
    unsigned char flags;       /* Set using the above table! */
    unsigned short base_hi;
} __attribute__((packed));

struct idt_ptr
{
    unsigned short limit;
    unsigned int base;
} __attribute__((packed));

/* Declare an IDT of 256 entries. Although we will only use the
*  first 32 entries in this tutorial, the rest exists as a bit
*  of a trap. If any undefined IDT entry is hit, it normally
*  will cause an "Unhandled Interrupt" exception. Any descriptor
*  for which the 'presence' bit is cleared (0) will generate an
*  "Unhandled Interrupt" exception */
struct idt_entry idt[256];
struct idt_ptr idtp;

/* This exists in 'start.asm', and is used to load our IDT */
extern "C" void idt_load();

/* Use this function to set an entry in the IDT. Alot simpler
*  than twiddling with the GDT ;) */
void idt_set_gate(unsigned char num, unsigned long base, unsigned short sel, unsigned char flags)
{
    /* We'll leave you to try and code this function: take the
    *  argument 'base' and split it up into a high and low 16-bits,
    *  storing them in idt[num].base_hi and base_lo. The rest of the
    *  fields that you must set in idt[num] are fairly self-
    *  explanatory when it comes to setup */
       /* The interrupt routine's base address */
    idt[num].base_lo = (base & 0xFFFF);
    idt[num].base_hi = (base >> 16) & 0xFFFF;

    /* The segment or 'selector' that this IDT entry will use
    *  is set here, along with any access flags */
    idt[num].sel = sel;
    idt[num].always0 = 0;
    idt[num].flags = flags;
}

/* Installs the IDT */
void idt_install()
{
    /* Sets the special IDT pointer up, just like in 'gdt.c' */
    idtp.limit = (sizeof (struct idt_entry) * 256) - 1;
    idtp.base = reinterpret_cast<unsigned int>(&idt[0]);

    /* Clear out the entire IDT, initializing it to zeros */
	for (int i = 0; i < sizeof(struct idt_entry) * 256; i++)
	{
		*reinterpret_cast<char*>(&idt[0]) = 0;
	}

    /* Add any new ISRs to the IDT here using idt_set_gate */

    /* Points the processor's internal register to the new IDT */
    idt_load();
    // asm volatile ("lidt %0" : : "memory"(idtp)); // load the new IDT
    // asm volatile ("sti"); // set the interrupt flag
}

extern "C" void _isr0();
extern "C" void _isr1();
extern "C" void _isr2();
extern "C" void _isr3();
extern "C" void _isr4();
extern "C" void _isr5();
extern "C" void _isr6();
extern "C" void _isr7();
extern "C" void _isr8();
extern "C" void _isr9();
extern "C" void _isr10();
extern "C" void _isr11();
extern "C" void _isr12();
extern "C" void _isr13();
extern "C" void _isr14();
extern "C" void _isr15();
extern "C" void _isr16();
extern "C" void _isr17();
extern "C" void _isr18();
extern "C" void _isr19();
extern "C" void _isr20();
extern "C" void _isr21();
extern "C" void _isr22();
extern "C" void _isr23();
extern "C" void _isr24();
extern "C" void _isr25();
extern "C" void _isr26();
extern "C" void _isr27();
extern "C" void _isr28();
extern "C" void _isr29();
extern "C" void _isr30();
extern "C" void _isr31();

void isrs_install()
{
    idt_set_gate(0, (unsigned)_isr0, 0x08, 0x8E);
    idt_set_gate(1, (unsigned)_isr1, 0x08, 0x8E);
    idt_set_gate(2, (unsigned)_isr2, 0x08, 0x8E);
    idt_set_gate(3, (unsigned)_isr3, 0x08, 0x8E);
	idt_set_gate(4, (unsigned)_isr4, 0x08, 0x8E);
	idt_set_gate(5, (unsigned)_isr5, 0x08, 0x8E);
	idt_set_gate(7, (unsigned)_isr7, 0x08, 0x8E);
	idt_set_gate(8, (unsigned)_isr8, 0x08, 0x8E);
	idt_set_gate(9, (unsigned)_isr9, 0x08, 0x8E);
	idt_set_gate(10, (unsigned)_isr10, 0x08, 0x8E);
	idt_set_gate(11, (unsigned)_isr11, 0x08, 0x8E);
	idt_set_gate(12, (unsigned)_isr12, 0x08, 0x8E);
	idt_set_gate(13, (unsigned)_isr13, 0x08, 0x8E);
	idt_set_gate(14, (unsigned)_isr14, 0x08, 0x8E);
	idt_set_gate(15, (unsigned)_isr15, 0x08, 0x8E);
	idt_set_gate(16, (unsigned)_isr16, 0x08, 0x8E);
	idt_set_gate(17, (unsigned)_isr17, 0x08, 0x8E);
	idt_set_gate(18, (unsigned)_isr18, 0x08, 0x8E);
	idt_set_gate(19, (unsigned)_isr19, 0x08, 0x8E);
	idt_set_gate(20, (unsigned)_isr20, 0x08, 0x8E);
	idt_set_gate(21, (unsigned)_isr21, 0x08, 0x8E);
	idt_set_gate(22, (unsigned)_isr22, 0x08, 0x8E);
	idt_set_gate(23, (unsigned)_isr23, 0x08, 0x8E);
	idt_set_gate(24, (unsigned)_isr24, 0x08, 0x8E);
	idt_set_gate(25, (unsigned)_isr25, 0x08, 0x8E);
	idt_set_gate(26, (unsigned)_isr26, 0x08, 0x8E);
	idt_set_gate(27, (unsigned)_isr27, 0x08, 0x8E);
	idt_set_gate(28, (unsigned)_isr28, 0x08, 0x8E);
	idt_set_gate(29, (unsigned)_isr29, 0x08, 0x8E);
    idt_set_gate(30, (unsigned)_isr30, 0x08, 0x8E);
    idt_set_gate(31, (unsigned)_isr31, 0x08, 0x8E);
	
}

// unsigned char *exception_messages[] =
// {
//     "Division By Zero",
//     "Debug",
//     "Non Maskable Interrupt",
// 	"4",
//     "Reserved",
//     "Reserved"
// };

/* This defines what the stack looks like after an ISR was running */
struct regs
{
    unsigned int gs, fs, es, ds;      /* pushed the segs last */
    unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax;  /* pushed by 'pusha' */
    unsigned int int_no, err_code;    /* our 'push byte #' and ecodes do this */
    unsigned int eip, cs, eflags, useresp, ss;   /* pushed by the processor automatically */ 
};
	

/* All of our Exception handling Interrupt Service Routines will
*  point to this function. This will tell us what exception has
*  happened! Right now, we simply halt the system by hitting an
*  endless loop. All ISRs disable interrupts while they are being
*  serviced as a 'locking' mechanism to prevent an IRQ from
*  happening and messing up kernel data structures */
extern "C" void fault_handler(struct regs *r)
{
    /* Is this a fault whose number is from 0 to 31? */
    // if (r->int_no < 32)
    {
        /* Display the description for the Exception that occurred.
        *  In this tutorial, we will simply halt the system using an
        *  infinite loop */
	   	kprintf("int %d code: %d\n", r->int_no, r->err_code);
		kprintf("eip %H\n", r->eip);
		// VgaTerminal t;
		// t.writeString("abcddefafsd");
        // puts(exception_messages[r->int_no]);
        // puts(" Exception. System Halted!\n");
        for (;;);
    }
}

extern "C" void main()
{
	Serial::init();

	gdt_install();
	idt_install();
	isrs_install();
	asm volatile ("sti");
	// gdt[0] = create_descriptor(0, 0, 0);
	// gdt[1] = create_descriptor(0, 0xFFFFFFFF, 0x9A);
    // gdt[2] = create_descriptor(0, 0xFFFFFFFF, 0x92);
	// intt.base = reinterpret_cast<uint32_t>(&gdt[0]);
	// intt.limit = 3 * 8 - 1;
	// asm volatile ("lgdt %0" : : "memory"(intt)); // load the new IDT
	// idt_init();
	// kprintf("test\n");
	// kprintf("%d %d", sizeof(unsigned), sizeof(unsigned long));

	VgaTerminal t;
	t.writeString("abc");
	// asm volatile ("cli");

	volatile int x;
	volatile int y = 0;

	// x /= y;
	asm volatile ("int 0");

	VgaTerminal terminal;
	terminal.writeString("azbc");
	// while (true)
	// {
	// 	t.writeString("abc");
	// 	asm volatile ("int 3");
	// 	for (volatile int i = 0; i < 100000; i++);
	// }
	
	// VgaTerminal terminal;
	// // terminal.writeString("abc");

	// // kprintf("test3");

	// // volatile int x = 5;
	// // asm volatile("int 0");
	// kprintf("abc");
	// terminal.writeString("efg");
	// // x /= 0;
	// volatile int x;
	// x /= 0;
	// asm volatile ("int 0");
	// asm volatile ("sti");
	// asm volatile ("cli");
	// VgaTerminal terminal;
	// terminal.writeString("abc");
	// kprintf("abc");
	// volatile int x = 5;
	// volatile int x = 5 / 0;

	// kprintf("test2\n");
	// kprintf("%H\n", native_save_fl() & 0x200);

	// HeapAllocator allocator(reinterpret_cast<void*>(40960), 1024);

	// void* a = allocator.allocate(4);
	// void* b = allocator.allocate(4);
	// void* c = allocator.allocate(4);
	// void* d = allocator.allocate(4);
	// void* e = allocator.allocate(4);

	// allocator.print();

	// void* arr[] = {
	// 	// a, b, c, d, e
	// 	// d, b, e, c, a, 
	// 	// d, b, c
	// 	c, a, b, e, d
	// };

	// for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	// {
	// 	if (Serial::read() == 'a')
	// 	// if (true)
	// 	{
	// 		allocator.free(arr[i]);
	// 		allocator.print();
	// 	}
	// }

	// // allocator.free(c);
	// // allocator.free(a);
	// allocator.free(b);
	// allocator.free(c);

	// allocator.print();


	// while (true)
	// {
	// 	char value = Serial::read();
	// 	terminal.putChar(value);
	// 	Serial::write(value);
	// }
}