#pragma once

#include <stdint.h>
#include <stddef.h>

enum class VgaColor
{
	Black = 0,
	Blue = 1,
	Green = 2,
	Cyan = 3,
	Red = 4,
	Magenta = 5,
	Brown = 6,
	LightGrey = 7,
	DarkGrey = 8,
	LightBlue = 9,
	LightGreen = 10,
	LightCyan = 11,
	LightRed = 12,
	LightMagenta = 13,
	LightBrown = 14,
    White = 15,
};

class VgaTerminal
{
public:
    VgaTerminal();

    void setColor(VgaColor foreground, VgaColor background = VgaColor::Black);
    void putChar(unsigned char chr);
    void write(const char* data, size_t length);
    void writeString(const char* string);
    void moveUp();

    static constexpr uint16_t makeChar(unsigned char chr, VgaColor foreground = VgaColor::White, VgaColor background = VgaColor::Black);

    static void clear();
    static uint16_t getAt(size_t x, size_t y);
    static void setAt(uint16_t chr, size_t x, size_t y);

public:
    static volatile uint16_t* const BUFFER;
    static constexpr size_t WIDTH = 80;
    static constexpr size_t HEIGHT = 25;

    size_t currentX;
    size_t currentY;
    uint16_t currentColor;
};

constexpr uint16_t VgaTerminal::makeChar(unsigned char chr, VgaColor foreground, VgaColor background)
{
    constexpr int FOREGROUND_OFFSET = 8;
    constexpr int BACKGROUND_OFFSET = 12;

    return static_cast<uint16_t>(chr)
        | (static_cast<uint16_t>(background) << BACKGROUND_OFFSET)
        | (static_cast<uint16_t>(foreground) << FOREGROUND_OFFSET);
}