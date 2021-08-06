#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include <LibCpp/Cstring.h>
#include <Kernel/IoBus.h>
#include <Kernel/Terminal/Terminal.h>
// #include ""
// /* Check if the compiler thinks you are targeting the wrong operating system. */
// #if defined(__linux__)
//     #error "You are not using a cross-compiler, you will most certainly run into trouble"
// #endif
 
// /* This tutorial will only work for the 32-bit ix86 targets. */
// #if !defined(__i386__)
//     #error "This tutorial needs to be compiled with a ix86-elf compiler"
// #endif
/* Hardware text mode color constants. */

static inline uint8_t vgaEntryColor(VgaColor foreground, VgaColor background)
{
	return static_cast<uint8_t>(foreground) | static_cast<uint8_t>(background) << 4;
}

static inline uint16_t vgaEntry(unsigned char chr, uint8_t color)
{
	return static_cast<uint16_t>(chr) | static_cast<uint16_t>(color << 8);
}

// size_t stringLength(const char* string)
// {
// 	size_t length = 0;
// 	while (string[length] != '\0')
// 		length++;
// 	return length;
// }

static constexpr size_t VGA_WIDTH = 80;
static constexpr size_t VGA_HEIGHT = 25;

size_t terminalRow;
size_t terminalColumn;
uint8_t terminalColor;
uint16_t* terminalBuffer;

void initTerminal()
{
	terminalRow = 0;
	terminalColumn = 0;
	terminalColor = vgaEntryColor(VgaColor::LightGrey, VgaColor::Black);
	terminalBuffer = reinterpret_cast<uint16_t*>(0xB8000);

	for (size_t y = 0; y < VGA_HEIGHT; y++)
	{
		for (size_t x = 0; x < VGA_WIDTH; x++)
		{
			terminalBuffer[y * VGA_WIDTH + x] = vgaEntry(' ', terminalColor);
		}	
	}
}

void setColor(uint8_t color)
{
	terminalColor = color;
}

void putEntryAt(char chr, uint8_t color, size_t x, size_t y)
{
	terminalBuffer[y * VGA_WIDTH + x] = vgaEntry(chr, color);
}

void putChar(char chr)
{
	if (chr == '\n')
	{
		terminalRow++;
		terminalColumn = 0;
		return;
	}
	else
	{
		putEntryAt(chr, terminalColor, terminalColumn, terminalRow);	
	}
	terminalColumn++;


	if (terminalColumn == VGA_WIDTH)
	{
		terminalRow++;
		terminalColumn = 0;
		if (terminalRow == VGA_HEIGHT)
			terminalRow = 0;
	}
}

void write(const char* data, size_t size)
{
	for (size_t i = 0; i < size; i++)
	{
		putChar(data[i]);
	}
}

void writeString(const char* string)
{
	write(string, strLen(string));
}

// void outb(volatile char* addr, unsigned int value)
// {
// 	(*reinterpret_cast<volatile unsigned char*>(addr)) = static_cast<unsigned char>(value);
// }

// unsigned char inb(volatile char* addr)
// {
// 	return (*reinterpret_cast<volatile unsigned char*>(addr));
// }

static inline void outb(uint16_t port, uint8_t val)
{
    asm volatile ( "outb %0, %1" : : "a"(val), "Nd"(port) );
    /* There's an outb %al, $imm8  encoding, for compile-time constant port numbers that fit in 8b.  (N constraint).
     * Wider immediate constants would be truncated at assemble-time (e.g. "i" constraint).
     * The  outb  %al, %dx  encoding is the only option for all other cases.
     * %1 expands to %dx because  port  is a uint16_t.  %w1 could be used if we had the port number a wider C type */
}

static inline uint8_t inb(uint16_t port)
{
    uint8_t ret;
    asm volatile ( "inb %1, %0"
                   : "=a"(ret)
                   : "Nd"(port) );
    return ret;
}

auto PORT = static_cast<uint16_t>(0x3F8);

int is_transmit_empty() {
	return inb(PORT + 5) & 0x20;
}

