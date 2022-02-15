
#include <Kernel/IoBus.h>
#include <Kernel/idt.h>
#include <stddef.h>

static struct idt_entry idt[256];

typedef void (*isr_fn_t)(void);

isr_fn_t handlers[256] = {
	isr0,   isr1,   isr2,   isr3,   isr4,   isr5,   isr6,   isr7,
	isr8,   isr9,   isr10,  isr11,  isr12,  isr13,  isr14,  isr15,
	isr16,  isr17,  isr18,  isr19,  isr20,  isr21,  isr22,  isr23,
	isr24,  isr25,  isr26,  isr27,  isr28,  isr29,  isr30,  isr31,
	// isr32,  isr33,  isr34,  isr35,  isr36,  isr37,  isr38,  isr39,
	// isr40,  isr41,  isr42,  isr43,  isr44,  isr45,  isr46,  isr47,
	// isr48,  isr49,  isr50,  isr51,  isr52,  isr53,  isr54,  isr55,
	// isr56,  isr57,  isr58,  isr59,  isr60,  isr61,  isr62,  isr63,
	// isr64,  isr65,  isr66,  isr67,  isr68,  isr69,  isr70,  isr71,
	// isr72,  isr73,  isr74,  isr75,  isr76,  isr77,  isr78,  isr79,
	// isr80,  isr81,  isr82,  isr83,  isr84,  isr85,  isr86,  isr87,
	// isr88,  isr89,  isr90,  isr91,  isr92,  isr93,  isr94,  isr95,
	// isr96,  isr97,  isr98,  isr99,  isr100, isr101, isr102, isr103,
	// isr104, isr105, isr106, isr107, isr108, isr109, isr110, isr111,
	// isr112, isr113, isr114, isr115, isr116, isr117, isr118, isr119,
	// isr120, isr121, isr122, isr123, isr124, isr125, isr126, isr127,
	// isr128, isr129, isr130, isr131, isr132, isr133, isr134, isr135,
	// isr136, isr137, isr138, isr139, isr140, isr141, isr142, isr143,
	// isr144, isr145, isr146, isr147, isr148, isr149, isr150, isr151,
	// isr152, isr153, isr154, isr155, isr156, isr157, isr158, isr159,
	// isr160, isr161, isr162, isr163, isr164, isr165, isr166, isr167,
	// isr168, isr169, isr170, isr171, isr172, isr173, isr174, isr175,
	// isr176, isr177, isr178, isr179, isr180, isr181, isr182, isr183,
	// isr184, isr185, isr186, isr187, isr188, isr189, isr190, isr191,
	// isr192, isr193, isr194, isr195, isr196, isr197, isr198, isr199,
	// isr200, isr201, isr202, isr203, isr204, isr205, isr206, isr207,
	// isr208, isr209, isr210, isr211, isr212, isr213, isr214, isr215,
	// isr216, isr217, isr218, isr219, isr220, isr221, isr222, isr223,
	// isr224, isr225, isr226, isr227, isr228, isr229, isr230, isr231,
	// isr232, isr233, isr234, isr235, isr236, isr237, isr238, isr239,
	// isr240, isr241, isr242, isr243, isr244, isr245, isr246, isr247,
	// isr248, isr249, isr250, isr251, isr252, isr253, isr254, isr255,
};

static int register_interrupt_handler(size_t vec, void *handler, uint8_t ist, uint8_t type) {
    uint64_t p = (uint64_t)handler;


    idt[vec].offset_lo = (uint16_t)p;
    idt[vec].selector = 40;
    idt[vec].ist = ist;
    idt[vec].type_attr = type;
    idt[vec].offset_mid = (uint16_t)(p >> 16);
    idt[vec].offset_hi = (uint32_t)(p >> 32);
    idt[vec].zero = 0;

    return 0;
}

struct idt_ptr_t idt_ptr;

