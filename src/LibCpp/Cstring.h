#pragma once

#include <LibCpp/Types.h>

size_t strlen(const char* string);

void memcpy(void* destination, const void* source, size_t size);
void memset(void* ptr, u8 val, size_t byte_count);