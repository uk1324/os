// make kprint use a static function variable

#include <Kernel/VgaTerminal.h>
#include <LibCpp/Cstring.h>

volatile uint16_t* const VgaTerminal::BUFFER = reinterpret_cast<volatile uint16_t*>(0xB8000);

VgaTerminal::VgaTerminal()
    : currentX(0)
    , currentY(0)
    , currentColor(makeChar(' ', VgaColor::White, VgaColor::Black))
{
    clear();
}

// uint16_t VgaTerminal::makeChar(char chr, VgaColor foreground, VgaColor background)
// {
//     static constexpr int FOREGROUND_OFFSET = 8;
//     static constexpr int BACKGROUND_OFFSET = 12;

//     return static_cast<uint16_t>(chr)
//         | (static_cast<uint16_t>(background) << BACKGROUND_OFFSET)
//         | (static_cast<uint16_t>(foreground) << FOREGROUND_OFFSET);
// }

void VgaTerminal::clear()
{
    // Maybe make this constexpr
    constexpr uint16_t EMPTY_CHAR = makeChar(' ', VgaColor::White, VgaColor::Black);
    for (size_t y = 0; y < HEIGHT; y++)
    {
        for (size_t x = 0; x < WIDTH; x++)
        {
            putAt(EMPTY_CHAR, x, y);
        }
    }
}

void VgaTerminal::putAt(uint16_t chr, size_t x, size_t y)
{
    BUFFER[y * WIDTH + x] = chr;
}

uint16_t VgaTerminal::getAt(size_t x, size_t y)
{
    return BUFFER[y * WIDTH + x];
}

void VgaTerminal::setColor(VgaColor foreground, VgaColor background)
{
    currentColor = makeChar(' ', foreground, background);
}

void VgaTerminal::putChar(char chr)
{
    if (chr == '\n')
    {
        currentX = 0;
        currentY++;

        if (currentY >= HEIGHT)
        {
            moveUp();
        }
    }
    else
    {
        putAt(
            static_cast<uint16_t>(chr) | currentColor,
            currentX, currentY
        );    
        currentX++;   

        if (currentX >= WIDTH)
        {
            currentX = 0;
            currentY++;

            if (currentY >= HEIGHT)
            {
                moveUp();
            }
        }
    }
}

void VgaTerminal::write(const char* data, size_t length)
{
    for (size_t i = 0; i < length; i++)
        putChar(data[i]);
}

void VgaTerminal::writeString(const char* string)
{
    write(string, strLen(string));
}

void VgaTerminal::moveUp()
{
    currentY--;
    currentX = 0;

    // Don't know is copying halfwords is better or worse than bytes
    for (size_t y = 1; y < HEIGHT; y++)
    {
        for (size_t x = 0; x < WIDTH; x++)
        {
            putAt(getAt(x, y), x, y - 1);
        }   
    }

    constexpr uint16_t EMPTY_CHAR = makeChar(' ', VgaColor::White, VgaColor::Black);

    for (size_t x = 0; x < WIDTH; x++)
    {
        putAt(EMPTY_CHAR, x, HEIGHT - 1);
    }   
}