void write_serial(char a) {
	while (is_transmit_empty() == 0);

	IoBus::writeByte(PORT, a);
	outb(PORT,a);
}

int serial_received() {
	return inb(PORT + 5) & 1;
}

char read_serial() {
	while (serial_received() == 0);

	return inb(PORT);
}

extern "C" void main()
{
// 	initTerminal();

// 	outb(PORT + 1, 0x00);    // Disable all interrupts
// 	outb(PORT + 3, 0x80);    // Enable DLAB (set baud rate divisor)
// 	outb(PORT + 0, 0x03);    // Set divisor to 3 (lo byte) 38400 baud
// 	outb(PORT + 1, 0x00);    //                  (hi byte)
// 	outb(PORT + 3, 0x03);    // 8 bits, no parity, one stop bit
// 	outb(PORT + 2, 0xC7);    // Enable FIFO, clear them, with 14-byte threshold
// 	outb(PORT + 4, 0x0B);    // IRQs enabled, RTS/DSR set
// 	outb(PORT + 4, 0x1E);    // Set in loopback mode, test the serial chip
// 	outb(PORT + 0, 0xAE);    // Test serial chip (send byte 0xAE and check if serial returns same byte)
 
//    // Check if serial is faulty (i.e: not same byte as sent)
// 	if (inb(PORT + 0) != 0xAE) {
// 		putEntryAt('1', vgaEntryColor(VgaColor::White, VgaColor::Black), 0, 0);
// 	}

	VgaTerminal terminal;

	// terminal.setColor(VgaColor::White, VgaColor::Black);
	// terminal.writeString("abc");

	for (int i = 1; i < 40; i++)
	{
		// terminal.writeString("Hello");
		for (int j = 0; j < i; j++)
		{
			terminal.putChar('\\');
			terminal.putChar('*');
			terminal.putChar('/');
			// terminal.writeString("Hello");
		}

		terminal.putChar('\n');
	}

	// VgaTerminal::putAt(VgaTerminal::makeChar('^'), 40, 10);
	// terminal.moveUp();
	// terminal.moveUp();
	// terminal.moveUp();

	// for (int i = 1; i < 4; i++)
	// {
	// 	for (int j = 0; j < i; j++)
	// 	{
	// 		terminal.putChar('*');
	// 	}
	// 	terminal.putChar('\n');
	// }

	// putEntryAt('2', VgaTerminal::makeChar(' ', VgaColor::White, VgaColor::Black), 0, 0);	
	// VgaTerminal::putAt(VgaTerminal::makeChar('2', VgaColor::White, VgaColor::Black), 0, 0);
   // If serial is not faulty set it in normal operation mode
   // (not-loopback with IRQs enabled and OUT#1 and OUT#2 bits enabled)
	// outb(PORT + 4, 0x0F);
 

	// if (is_transmit_empty())
	// {
	// 	write_serial('a');
	// 	write_serial('b');
	// 	write_serial('c');
	// 	write_serial('d');
	// 	write_serial('e');
	// 	write_serial('f');
	// }
	// else
	// {
	// 	putEntryAt('2', vgaEntryColor(VgaColor::White, VgaColor::Black), 0, 0);	
	// }

	// while (true)
	// {
	// 	putEntryAt(read_serial(), vgaEntryColor(VgaColor::White, VgaColor::Black), 0, 0);	
	// }

	// putEntryAt('0', vgaEntryColor(VgaColor::White, VgaColor::Black), 0, 0);

	// while (true)
	// {
	// 	putEntryAt(*COM1, vgaEntryColor(VgaColor::White, VgaColor::Black), 0, 0);
	// }
	

	// initTerminal();
	// setColor(vgaEntryColor(VgaColor::Red, VgaColor::Black));
	// writeString("Hello world\n");
	// writeString("Hello world\n");
	// writeString("Hello world\n");
	// writeString("Hello world\n");

	// for (int i = 0; i < 255; i++)
	// {
	// 	putChar(static_cast<char>(i));
	// }
}