module;
#include <stdlib.h>


export module NGIN.Memory:FreeListAllocator;

import :IAllocator;
import :AlignmentUtils;
import std;

namespace NGIN::Memory
{

    struct FreeBlock
    {
        Size size;
        FreeBlock* next;
    };

    export class FreeListAllocator : public IAllocator
    {
    public:
        FreeListAllocator(Size totalSize)
        {

            #if defined(NGIN_PLATFORM_WINDOWS)
            startPtr = _aligned_malloc(totalSize, alignof(std::max_align_t));
#else
            void* alignedMemory;
            posix_memalign(&alignedMemory, alignof(std::max_align_t), totalSize);
            startPtr = alignedMemory;
#endif
            this->totalSize = totalSize;
            firstFreeBlock = static_cast<FreeBlock*>(startPtr);
            firstFreeBlock->size = totalSize;
            firstFreeBlock->next = nullptr;
        }

        ~FreeListAllocator() override
        {
#if defined(NGIN_PLATFORM_WINDOWS)
            _aligned_free(startPtr);
#else
            free(startPtr);
#endif
        }

        void* Allocate(Size size, Size alignment = alignof(std::max_align_t)) override
        {
            FreeBlock* prevFreeBlock = nullptr;
            FreeBlock* freeBlock = firstFreeBlock;

            while (freeBlock != nullptr)
            {
                const Size adjustment = AlignForwardAdjustment(freeBlock, alignment);
                Size totalSize = size + adjustment;

                if (freeBlock->size < totalSize)
                {
                    prevFreeBlock = freeBlock;
                    freeBlock = freeBlock->next;
                    continue;
                }

                if (freeBlock->size - totalSize <= sizeof(FreeBlock))
                {
                    totalSize = freeBlock->size;

                    if (prevFreeBlock != nullptr)
                    {
                        prevFreeBlock->next = freeBlock->next;
                    } else
                    {
                        firstFreeBlock = freeBlock->next;
                    }
                } else
                {
                    FreeBlock* nextBlock = reinterpret_cast<FreeBlock*>(reinterpret_cast<Size>(freeBlock) + totalSize);
                    nextBlock->size = freeBlock->size - totalSize;
                    nextBlock->next = freeBlock->next;

                    if (prevFreeBlock != nullptr)
                    {
                        prevFreeBlock->next = nextBlock;
                    } else
                    {
                        firstFreeBlock = nextBlock;
                    }
                }

                return reinterpret_cast<void*>(reinterpret_cast<Size>(freeBlock) + adjustment);
            }

            return nullptr;// No suitable free block found
        }

        void Deallocate(void* ptr) override
        {
            FreeBlock* newFreeBlock = static_cast<FreeBlock*>(ptr);
            newFreeBlock->next = firstFreeBlock;
            firstFreeBlock = newFreeBlock;
        }

        void Reset() override
        {
            firstFreeBlock = static_cast<FreeBlock*>(startPtr);
            firstFreeBlock->size = totalSize;
            firstFreeBlock->next = nullptr;
        }

        bool Owns(const void* ptr) override
        {
            return ptr >= startPtr && ptr < reinterpret_cast<void*>(reinterpret_cast<Size>(startPtr) + totalSize);
        }

    private:
        void* startPtr;
        Size totalSize;
        FreeBlock* firstFreeBlock;
    };

}// namespace NGIN::Memory