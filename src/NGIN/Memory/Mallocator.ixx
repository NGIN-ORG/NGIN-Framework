module;
#include <stdlib.h>
export module NGIN.Memory:Mallocator;

export import NGIN.Types;
import :IAllocator;
namespace NGIN::Memory
{
    /// @brief Interface for memory allocators
    export class Mallocator : public IAllocator
    {
    public:
        ~Mallocator() = default;

        /// @brief Allocates memory using malloc.
        /// @details
        /// @param size The size of the memory to allocate.
        /// @param alignment The alignment of the memory to allocate.
        /// @return A pointer to the allocated memory.
        [[nodiscard]] virtual void* Allocate(const Size size, const Size alignment) override
        {
#if defined(NGIN_PLATFORM_WINDOWS)
            return _aligned_malloc(size, alignment);
#else
            void* ptr;
            posix_memalign(&ptr, alignment, size);
            return ptr;
#endif
        }

        virtual void Deallocate(void* ptr) override
        {
#if defined(NGIN_PLATFORM_WINDOWS)
            _aligned_free(ptr);
#else
            free(ptr);
#endif
        }

        virtual void Reset() override
        {
            return;
        }

        /// @brief Checks if the allocator owns the given pointer.
        /// @details The assumption is that this allocator always owns the pointer, as there is not way to know for sure.
        /// @param ptr The pointer to check.
        /// @return Always returns true.
        [[nodiscard]] virtual bool Owns(const void* ptr) override
        {
            return true;
        }
    };
}// namespace NGIN::Memory