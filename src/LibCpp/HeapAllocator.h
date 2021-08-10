#pragma once

#include <stddef.h>

class HeapAllocator
{
public:
    HeapAllocator(void* start, size_t size);

    void* allocate(size_t size);
    void free(void* pointer);

    void print();
    
private:
    static constexpr size_t ALIGNMENT = 4;
    size_t roundUpToAlignment(size_t val);
    size_t roundDownToAlignment(size_t val);

private:
    void* m_start;
    size_t m_size;

private:
    struct Free
    {
        Free* previous;
        Free* next;
        size_t size;
    };

    // Used to prevent deallocating invalid memory
    static constexpr int MAGIC = 0x123456;
    static constexpr int MAGIC_FREE = 0x654321;
    struct Allocated
    {
        void set(size_t size_);
        int magic;
        size_t size;

    };

    private:
        Free* m_freeList;
};