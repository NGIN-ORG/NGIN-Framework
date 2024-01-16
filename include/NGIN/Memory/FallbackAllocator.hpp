#pragma once
#include <NGIN/Common/Defines.hpp>
#include <NGIN/Memory/IAllocator.hpp>

namespace NGIN::Memory
{

    /// @class FallbackAllocator
    /// @brief A composite allocator that uses a primary allocator and falls back to a secondary allocator if the primary fails.
    ///
    /// FallbackAllocator is a type of allocator that attempts to allocate memory using a primary allocator, and if that fails,
    /// it tries to allocate memory using a fallback allocator. This can be useful in situations where you have a fast,
    /// limited-size allocator (the primary) and a slower, unlimited-size allocator (the fallback).
    ///
    /// @tparam PrimaryAllocatorT The type of the primary allocator.
    /// @tparam FallbackAllocatorT The type of the fallback allocator.
    template<IsAllocator PrimaryAllocatorT, IsAllocator FallbackAllocatorT>
    class FallbackAllocator : public IAllocator
    {
    public:
        /// @brief Constructs a FallbackAllocator with the specified primary and fallback allocators.
        FallbackAllocator(PrimaryAllocatorT&& primaryAllocator, FallbackAllocatorT&& fallbackAllocator) noexcept;

        /// @brief Default destructor.
        ~FallbackAllocator() = default;

        /// @brief Copy constructor is deleted because FallbackAllocators should not be copied.
        FallbackAllocator(const FallbackAllocator& other) noexcept = delete;

        /// @brief Copy assignment operator is deleted because FallbackAllocators should not be copied.
        FallbackAllocator& operator=(const FallbackAllocator& other) noexcept = delete;

        /// @brief Move constructor.
        FallbackAllocator(FallbackAllocator&& other) noexcept;

        /// @brief Move assignment operator.
        FallbackAllocator& operator=(FallbackAllocator&& other);

        /// @brief Allocates a block of memory of the specified size and alignment.
        /// @details First tries to allocate from the primary allocator, and if that fails, tries the fallback allocator.
        Void* Allocate(Size size, Size alignment = alignof(std::max_align_t), const std::source_location& location = std::source_location::current()) override;

        /// @brief Deallocates a block of memory.
        /// @details Deallocates from the primary allocator if it owns the block, otherwise deallocates from the fallback allocator.
        Void Deallocate(void* ptr) override;

        /// @brief Checks if the specified pointer was allocated by this allocator.
        /// @details Returns true if either the primary allocator or the fallback allocator owns the block.
        Bool Owns(void* ptr) const override;

    private:
        /// @brief The primary allocator.
        PrimaryAllocatorT primaryAllocator;

        /// @brief The fallback allocator.
        FallbackAllocatorT fallbackAllocator;
    };

    // INLINE IMPLEMENTATION

    template<IsAllocator PrimaryAllocatorT, IsAllocator FallbackAllocatorT>
    inline FallbackAllocator<PrimaryAllocatorT, FallbackAllocatorT>::FallbackAllocator(PrimaryAllocatorT&& primaryAllocator, FallbackAllocatorT&& fallbackAllocator) noexcept
        : primaryAllocator(std::move(primaryAllocator)), fallbackAllocator(std::move(fallbackAllocator))
    {
    }

    template<IsAllocator PrimaryAllocatorT, IsAllocator FallbackAllocatorT>
    inline FallbackAllocator<PrimaryAllocatorT, FallbackAllocatorT>::FallbackAllocator(FallbackAllocator&& other) noexcept
        : primaryAllocator(std::move(other.primaryAllocator)), fallbackAllocator(std::move(other.fallbackAllocator))
    {
    }
    template<IsAllocator PrimaryAllocatorT, IsAllocator FallbackAllocatorT>
    inline FallbackAllocator& FallbackAllocator<PrimaryAllocatorT, FallbackAllocatorT>::operator=(FallbackAllocator&& other)
    {
        if (this != &other)
        {
            primaryAllocator = std::move(other.primaryAllocator);
            fallbackAllocator = std::move(other.fallbackAllocator);
        }
        return *this;
    }


    template<IsAllocator PrimaryAllocatorT, IsAllocator FallbackAllocatorT>
    inline Void* FallbackAllocator<PrimaryAllocatorT, FallbackAllocatorT>::Allocate(Size size, Size alignment, const std::source_location& location)
    {
        Void* ptr = primaryAllocator.Allocate(size, alignment, location);
        if (ptr == nullptr)
            ptr = fallbackAllocator.Allocate(size, alignment, location);
        return ptr;
    }

    template<IsAllocator PrimaryAllocatorT, IsAllocator FallbackAllocatorT>
    inline Void FallbackAllocator<PrimaryAllocatorT, FallbackAllocatorT>::Deallocate(void* ptr)
    {
        if (primaryAllocator.Owns(ptr))
            primaryAllocator.Deallocate(ptr);
        else if (fallbackAllocator.Owns(ptr))
            fallbackAllocator.Deallocate(ptr);
        else
            NGIN_ERROR("Cannot deallocate pointer because it was not allocated by this allocator.");
    }

    template<IsAllocator PrimaryAllocatorT, IsAllocator FallbackAllocatorT>
    inline Bool FallbackAllocator<PrimaryAllocatorT, FallbackAllocatorT>::Owns(void* ptr) const override
    {
        return primaryAllocator.Owns(ptr) || fallbackAllocator.Owns(ptr);
    }

}// namespace NGIN::Memory