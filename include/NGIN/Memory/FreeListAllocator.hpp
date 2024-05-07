#pragma once
#include <NGIN/Memory/IAllocator.hpp>

#include <stdlib.h>


namespace NGIN::Memory
{
    struct FreeBlock
    {
        Size size;
        FreeBlock* next;
    };

    class FreeListAllocator : public IAllocator
    {
    public:
        FreeListAllocator(Size totalSize = 1024);

        ~FreeListAllocator() override;

        FreeListAllocator(FreeListAllocator&& other) noexcept;


        FreeListAllocator& operator=(FreeListAllocator&& other) noexcept;

        void* Allocate(Size size, Size alignment = alignof(std::max_align_t)) override;

        void Deallocate(void* ptr) override;

        void Reset() override;

        bool Owns(const void* ptr) override;
        Size totalSize;

    private:
        FreeBlock* FindFreeBlock(Size size, Size alignment, FreeBlock*& previousBlock) const;

        void* startPtr;
        FreeBlock* firstFreeBlock;
    };
} // namespace NGIN::Memory
