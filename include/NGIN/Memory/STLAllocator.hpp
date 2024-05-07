#pragma once
#include <NGIN/Memory/Mallocator.hpp>
#include <NGIN/Memory/SynchronizedAllocator.hpp>
#include <NGIN/Memory/GrowingAllocator.hpp>

#include <memory> // For std::allocator_traits

namespace NGIN::Memory
{
    /// @brief An STL allocator is a wrapper around NGIN allocators that allows them to be used with the STL containers.
    /// @details The STLAllocator takes the AllocatorType and Wraps it in a SynchronizedAllocator and GrowingAllocator. This allows the allocator to be thread safe and grow in size if it runs out of memory.
    ///
    template <typename T, typename AllocatorType = Mallocator, size_t InitialSize = 1024>
    class STLAllocator
    {
    public:
        using FullAllocatorType = SynchronizedAllocator<GrowingAllocator<AllocatorType, InitialSize>>;
        using value_type = T;
        using pointer = T*;
        using const_pointer = const T*;
        using void_pointer = void*;
        using const_void_pointer = const void*;
        using size_type = std::size_t;
        using difference_type = std::ptrdiff_t;
        using propagate_on_container_move_assignment = std::true_type;
        using is_always_equal = std::false_type;

        template <typename U>
        struct rebind
        {
            using other = STLAllocator<U, AllocatorType>;
        };

        STLAllocator() : allocator_(getAllocatorInstance())
        {
        }

        template <typename U>
        STLAllocator(const STLAllocator<U, AllocatorType>&) : allocator_(getAllocatorInstance())
        {
        }

        T* allocate(std::size_t numObjects)
        {
            return static_cast<T*>(allocator_->Allocate(numObjects * sizeof(T), alignof(T)));
        }

        void deallocate(T* p, std::size_t numObjects)
        {
            allocator_->Deallocate(p);
        }

        static FullAllocatorType* getAllocatorInstance()
        {
            static FullAllocatorType allocatorInstance;
            return &allocatorInstance;
        }

    private:
        FullAllocatorType* allocator_;
    };

    template <typename T, typename U, typename AllocatorType>
    bool operator==(const STLAllocator<T, AllocatorType>&, const STLAllocator<U, AllocatorType>&)
    {
        return true; // All allocators of this type are interchangeable
    }

    template <typename T, typename U, typename AllocatorType>
    bool operator!=(const STLAllocator<T, AllocatorType>& a, const STLAllocator<U, AllocatorType>& b)
    {
        return !(a == b);
    }
} // namespace NGIN::Memory
