#pragma once
#include <NGIN/Common/Defines.hpp>
#include <NGIN/Memory/IAllocator.hpp>
#include <NGIN/Common/Containers/Vector.hpp>

namespace NGIN::Memory
{

    template<IsAllocator AllocatorT>
    class ExpandingAllocator : public IAllocator
    {
    public:
        ExpandingAllocator(Size sizeBytes = 1024);

        ~ExpandingAllocator() = default;

        ExpandingAllocator(const ExpandingAllocator& other) noexcept = delete;

        ExpandingAllocator& operator=(const ExpandingAllocator& other) noexcept = delete;

        ExpandingAllocator(ExpandingAllocator&& other) noexcept;

        ExpandingAllocator& operator=(ExpandingAllocator&& other) noexcept;

        Void* Allocate(Size size, Size alignment = alignof(std::max_align_t), const std::source_location& location = std::source_location::current()) override;

        Void Deallocate(void* ptr) override;

        Bool Owns(void* ptr) const override;

        void Reset();

    private:
        Vector<AllocatorT> allocators;
        Size currentAllocatorIndex;
    };

    template<IsAllocator AllocatorT>
    inline Void* ExpandingAllocator<AllocatorT>::Allocate(Size size, Size alignment, const std::source_location& location)
    {
        Void* ptr = allocators[currentAllocatorIndex].Allocate(size, alignment, location);
        if (ptr == nullptr)
        {
            ++currentAllocatorIndex;
            if (currentAllocatorIndex >= allocators.size())
                allocators.emplace_back(allocators.back().GetSize() * 2);
        }
        return Allocate(size, alignment, location);
    }
};

}// namespace NGIN::Memory