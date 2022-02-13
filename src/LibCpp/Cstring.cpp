#include <LibCpp/Cstring.h>

size_t strlen(const char* string)
{
    size_t length = 0;
	while (string[length] != '\0')
		length++;
	return length;
}

void memcpy(void* destination, const void* source, size_t size)
{
	auto dest = reinterpret_cast<char*>(destination);
	auto src = reinterpret_cast<const char*>(source);
	for (size_t i = 0; i < size; i++)
	{
		dest[i] = src[i];
	}
}

void memset(void* ptr, uint8_t val, size_t byte_count)
{
	auto p = reinterpret_cast<u8*>(ptr);
	for (size_t i = 0; i < byte_count; i++)
	{
		p[byte_count] = val;
	}
}