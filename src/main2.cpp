#include <stdint.h>
#include <stddef.h>

#include <gdt.h>

#include <Kernel/idt.h>

void (*term_write)(const char *, size_t);

typedef struct cpu_register_state {
    /// Every gp register is defined as unsigned 64bit number
    uint64_t r15, r14, r13, r12, r11, r10, r9, r8, rdi, rsi, rbp, rdx, rcx, rbx, rax; 
} __attribute__((packed)) cpu_register_state_t;

typedef struct interrupt_context {
    cpu_register_state_t regs; ///< general purpose registers which get pushed upon interrupt
    uint64_t int_no, err;      ///< interrupt number and the error code of the interrupt
    uint64_t rip, cs, rflags;  ///< Instruction pointer to see where the interrupt happened, code segments and flags
    uint64_t rsp, ss;          ///< Stack pointer and stack segment
} __attribute__((packed)) interrupt_context_t;

#include <Kernel/IoBus.h>

extern "C" void handle_interrupt(interrupt_context_t *irq_context)
{

    char a[1];
    a[0] = '0' + irq_context->err;
    term_write(a, 1);

    term_write(" test\n", 5);

    IoBus::writeByte(0x20,0x20);

    // for (;;)
    //     asm ("hlt");
}


static constexpr auto outportb = IoBus::writeByte;

void timer_phase(int hz)
{
    int divisor = 1193180 / hz;       /* Calculate our divisor */
    outportb(0x43, 0x36);             /* Set our command byte 0x36 */
    outportb(0x40, divisor & 0xFF);   /* Set low byte of divisor */
    outportb(0x40, divisor >> 8);     /* Set high byte of divisor */
}

void main(void (*write)(const char *, size_t))
{
    term_write = write;

    asm volatile ("cli");
    idt_init();
    irq_install();
    // timer_phase(100);
    asm volatile ("sti");



    write("after idt", 9);

    // asm volatile ("int $0");

    // char b[20];
    // uint64_t p = *reinterpret_cast<uint64_t*>(&static_gdtr);
    // int i = 0;
    // while (p)
    // {
    //     b[i] = '0' + p % 16;
    //     p /= 16;
    //     i++;
    // }
    // write(b, i + 1);
    // asm volatile ("cli");

    // write("before gdt", 10);

    // gdt_init();

    // write("mid gdt", 7);
    // gdt_load();



    // volatile int x = 5;
    // for (int i = 0; 5; i++)
    // {
    //     x += i;
    // }
    // write("after gdt", 9);
}