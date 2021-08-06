#include <Kernel/Serial.h>
#include <Kernel/IoBus.h>

namespace Serial
{
    // COM1 address
    static constexpr uint16_t PORT_ADDRESS = 0x3F8;

    void init();
    void write(char val);
    char read();
}