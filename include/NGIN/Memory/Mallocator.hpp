#pragma once

#include <NGIN/Memory/IAllocator.hpp>


namespace NGIN::Memory
{
    /// @class Mallocator
    /// @brief An allocator that uses malloc and free to allocate and deallocate memory.
    /// @details
    /// This allocator is designed to be used as a general purpose allocator, and is not intended to be used for high performance or specialized use cases.
    /// Can also work as a fallback allocator if a more specialized allocator fails to allocate memory.
    /// @note This allocator cannot be reset, as there is no way to track the memory that has been allocated.
    class NGIN_API Mallocator : public IAllocator
    {
    public:
        Mallocator() {}

        explicit Mallocator(Size totalSize) {}

        ~Mallocator() override = default;

        /// @brief Allocates memory using malloc.
        /// @details
        /// @param size The size of the memory to allocate.
        /// @param alignment The alignment of the memory to allocate.
        /// @return A pointer to the allocated memory.
        [[nodiscard]] void* Allocate(const Size size, const Size alignment) override;

        void Deallocate(void* ptr) override;

        void Reset() override;


        /// @brief Checks if the allocator owns the given pointer.
        /// @details The assumption is that this allocator always owns the pointer, as there is not way to know for sure.
        /// @param ptr The pointer to check.
        /// @return Always returns true.
        [[nodiscard]] bool Owns(const void* ptr) override;
    };
}// namespace NGIN::Memory
