#pragma once
#include <NGIN/Memory/IAllocator.hpp>
#include <NGIN/Common/Defines.hpp>

namespace NGIN::Memory
{
    /// @class Mallocator
    /// @brief A memory allocator that uses the standard malloc and free functions.
    /// @details This class implements the IAllocator interface. It should be used as a fallback allocator.
    class NGIN_API Mallocator : public IAllocator
    {
    public:
        Mallocator() = default;
        ~Mallocator() = default;
        Mallocator(const Mallocator& other) noexcept = delete;
        Mallocator& operator=(const Mallocator& other) noexcept = delete;
        Mallocator(Mallocator&& other) noexcept = default;
        Mallocator& operator=(Mallocator&& other) noexcept = default;

        Void* Allocate(Size size, Size alignment = alignof(std::max_align_t), const std::source_location& location = std::source_location::current()) override;

        Void Deallocate(void* ptr) override;

        /// @brief Checks if the allocator owns a block of memory.
        /// @param ptr A pointer to the block of memory to check.
        /// @return Always returns true, since Mallocator should be used as a fallback allocator.
        Bool Owns(void* ptr) const override;
    };
}// namespace NGIN::Memory