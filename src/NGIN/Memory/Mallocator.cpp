#include <NGIN/Memory/Mallocator.hpp>
#include <stdlib.h>

namespace NGIN::Memory
{


    void* Mallocator::Allocate(const Size size, const Size alignment)
    {
#if defined(NGIN_PLATFORM_WINDOWS)
        return _aligned_malloc(size, alignment);
#else
            void* ptr;
            posix_memalign(&ptr, alignment, size);
            return ptr;
#endif
    }

    void Mallocator::Deallocate(void* ptr)
    {
#if defined(NGIN_PLATFORM_WINDOWS)
        _aligned_free(ptr);
#else
            free(ptr);
#endif
    }

    void Mallocator::Reset()
    {
        return;
    }


    bool Mallocator::Owns(const void* ptr)
    {
        return true;
    }
};