void idt_init()
{
    for (size_t i = 0; i < 256; i++)
    {
        if (i < 32)
            // register_interrupt_handler(i, reinterpret_cast<void*>(handlers[i]), 0, 0x8F);
            register_interrupt_handler(i, reinterpret_cast<void*>(handlers[i]), 0, 0x8e);
        else   
            // register_interrupt_handler(i, reinterpret_cast<void*>(handlers[i]), 0, 0x8F);         
            register_interrupt_handler(i, reinterpret_cast<void*>(handlers[0]), 0, 0x8e);
    }

    idt_ptr = {
        sizeof(idt) - 1,
        (uint64_t)idt
    };

    asm volatile (
        "lidt %0"
        :
        : "m" (idt_ptr)
    );
}


/* These are own ISRs that point to our special IRQ handler
*  instead of the regular 'fault_handler' function */
extern "C" void irq0();
extern "C" void irq1();
extern "C" void irq2();
extern "C" void irq3();
extern "C" void irq4();
extern "C" void irq5();
extern "C" void irq6();
extern "C" void irq7();
extern "C" void irq8();
extern "C" void irq9();
extern "C" void irq10();
extern "C" void irq11();
extern "C" void irq12();
extern "C" void irq13();
extern "C" void irq14();
extern "C" void irq15();

/* This array is actually an array of function pointers. We use
*  this to handle custom IRQ handlers for a given IRQ */
void *irq_routines[16] =
{
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0
};

/* Normally, IRQs 0 to 7 are mapped to entries 8 to 15. This
*  is a problem in protected mode, because IDT entry 8 is a
*  Double Fault! Without remapping, every time IRQ0 fires,
*  you get a Double Fault Exception, which is NOT actually
*  what's happening. We send commands to the Programmable
*  Interrupt Controller (PICs - also called the 8259's) in
*  order to make IRQ0 to 15 be remapped to IDT entries 32 to
*  47 */
void irq_remap(void)
{
    IoBus::writeByte(0x20, 0x11);
    IoBus::writeByte(0xA0, 0x11);
    IoBus::writeByte(0x21, 0x20);
    IoBus::writeByte(0xA1, 0x28);
    IoBus::writeByte(0x21, 0x04);
    IoBus::writeByte(0xA1, 0x02);
    IoBus::writeByte(0x21, 0x01);
    IoBus::writeByte(0xA1, 0x01);
    IoBus::writeByte(0x21, 0x0);
    IoBus::writeByte(0xA1, 0x0);
}

/* We first remap the interrupt controllers, and then we install
*  the appropriate ISRs to the correct entries in the IDT. This
*  is just like installing the exception handlers */
void irq_install()
{
    irq_remap();
    register_interrupt_handler(32, (void*)irq0, 0x0, 0x8E);
    register_interrupt_handler(33, (void*)irq1, 0x0, 0x8E);
    register_interrupt_handler(34, (void*)irq2, 0x0, 0x8E);
    register_interrupt_handler(35, (void*)irq3, 0x0, 0x8E);
    register_interrupt_handler(36, (void*)irq4, 0x0, 0x8E);
    register_interrupt_handler(37, (void*)irq5, 0x0, 0x8E);
    register_interrupt_handler(38, (void*)irq6, 0x0, 0x8E);
    register_interrupt_handler(39, (void*)irq7, 0x0, 0x8E);
    register_interrupt_handler(40, (void*)irq8, 0x0, 0x8E);
    register_interrupt_handler(41, (void*)irq9, 0x0, 0x8E);
    register_interrupt_handler(42, (void*)irq10, 0x0, 0x8E);
    register_interrupt_handler(43, (void*)irq11, 0x0, 0x8E);
    register_interrupt_handler(44, (void*)irq12, 0x0, 0x8E);
    register_interrupt_handler(45, (void*)irq13, 0x0, 0x8E);
    register_interrupt_handler(46, (void*)irq14, 0x0, 0x8E);
    register_interrupt_handler(47, (void*)irq15, 0x0, 0x8E);
}