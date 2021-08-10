#include "Cstring.h"

size_t strLen(const char* string)
{
    size_t length = 0;
	while (string[length] != '\0')
		length++;
	return length;
}

void memCpy(void* destination, const void* source, size_t size)
{
	char* dest = reinterpret_cast<char*>(destination);
	const char* src = reinterpret_cast<char*>(destination);
	for (size_t i = 0; i < size; i++)
	{
		dest[i] = src[i];
	}
}