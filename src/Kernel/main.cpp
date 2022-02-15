// #include <LibCpp/Types.h>

// static void (*terminal_write)(const char *, size_t);

// using Isr = void (*)();

// struct IdtEntry
// {
//     u16 offset_1;        // offset bits 0..15
//     u16 selector;        // a code segment selector in GDT or LDT
//     u8 ist;             // bits 0..2 holds Interrupt Stack Table offset, rest of bits zero.
//     u8 type_attributes; // gate type, dpl, and p fields
//     u16 offset_2;        // offset bits 16..31
//     u32 offset_3;        // offset bits 32..63
//     u32 zero;   
// };

// static IdtEntry idt[256];

// void set_exception_handler(u8 index, Isr isr)
// {
//     auto offset = reinterpret_cast<u64>(isr);

//     idt[index].offset_1 = static_cast<u16>(offset);
//     idt[index].offset_2 = static_cast<u16>(offset >> 16);
//     idt[index].offset_3 = static_cast<u32>(offset >> 32);
//     idt[index].selector = 0x08;
//     idt[index].type_attributes = 0x8E;
// }

// void error()
// {
//     terminal_write("divide error", 12);
//     for (;;)
//         asm ("hlt");
// }

// struct  __attribute__((packed)) Idtr
// {
// 	u16 limit;
// 	u64 base;
// };

// struct Idtr idtp;

// struct __attribute__((packed)) GdtEntry
// {
//     u16 limit_1;
//     u16 base_1;
//     u8 base_2;
//     u8 access;
//     u8 flags;
//     u8 base_3;
//     u32 base_4;
//     u32 zero;
// };

// struct Gdtr
// {
// 	u16 limit;
// 	u64 base;
// }  __attribute__((packed));

// GdtEntry gdt[3];
// Gdtr gp;

// void gdt_set_gate(int num, u64 base, u32 limit, u8 access, u8 gran)
// {
//     /* Setup the descriptor base address */
//     gdt[num].base_1 = (base & 0xFFFF);
//     gdt[num].base_2 = (base >> 16) & 0xFF;
//     gdt[num].base_3 = (base >> 24) & 0xFF;
//     gdt[num].base_4 = (base >> 32) & 0xFFFFFFFF;

//     /* Setup the descriptor limits */
//     gdt[num].limit_1 = (limit & 0xFFFF);
//     gdt[num].flags = ((limit >> 16) & 0x0F);

//     /* Finally, set up the granularity and access flags */
//     gdt[num].flags |= (gran & 0xF0);
//     gdt[num].access = access;
// }

// extern "C" void idt_load();
// extern "C" void gdt_flush();

// void main(void (*write)(const char *, size_t))
// {
//     terminal_write = write;
//     asm volatile ("cli");
//     // write("abc", 3);

//     gp.base = reinterpret_cast<u64>(gdt);
//     gp.limit = (sizeof (GdtEntry) * 3) - 1;
//     gdt_set_gate(0, 0, 0, 0, 0);
//     gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);
//     gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF);
//     gdt_flush();

//     return;
//         idtp.base = reinterpret_cast<u64>(idt);
//     idtp.limit = (sizeof (IdtEntry) * 256) - 1;
//     idt_load();

//     for (u8 i = 0; i < 32; i++)
//     {
//         set_exception_handler(i, error);
//     }

//     // gdt_set_gate(0, 0, 0, 0, 0);
//     // gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);
//     // gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF);

//     gdt_set_gate(0, 0, 0, 0, 0);
//     gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xAF);
//     gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF);

//     gp.base = reinterpret_cast<u64>(gdt);
//     gp.limit = (sizeof (GdtEntry) * 3) - 1;
//     gdt_flush();

//     write("efg", 3);
//     // asm volatile ("lidt %0" : : "memory"(idtr));
//     //asm volatile ("sti");
//     // char* a = "abc";
//     // a[0] = offsetof(Idtr, limit) + '0';
//     // a[1] = offsetof(Idtr, base) + '0';
//     //asm volatile ("int 0");
// }