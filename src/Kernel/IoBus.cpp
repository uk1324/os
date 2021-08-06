#include <Kernel/IoBus.h>

// Inline asm constraints
// "a" - use accumulator register
// "d" - use data register
// "N" - use 8 bit integer constant
// Using "Nd" optimizes for both cases

void IoBus::writeByte(uint16_t portAddress, uint8_t val)
{
    asm volatile (
        "outb %0, %1"
            :
            : "a"(val), "Nd"(portAddress)
    );
}

uint8_t IoBus::readByte(uint16_t portAddress)
{
    uint8_t ret;
    asm volatile (
        "inb %1, %0"
            : "=a"(ret)
            : "Nd"(portAddress)
    );
    return ret;
}
