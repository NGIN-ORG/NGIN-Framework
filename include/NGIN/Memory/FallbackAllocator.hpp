
#pragma once
#include <NGIN/Memory/IAllocator.hpp>
#include <utility>

namespace NGIN::Memory
{
    template <typename PrimaryT, typename FallbackT>
        requires std::is_base_of_v<IAllocator, PrimaryT> and std::is_base_of_v<IAllocator, FallbackT>
    class FallbackAllocator : public IAllocator
    {
    public:
        FallbackAllocator(Size totalSize = 1024)
            : primary(totalSize), fallback(totalSize)
        {
        }

        FallbackAllocator(PrimaryT&& primary, FallbackT&& fallback)
            : primary(std::move(primary)), fallback(std::move(fallback))
        {
        }

        FallbackAllocator(FallbackAllocator&& other) noexcept
            : primary(std::move(other.primary)), fallback(std::move(other.fallback))
        {
        }

        FallbackAllocator& operator=(FallbackAllocator&& other) noexcept
        {
            primary = std::move(other.primary);
            fallback = std::move(other.fallback);
            return *this;
        }

        void* Allocate(Size size, Size alignment = alignof(std::max_align_t)) override
        {
            void* ptr = primary.Allocate(size, alignment);
            if (!ptr)
                ptr = fallback.Allocate(size, alignment);
            return ptr;
        }

        void Deallocate(void* ptr) override
        {
            if (primary.Owns(ptr))
                primary.Deallocate(ptr);
            else if (fallback.Owns(ptr))
                fallback.Deallocate(ptr);
            else
                throw std::runtime_error("Cannot deallocate a non-owned pointer");
        }

        void Reset() override
        {
            primary.Reset();
            fallback.Reset();
        }


        bool Owns(const void* ptr) override
        {
            return primary.Owns(ptr) || fallback.Owns(ptr);
        }

    private:
        PrimaryT primary;
        FallbackT fallback;
    };
}
