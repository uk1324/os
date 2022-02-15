#include <stdint.h>

void irq_install();

/**
 *  @brief Single idt entry which represents an interrupt
 */
struct __attribute((packed)) idt_entry {
    uint16_t offset_lo;    ///< base address bits 0..15
    uint16_t selector;     ///< code segment selector, typically 0x08
    uint8_t  ist;          ///< bits 0..2 holds Interrupt Stack Table offset, rest of bits zero
    uint8_t  type_attr;    ///< types and attributes
    uint16_t offset_mid;   ///< base address bits 16..31
    uint32_t offset_hi;    ///< base address bits 32..63
    uint32_t zero;         ///< reserved
};

/**
 *  @brief Pointer to idt table array, which can be loaded with the lidt instruction
 */
struct __attribute((packed)) idt_ptr_t {
    uint16_t size;         ///< size of whole idt
    uint64_t address;      ///< address to idt
} ;

/**
 *  @brief Initializes the ivt-table
 */
void idt_init();

/**
 *  @brief Loads the ivt-table to be available for the cpu
 */
void idt_load();

extern "C" void isr0(void);
extern "C" void isr1(void);
extern "C" void isr2(void);
extern "C" void isr3(void);
extern "C" void isr4(void);
extern "C" void isr5(void);
extern "C" void isr6(void);
extern "C" void isr7(void);
extern "C" void isr8(void);
extern "C" void isr9(void);
extern "C" void isr10(void);
extern "C" void isr11(void);
extern "C" void isr12(void);
extern "C" void isr13(void);
extern "C" void isr14(void);
extern "C" void isr15(void);
extern "C" void isr16(void);
extern "C" void isr17(void);
extern "C" void isr18(void);
extern "C" void isr19(void);
extern "C" void isr20(void);
extern "C" void isr21(void);
extern "C" void isr22(void);
extern "C" void isr23(void);
extern "C" void isr24(void);
extern "C" void isr25(void);
extern "C" void isr26(void);
extern "C" void isr27(void);
extern "C" void isr28(void);
extern "C" void isr29(void);
extern "C" void isr30(void);
extern "C" void isr31(void);
// extern "C" void isr32(void);
// extern "C" void isr33(void);
// extern "C" void isr34(void);
// extern "C" void isr35(void);
// extern "C" void isr36(void);
// extern "C" void isr37(void);
// extern "C" void isr38(void);
// extern "C" void isr39(void);
// extern "C" void isr40(void);
// extern "C" void isr41(void);
// extern "C" void isr42(void);
// extern "C" void isr43(void);
// extern "C" void isr44(void);
// extern "C" void isr45(void);
// extern "C" void isr46(void);
// extern "C" void isr47(void);
// extern "C" void isr48(void);
// extern "C" void isr49(void);
// extern "C" void isr50(void);
// extern "C" void isr51(void);
// extern "C" void isr52(void);
// extern "C" void isr53(void);
// extern "C" void isr54(void);
// extern "C" void isr55(void);
// extern "C" void isr56(void);
// extern "C" void isr57(void);
// extern "C" void isr58(void);
// extern "C" void isr59(void);
// extern "C" void isr60(void);
// extern "C" void isr61(void);
// extern "C" void isr62(void);
// extern "C" void isr63(void);
// extern "C" void isr64(void);
// extern "C" void isr65(void);
// extern "C" void isr66(void);
// extern "C" void isr67(void);
// extern "C" void isr68(void);
// extern "C" void isr69(void);
// extern "C" void isr70(void);
// extern "C" void isr71(void);
// extern "C" void isr72(void);
// extern "C" void isr73(void);
// extern "C" void isr74(void);
// extern "C" void isr75(void);
// extern "C" void isr76(void);
// extern "C" void isr77(void);
// extern "C" void isr78(void);
// extern "C" void isr79(void);
// extern "C" void isr80(void);
// extern "C" void isr81(void);
// extern "C" void isr82(void);
// extern "C" void isr83(void);
// extern "C" void isr84(void);
// extern "C" void isr85(void);
// extern "C" void isr86(void);
// extern "C" void isr87(void);
// extern "C" void isr88(void);
// extern "C" void isr89(void);
// extern "C" void isr90(void);
// extern "C" void isr91(void);
// extern "C" void isr92(void);
// extern "C" void isr93(void);
// extern "C" void isr94(void);
// extern "C" void isr95(void);
// extern "C" void isr96(void);
// extern "C" void isr97(void);
// extern "C" void isr98(void);
// extern "C" void isr99(void);
// extern "C" void isr100(void);
// extern "C" void isr101(void);
// extern "C" void isr102(void);
// extern "C" void isr103(void);
// extern "C" void isr104(void);
// extern "C" void isr105(void);
// extern "C" void isr106(void);
// extern "C" void isr107(void);
// extern "C" void isr108(void);
// extern "C" void isr109(void);
// extern "C" void isr110(void);
// extern "C" void isr111(void);
// extern "C" void isr112(void);
// extern "C" void isr113(void);
// extern "C" void isr114(void);
// extern "C" void isr115(void);
// extern "C" void isr116(void);
// extern "C" void isr117(void);
// extern "C" void isr118(void);
// extern "C" void isr119(void);
// extern "C" void isr120(void);
// extern "C" void isr121(void);
// extern "C" void isr122(void);
// extern "C" void isr123(void);
// extern "C" void isr124(void);
// extern "C" void isr125(void);
// extern "C" void isr126(void);
// extern "C" void isr127(void);
// extern "C" void isr128(void);
// extern "C" void isr129(void);
// extern "C" void isr130(void);
// extern "C" void isr131(void);
// extern "C" void isr132(void);
// extern "C" void isr133(void);
// extern "C" void isr134(void);
// extern "C" void isr135(void);
// extern "C" void isr136(void);
// extern "C" void isr137(void);
// extern "C" void isr138(void);
// extern "C" void isr139(void);
// extern "C" void isr140(void);
// extern "C" void isr141(void);
// extern "C" void isr142(void);
// extern "C" void isr143(void);
// extern "C" void isr144(void);
// extern "C" void isr145(void);
// extern "C" void isr146(void);
// extern "C" void isr147(void);
// extern "C" void isr148(void);
// extern "C" void isr149(void);
// extern "C" void isr150(void);
// extern "C" void isr151(void);
// extern "C" void isr152(void);
// extern "C" void isr153(void);
// extern "C" void isr154(void);
// extern "C" void isr155(void);
// extern "C" void isr156(void);
// extern "C" void isr157(void);
// extern "C" void isr158(void);
// extern "C" void isr159(void);
// extern "C" void isr160(void);
// extern "C" void isr161(void);
// extern "C" void isr162(void);
// extern "C" void isr163(void);
// extern "C" void isr164(void);
// extern "C" void isr165(void);
// extern "C" void isr166(void);
// extern "C" void isr167(void);
// extern "C" void isr168(void);
// extern "C" void isr169(void);
// extern "C" void isr170(void);
// extern "C" void isr171(void);
// extern "C" void isr172(void);
// extern "C" void isr173(void);
// extern "C" void isr174(void);
// extern "C" void isr175(void);
// extern "C" void isr176(void);
// extern "C" void isr177(void);
// extern "C" void isr178(void);
// extern "C" void isr179(void);
// extern "C" void isr180(void);
// extern "C" void isr181(void);
// extern "C" void isr182(void);
// extern "C" void isr183(void);
// extern "C" void isr184(void);
// extern "C" void isr185(void);
// extern "C" void isr186(void);
// extern "C" void isr187(void);
// extern "C" void isr188(void);
// extern "C" void isr189(void);
// extern "C" void isr190(void);
// extern "C" void isr191(void);
// extern "C" void isr192(void);
// extern "C" void isr193(void);
// extern "C" void isr194(void);
// extern "C" void isr195(void);
// extern "C" void isr196(void);
// extern "C" void isr197(void);
// extern "C" void isr198(void);
// extern "C" void isr199(void);
// extern "C" void isr200(void);
// extern "C" void isr201(void);
// extern "C" void isr202(void);
// extern "C" void isr203(void);
// extern "C" void isr204(void);
// extern "C" void isr205(void);
// extern "C" void isr206(void);
// extern "C" void isr207(void);
// extern "C" void isr208(void);
// extern "C" void isr209(void);
// extern "C" void isr210(void);
// extern "C" void isr211(void);
// extern "C" void isr212(void);
// extern "C" void isr213(void);
// extern "C" void isr214(void);
// extern "C" void isr215(void);
// extern "C" void isr216(void);
// extern "C" void isr217(void);
// extern "C" void isr218(void);
// extern "C" void isr219(void);
// extern "C" void isr220(void);
// extern "C" void isr221(void);
// extern "C" void isr222(void);
// extern "C" void isr223(void);
// extern "C" void isr224(void);
// extern "C" void isr225(void);
// extern "C" void isr226(void);
// extern "C" void isr227(void);
// extern "C" void isr228(void);
// extern "C" void isr229(void);
// extern "C" void isr230(void);
// extern "C" void isr231(void);
// extern "C" void isr232(void);
// extern "C" void isr233(void);
// extern "C" void isr234(void);
// extern "C" void isr235(void);
// extern "C" void isr236(void);
// extern "C" void isr237(void);
// extern "C" void isr238(void);
// extern "C" void isr239(void);
// extern "C" void isr240(void);
// extern "C" void isr241(void);
// extern "C" void isr242(void);
// extern "C" void isr243(void);
// extern "C" void isr244(void);
// extern "C" void isr245(void);
// extern "C" void isr246(void);
// extern "C" void isr247(void);
// extern "C" void isr248(void);
// extern "C" void isr249(void);
// extern "C" void isr250(void);
// extern "C" void isr251(void);
// extern "C" void isr252(void);
// extern "C" void isr253(void);
// extern "C" void isr254(void);
// extern "C" void isr255(void);
