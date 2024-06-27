#include <NGIN/Memory/Alignment.hpp>
#include <NGIN/Memory/FreeListAllocator.hpp>
#include <stdexcept>

#include <limits>

namespace NGIN::Memory
{
    FreeListAllocator::FreeListAllocator(Size totalSize)
    {

#if defined(NGIN_PLATFORM_WINDOWS)
        startPtr = _aligned_malloc(totalSize, alignof(std::max_align_t));
#else
        void* alignedMemory;
        posix_memalign(&alignedMemory, alignof(std::max_align_t), totalSize);
        startPtr = alignedMemory;
#endif
        if (startPtr == nullptr)
            throw std::runtime_error("Could not allocate memory!");
        this->totalSize      = totalSize;
        firstFreeBlock       = static_cast<FreeBlock*>(startPtr);
        firstFreeBlock->size = totalSize;
        firstFreeBlock->next = nullptr;
    }

    FreeListAllocator::~FreeListAllocator()
    {
        {
#if defined(NGIN_PLATFORM_WINDOWS)
            _aligned_free(startPtr);
#else
            free(startPtr);
#endif
        }
    }

    FreeListAllocator::FreeListAllocator(FreeListAllocator&& other) noexcept
        : totalSize(other.totalSize), startPtr(other.startPtr), firstFreeBlock(other.firstFreeBlock)
    {
        other.startPtr       = nullptr;
        other.firstFreeBlock = nullptr;
        other.totalSize      = 0;
    }

    FreeListAllocator& FreeListAllocator::operator=(FreeListAllocator&& other) noexcept
    {
        totalSize      = other.totalSize;
        startPtr       = other.startPtr;
        firstFreeBlock = other.firstFreeBlock;

        other.startPtr       = nullptr;
        other.firstFreeBlock = nullptr;
        other.totalSize      = 0;

        return *this;
    }

    void* FreeListAllocator::Allocate(Size size, const Size alignment)
    {

        size = size < sizeof(FreeBlock) ? sizeof(FreeBlock) : size;


        FreeBlock* previousBlock = nullptr;
        FreeBlock* freeBlock     = FindFreeBlock(size, alignment, previousBlock);

        if (freeBlock == nullptr)
            return nullptr;

        // Calculate adjustment needed to keep the block aligned
        Size adjustment      = AlignForwardAdjustment(reinterpret_cast<void*>(freeBlock), alignment);
        Size totalSizeNeeded = size + adjustment;

        // Check if we should split the block
        if (freeBlock->size - totalSizeNeeded > sizeof(FreeBlock))
        {
            FreeBlock* newBlock = reinterpret_cast<FreeBlock*>(reinterpret_cast<Size>(freeBlock) + totalSizeNeeded);
            newBlock->size      = freeBlock->size - totalSizeNeeded;
            newBlock->next      = freeBlock->next;

            freeBlock->size = totalSizeNeeded;

            // Updating the linked list
            if (previousBlock != nullptr)
                previousBlock->next = newBlock;
            else
                firstFreeBlock = newBlock;
        }
        else
        {
            // No splitting, remove the block from the free list
            if (previousBlock != nullptr)
                previousBlock->next = freeBlock->next;
            else
                firstFreeBlock = freeBlock->next;
        }

        // The return pointer is the start of the allocated block, aligned
        return reinterpret_cast<void*>(reinterpret_cast<Size>(freeBlock) + adjustment);
    }

    void FreeListAllocator::Deallocate(void* ptr)
    {
        FreeBlock* newFreeBlock = static_cast<FreeBlock*>(ptr);
        newFreeBlock->next      = firstFreeBlock;
        firstFreeBlock          = newFreeBlock;
    }

    void FreeListAllocator::Reset()
    {
        firstFreeBlock       = static_cast<FreeBlock*>(startPtr);
        firstFreeBlock->size = totalSize;
        firstFreeBlock->next = nullptr;
    }

    bool FreeListAllocator::Owns(const void* ptr)
    {
        return ptr >= startPtr && ptr < reinterpret_cast<void*>(reinterpret_cast<Size>(startPtr) + totalSize);
    }

    FreeBlock* FreeListAllocator::FindFreeBlock(Size size, const Size alignment, FreeBlock*& previousBlock) const
    {
        size = size < sizeof(FreeBlock) ? sizeof(FreeBlock) : size;

        FreeBlock* current = firstFreeBlock;
        FreeBlock* prev    = nullptr;

        while (current != nullptr)
        {
            // Calculate the adjustment needed to meet the alignment requirements
            Size adjustment      = AlignForwardAdjustment(reinterpret_cast<void*>(current), alignment);
            Size totalSizeNeeded = size + adjustment;

            if (current->size >= totalSizeNeeded)
            {
                if (previousBlock != nullptr)
                    previousBlock = prev;
                return current;
            }

            prev    = current;
            current = current->next;
        }

        if (previousBlock != nullptr)
            previousBlock = nullptr;
        return nullptr;
    }


}// namespace NGIN::Memory