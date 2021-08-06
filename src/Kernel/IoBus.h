#pragma once

#include <stdint.h>

namespace IoBus
{
    void writeByte(uint16_t portAddress, uint8_t val);
    uint8_t readByte(uint16_t portAddress);
}