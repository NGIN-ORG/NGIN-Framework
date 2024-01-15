#pragma once
#include <NGIN/Memory/IAllocator.hpp>
#include <NGIN/Common/Defines.hpp>
#include <NGIN/Common/Memory/Scope.hpp>

namespace NGIN::Memory
{
    class NGIN_API LinearAllocator : public IAllocator
    {
    public:
        LinearAllocator(Size sizeBytes = 1024);
        ~LinearAllocator() = default;
        LinearAllocator(const LinearAllocator& other) noexcept = delete;
        LinearAllocator& operator=(const LinearAllocator& other) noexcept = delete;
        LinearAllocator(LinearAllocator&& other) noexcept;
        LinearAllocator& operator=(LinearAllocator&& other) noexcept;

        Void* Allocate(Size size, Size alignment = alignof(std::max_align_t), const std::source_location& location = std::source_location::current()) override;

        Void Deallocate(void* ptr) override;

        Bool Owns(void* ptr) const override;

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