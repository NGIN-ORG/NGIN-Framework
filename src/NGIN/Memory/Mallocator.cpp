#include <NGIN/Memory/Mallocator.hpp>
#include <cstdio>
#include <cstdlib>
namespace NGIN::Memory
{
    Void* Mallocator::Allocate(Size size, Size alignment, const std::source_location& location)
    {
#if defined(NGIN_PLATFORM_WINDOWS)
        return _aligned_malloc(size, alignment);
#else
        void* ptr;
        posix_memalign(&ptr, alignment, size);
        return ptr;
#endif
    }

    Void Mallocator::Deallocate(Void* ptr)
    {
#if defined(_MSC_VER)
        _aligned_free(ptr);
#else
        free(ptr);
#endif
    }

    Bool Mallocator::Owns(Void* ptr) const
    {
        return true;// Assume true, since Mallocator should be used as a fallback allocator
    }
}// namespace NGIN::Memory