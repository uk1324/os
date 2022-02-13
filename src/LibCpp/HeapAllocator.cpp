#include <LibCpp/HeapAllocator.h>

HeapAllocator::HeapAllocator(void* start, size_t size)
    : m_start(start)
    , m_size(size)
{
    if (size < sizeof(Free))
    {
        m_freeList = nullptr;   
    }
    else
    {
        m_freeList = reinterpret_cast<Free*>(roundUpToAlignment(reinterpret_cast<size_t>(start)));
        m_freeList->size = roundDownToAlignment(size - sizeof(Free));
        m_freeList->next = nullptr;
        m_freeList->previous = nullptr;
    }
}

#include <Kernel/VgaTerminal.h>

void* HeapAllocator::allocate(size_t size)
{
    if (size == 0)
    {
        return nullptr;
    }

    Free* free = m_freeList;

    while (free != nullptr)
    {
        size_t allocationSize = roundUpToAlignment(size);
        if ((free->size >= allocationSize + sizeof(Allocated)))
        {
            Allocated* allocation = reinterpret_cast<Allocated*>(reinterpret_cast<char*>(free) + sizeof(Free));
            // Enough space to allocate but not enough to indicate free memory
            if (free->size < allocationSize + sizeof(Allocated) + sizeof(Free))
            {
                // Take all memory in free segment
                allocationSize = free->size - sizeof(Allocated);
                allocation->set(allocationSize);
                free->size = 0;
                return reinterpret_cast<char*>(allocation) + sizeof(Allocated);
            }

            allocation->set(allocationSize); 
    
            Free* nextFree = reinterpret_cast<Free*>(
                reinterpret_cast<char*>(allocation) + sizeof(Allocated) + allocation->size
            );

            if (free->next == nullptr)
            {
                free->next = nextFree;
                nextFree->previous = free;
                nextFree->next = nullptr;
                nextFree->size = free->size - allocation->size - sizeof(Allocated) - sizeof(Free);
                free->size = 0;
                return reinterpret_cast<char*>(allocation) + sizeof(Allocated);
            }

            free->next->previous = nextFree;
            nextFree->next = free->next;
            nextFree->previous = free;
            free->next = nextFree;
            nextFree->size = free->size - allocation->size - sizeof(Allocated) - sizeof(Free);
            free->size = 0;
            return reinterpret_cast<char*>(allocation) + sizeof(Allocated);

            // if (free->next == nullptr)
            // {
            //     free->next = nextFree;
            //     nextFree->previous = free;
            //     nextFree->next = nullptr;
            //     nextFree->size = free->size - size - sizeof(Allocated) - sizeof(Free);
            //     free->size = 0;
            //     return reinterpret_cast<char*>(allocation) + sizeof(Allocated);
            // }

            // free->next->previous = nextFree;
            // nextFree->next = free->next;
            // nextFree->previous = free;
            // free->next = nextFree;
            // nextFree->size = free->size - size - sizeof(Allocated) - sizeof(Free);
            // free->size = 0;
            // return reinterpret_cast<char*>(allocation) + sizeof(Allocated);
        }
        
        free = free->next;
    }
    
    return nullptr;
}

void HeapAllocator::free(void* pointer)
{
    if (pointer == nullptr)
    {
        return;
    }

    // Check if aligned
    Allocated* memory = reinterpret_cast<Allocated*>(reinterpret_cast<char*>(pointer) - sizeof(Allocated));
    if (memory->magic != MAGIC)
    {
        return;
    }

    memory->magic = MAGIC_FREE;
    Free* freed = reinterpret_cast<Free*>(reinterpret_cast<char*>(memory) - sizeof(Free));

    freed->size = memory->size + sizeof(Allocated);

    // Try to merge free memory
    if ((freed->previous != nullptr) && (freed->previous->size > 0))
    {
        freed->previous->size += freed->size + sizeof(Free);
        freed->previous->next = freed->next;
        if (freed->next != nullptr)
        {
            freed->next->previous = freed->previous;
        }
        freed = freed->previous;
    }

    if ((freed->next != nullptr) && (freed->next->size > 0))
    {
        freed->size += freed->next->size + sizeof(Free);
        if (freed->next->next != nullptr)
        {
            freed->next->next->previous = freed;
        }
        freed->next = freed->next->next;
    }
}

void HeapAllocator::Allocated::set(size_t size_)
{
    size = size_;
    magic = MAGIC;
}

// All major compilers optimize the division away even at -O0
size_t HeapAllocator::roundUpToAlignment(size_t val)
{
    size_t unalignment = (val % ALIGNMENT);
    return unalignment == 0
        ? val
        : val + (ALIGNMENT - unalignment);
}

size_t HeapAllocator::roundDownToAlignment(size_t val)
{
    return val - (val % ALIGNMENT);
}

void HeapAllocator::print()
{
    VgaTerminal terminal;

    Free* free = m_freeList;

    while (true)
    {
        terminal.setColor(VgaColor::Blue);
        for (size_t i = 0; i < sizeof(Free); i++)
        {
            terminal.putChar(254);
        }

        terminal.setColor(VgaColor::Green);
        for (size_t i = 0; i < free->size; i++)
        {
            terminal.putChar(254);
        }


        if (free->next == nullptr)
            break;

        if (free->size == 0)
        {
            Allocated* allocated = reinterpret_cast<Allocated*>(reinterpret_cast<char*>(free) + sizeof(Free));
            if (allocated->magic != MAGIC)
            {
                terminal.putChar('*');
            }
            
            terminal.setColor(VgaColor::Brown);
            for (size_t i = 0; i < sizeof(Allocated); i++)
            {
                terminal.putChar(static_cast<char>(254));
            }

            terminal.setColor(VgaColor::Red);
            for (size_t i = 0; i < allocated->size; i++)
            {
                terminal.putChar(static_cast<char>(254));
            }

        }

        free = free->next;
    }
}