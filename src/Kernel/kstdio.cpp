#include <Kernel/kstdio.h>
#include <Kernel/Serial.h>

#include <LibC/stdlib.h>

#include <stdarg.h>

#include <Kernel/VgaTerminal.h>

#include <LibCpp/TypeTraits.h>

void kputchar(char chr)
{
    Serial::write(chr);
}

static void printString(const char* string);
namespace
{
    template <typename Int>
    struct WriteIntToBufferConfig
    {
        Int value;
        char* buffer;
        int base;
        bool hexUppercase;
    };
}
template <typename Int>
static char* writeIntToBuffer(WriteIntToBufferConfig<Int> parameters);

void kprintf(const char* format, ...)
{
    va_list args;
    va_start(args, format);

    const char* current = format;

    while (*current != '\0')
    {
        // Every bit + NULL;
        static constexpr size_t MAX_INT_STRING_LENGTH = sizeof(long long) * 8 + 1;

        if (*current == '%')
        {
            current++;

            switch (*current)
            {
                case 's':
                    printString(va_arg(args, const char*));
                    current++;
                    break;

                case 'd':
                {
                    char buffer[MAX_INT_STRING_LENGTH];
                    writeIntToBuffer<int>({
                        .value = va_arg(args, int),
                        .buffer = buffer,
                        .base = 10,
                        .hexUppercase = false
                    });
                    printString(buffer);
                    current++;
                    break;
                }

                case 'h':
                {
                    char buffer[MAX_INT_STRING_LENGTH];
                    writeIntToBuffer<int>({
                        .value = va_arg(args, int),
                        .buffer = buffer,
                        .base = 16,
                        .hexUppercase = false
                    });
                    printString(buffer);
                    current++;
                    break;
                }

                case 'H':
                {
                    char buffer[MAX_INT_STRING_LENGTH];
                    writeIntToBuffer<int>({
                        .value = va_arg(args, int),
                        .buffer = buffer,
                        .base = 16,
                        .hexUppercase = true
                    });
                    printString(buffer);
                    current++;
                    break;
                }

                case '%':
                    kputchar('%');
                    current++;
                    break;
            }
        }
        else
        {
            kputchar(*current);
            current++;
        }
    }

    va_end(args);
}

static void printString(const char* string)
{
    while (*string != '\0')
    {
        kputchar(*string);
        string++;
    }
}

template <typename Int>
static char* writeIntToBuffer(WriteIntToBufferConfig<Int> parameters)
{
    auto& [value, buffer, base, hexUppercase] = parameters;

    char* current = buffer;
    char* start = current;

    if (value == 0)
    {
        *current = '0';
        current++;
        *current = '\0';
        return buffer;
    }

    bool isNegative = false;
    // Treat all non base 10 numbers as unsigned
    if ((base == 10) && (value < 0))
    {
        isNegative = true;
        value = -value;
    }

    char toDigitUppercase[] = "0123456789ABCDEF";
    char toDigitLowercase[] = "0123456789abcdef";

    char* digitToChar = hexUppercase ? toDigitUppercase : toDigitLowercase;

    MakeUnsignedT<Int> val = value;

    while (val != 0)
    {
        *current = digitToChar[val % base];
        current++;
        val /= base;
    }

    if (isNegative)
    {
        *current = '-';
        current++;
    }

    for (int i = 0; i < (current - start) / 2; i++)
    {
        char temp = current[-i - 1];
        current[-i - 1] = start[i];
        start[i] = temp;
    }


    *current = '\0';

    return buffer;
}