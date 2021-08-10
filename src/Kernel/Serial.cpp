#include <Kernel/Serial.h>
#include <Kernel/IoBus.h>

// Use enums for bit count
// rename write to send

void Serial::init()
{
    IoBus::writeByte(PORT_ADDRESS + 1, 0x00);    // Disable all interrupts
    IoBus::writeByte(PORT_ADDRESS + 3, 0x80);    // Enable DLAB (set baud rate divisor)
    IoBus::writeByte(PORT_ADDRESS + 0, 0x03);    // Set divisor to 3 (lo byte) 38400 baud
    IoBus::writeByte(PORT_ADDRESS + 1, 0x00);    //                  (hi byte)
    IoBus::writeByte(PORT_ADDRESS + 3, 0x03);    // 8 bits, no parity, one stop bit
    IoBus::writeByte(PORT_ADDRESS + 2, 0xC7);    // Enable FIFO, clear them, with 14-byte threshold
    IoBus::writeByte(PORT_ADDRESS + 4, 0x0B);    // IRQs enabled, RTS/DSR set
    IoBus::writeByte(PORT_ADDRESS + 4, 0x1E);    // Set in loopback mode, test the serial chip
    IoBus::writeByte(PORT_ADDRESS + 0, 0xAE);    // Test serial chip (send byte 0xAE and check if serial returns same byte)

    // Check if serial is faulty (i.e: not same byte as sent)
    if (IoBus::readByte(PORT_ADDRESS + 0) != 0xAE) {
        // VgaTerminal::setAt(VgaTerminal::makeChar('1'), 0, 0);
        // putEntryAt('1', vgaEntryColor(VgaColor::White, VgaColor::Black), 0, 0);
    }

    // If serial is not faulty set it in normal operation mode
    // (not-loopback with IRQs enabled and OUT#1 and OUT#2 bits enabled)
    IoBus::writeByte(PORT_ADDRESS + 4, 0x0F);
}

void Serial::write(char chr)
{
    while (isTransmitEmpty() == false)
        ;

    IoBus::writeByte(PORT_ADDRESS, chr);
}

bool Serial::isTransmitEmpty()
{
	return IoBus::readByte(PORT_ADDRESS + 5) & 0x20;
}

char Serial::read()
{
    while (isDataAvailable() == false)
        ;

    return IoBus::readByte(PORT_ADDRESS);
}

bool Serial::isDataAvailable()
{
    return IoBus::readByte(PORT_ADDRESS + 5) & 1;
}