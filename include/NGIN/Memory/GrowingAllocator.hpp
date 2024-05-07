
#pragma once

#include <NGIN/Memory/IAllocator.hpp>
#include <NGIN/Containers/Vector.hpp>
#include <utility>
#include <stdexcept>


namespace NGIN::Memory
{
    template <typename AllocatorType, Size InitialSize>
        requires std::is_base_of_v<IAllocator, AllocatorType>
    class GrowingAllocator : public IAllocator
    {
    public:
        GrowingAllocator()
        {
            Grow();
        }


        GrowingAllocator(GrowingAllocator&& other) noexcept
            : allocators(std::move(other.allocators)), newSize(other.newSize)
        {
        }

        GrowingAllocator& operator=(GrowingAllocator&& other) noexcept
        {
            allocators = std::move(other.allocators);
            newSize = other.newSize;
            return *this;
        }

        void* Allocate(Size size, Size alignment = alignof(std::max_align_t)) override
        {
            for (auto& allocator : allocators)
            {
                void* ptr = allocator.Allocate(size, alignment);
                if (ptr)
                    return ptr;
            }

            do
            {
                Grow();
                void* ptr = allocators.back().Allocate(size, alignment);
                if (ptr)
                    return ptr;
            }
            while (true);
        }

        void Deallocate(void* ptr) override
        {
            for (auto& allocator : allocators)
            {
                if (allocator.Owns(ptr))
                {
                    allocator.Deallocate(ptr);
                    return;
                }
            }

            throw std::runtime_error("Cannot deallocate a non-owned pointer");
        }

        void Reset() override
        {
            for (auto& allocator : allocators)
                allocator.Reset();
        }


        bool Owns(const void* ptr) override
        {
            for (auto& allocator : allocators)
            {
                if (allocator.Owns(ptr))
                    return true;
            }

            return false;
        }

    private:
        void Grow()
        {
            allocators.emplace_back(newSize);
            newSize *= 2;
        }


        Vector<AllocatorType> allocators;
        Size newSize = InitialSize;
    };
}
