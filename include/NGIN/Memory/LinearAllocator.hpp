#pragma once
#include <NGIN/Memory/IAllocator.hpp>
#include <NGIN/Common/Defines.hpp>
#include <NGIN/Common/Memory/Scope.hpp>

namespace NGIN::Memory
{
    /// @class LinearAllocator
    /// @brief A simple linear (also known as stack or arena) allocator.
    ///
    /// LinearAllocator is a type of allocator that allocates memory by simply incrementing a pointer.
    /// It's extremely fast and has low overhead per allocation, but it doesn't support deallocation of individual blocks.
    /// It's ideal for use cases where you need to allocate a lot of blocks quickly and deallocate them all at once.
    ///
    /// @note This allocator does not support deallocating individual blocks.
    class NGIN_API LinearAllocator : public IAllocator
    {
    public:
        /// @brief Constructs a LinearAllocator with the specified size in bytes.
        LinearAllocator(Size sizeBytes = 1024);

        /// @brief Default destructor.
        ~LinearAllocator() = default;

        /// @brief Copy constructor is deleted because LinearAllocators should not be copied.
        LinearAllocator(const LinearAllocator& other) noexcept = delete;

        /// @brief Copy assignment operator is deleted because LinearAllocators should not be copied.
        LinearAllocator& operator=(const LinearAllocator& other) noexcept = delete;

        /// @brief Move constructor.
        LinearAllocator(LinearAllocator&& other) noexcept;

        /// @brief Move assignment operator.
        LinearAllocator& operator=(LinearAllocator&& other) noexcept;

        /// @brief Allocates a block of memory of the specified size and alignment.
        Void* Allocate(Size size, Size alignment = alignof(std::max_align_t), const std::source_location& location = std::source_location::current()) override;

        /// @brief Deallocating individual allocations is not supported by the linear allocator.
        /// @details Throws an error.
        Void Deallocate(void* ptr) override;

        /// @brief Checks if the specified pointer was allocated by this allocator.
        Bool Owns(void* ptr) const override;

        /// @brief Resets the allocator, deallocating all blocks.
        void Reset();

    private:
        /// @brief The memory owned by the allocator.
        Scope<Byte[]> memory;

        /// @brief The current position in the memory.
        Byte* current;

        /// @brief The end of the memory.
        Byte* end;
    };
}// namespace NGIN::Memory