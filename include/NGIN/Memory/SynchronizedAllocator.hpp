#pragma once

#include <NGIN/Memory/IAllocator.hpp>
#include <mutex>
#include <utility>
#include <stdexcept>


namespace NGIN::Memory
{
    template <typename AllocatorType>
        requires std::is_base_of_v<IAllocator, AllocatorType>
    class SynchronizedAllocator : public IAllocator
    {
    public:
        SynchronizedAllocator(Size totalSize = 1024)
            : allocator()
        {
        }

        SynchronizedAllocator(AllocatorType&& allocator)
            : allocator(std::move(allocator))
        {
        }

        SynchronizedAllocator(SynchronizedAllocator&& other) noexcept
            : allocator(std::move(other.allocator))
        {
        }

        SynchronizedAllocator& operator=(SynchronizedAllocator&& other) noexcept
        {
            allocator = std::move(other.allocator);
            return *this;
        }

        void* Allocate(Size size, Size alignment = alignof(std::max_align_t)) override
        {
            std::lock_guard<std::mutex> lock(mutex);
            return allocator.Allocate(size, alignment);
        }

        void Deallocate(void* ptr) override
        {
            std::lock_guard<std::mutex> lock(mutex);
            allocator.Deallocate(ptr);
        }

        void Reset() override
        {
            std::lock_guard<std::mutex> lock(mutex);
            allocator.Reset();
        }

        bool Owns(const void* ptr) override
        {
            std::lock_guard<std::mutex> lock(mutex);
            return allocator.Owns(ptr);
        }

    private:
        AllocatorType allocator;
        std::mutex mutex;
    };
}
