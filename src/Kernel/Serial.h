#pragma once

#include <stdint.h>

// Maybe add tryRead and tryWrite that return false if can't 
// Change this to class that takes in the port address
namespace Serial
{
    void init();
    void setBaudRateDivisor(uint16_t divisor);

    void write(char chr);
    bool isTransmitEmpty();

    char read();
    bool isDataAvailable();

    static constexpr uint16_t PORT_ADDRESS = 0x3F8;
}