#pragma once

#include <stdint.h>

// Maybe add tryRead and tryWrite that return false if can't 
namespace Serial
{
    void init();

    void write(char chr);
    bool isTransmitEmpty();

    char read();
    bool isDataAvailable();

    static constexpr uint16_t PORT_ADDRESS = 0x3F8;
}