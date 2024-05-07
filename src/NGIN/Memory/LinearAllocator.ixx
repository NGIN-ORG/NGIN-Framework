module;
#include <stdlib.h>


export module NGIN.Memory:LinearAllocator;

export import :IAllocator;
export import NGIN.Types;

import std;
import :Scope;
import :AlignmentUtils;

namespace NGIN::Memory
{
    /// @class LinearAllocator
    /// @brief A fast allocator that allocates memory by incrementing a pointer.
    /// @note This allocator does not support deallocation of memory. Only resetting the allocator is supported.
    export class LinearAllocator : public IAllocator
    {
    public:
        ~LinearAllocator() override = default;

        /// @brief Constructs a linear allocator with a given size.
        /// @param sizeInBytes The total size of the buffer.
        /// @TODO Buffer should be aligned to the maximum alignment.
        LinearAllocator(Size sizeInBytes)
            : buffer(nullptr), totalSize(sizeInBytes)
        {
#if defined(NGIN_PLATFORM_WINDOWS)
            void* alignedMemory = _aligned_malloc(sizeInBytes, alignof(std::max_align_t));
#else
            void* alignedMemory;
            posix_memalign(&alignedMemory, alignof(std::max_align_t), sizeInBytes);
#endif
            // Allocate the buffer with maximum alignment

            // Check if allocation was successful
            if (!alignedMemory)
            {
                throw std::bad_alloc();// or handle the allocation failure appropriately
            }


#if defined(NGIN_PLATFORM_WINDOWS)
            buffer.reset(static_cast<Byte*>(alignedMemory), [](Byte* ptr) { _aligned_free(ptr); });
#else
            buffer.reset(static_cast<Byte*>(alignedMemory), [](Byte* ptr) { free(ptr); });
#endif

            currentPtr = buffer.get();// Set currentPtr to the start of the aligned buffer

            bool isAligned = (reinterpret_cast<std::uintptr_t>(currentPtr) % alignof(std::max_align_t)) == 0;
        }

        /// @brief Copy constructor is deleted because LinearAllocators cannot share owned memory.
        LinearAllocator(const LinearAllocator& other) noexcept = delete;

        /// @brief Copy assignment operator is deleted because LinearAllocators cannot share the owned memory.
        LinearAllocator& operator=(const LinearAllocator& other) noexcept = delete;

        /// @brief Move constructor.
        LinearAllocator(LinearAllocator&& other) noexcept
            : buffer(std::move(other.buffer)), currentPtr(other.currentPtr), totalSize(other.totalSize)
        {
            other.currentPtr = nullptr;
            other.totalSize = 0;
        }

        /// @brief Move assignment operator.
        LinearAllocator& operator=(LinearAllocator&& other) noexcept
        {
            if (this != &other)
            {
                buffer = std::move(other.buffer);
                currentPtr = other.currentPtr;
                totalSize = other.totalSize;
                other.currentPtr = nullptr;
                other.totalSize = 0;
            }
            return *this;
        }

        /// @brief Allocates memory by incrementing a pointer.
        /// @param size The size of the memory to allocate, in bytes.
        /// @param alignment The alignment of the memory to allocate, in bytes.
        /// @return A pointer to the allocated memory.
        [[nodiscard]] void* Allocate(Size size, Size alignment = alignof(std::max_align_t)) override
        {
            // Calculate the adjustment needed to keep the data correctly aligned.
            const Size adjustment = AlignForwardAdjustment(currentPtr, alignment);

            // If the allocator is out of memory, return nullptr.
            if (currentPtr + size + adjustment > buffer.get() + totalSize)
                return nullptr;
            Byte* alignedAddress = currentPtr + adjustment;// Calculate the aligned address.
            currentPtr = alignedAddress + size;            // Move the current pointer to the next available address.
            return alignedAddress;     // Return the aligned address.
        }

        /// @brief This function is not supported by the linear allocator and will always throw
        /// @details Deallocating memory from a linear allocator is not supported, because the allocator does not keep track of previous allocations.
        /// @param ptr The pointer to deallocate.
        /// @throw std::runtime_error
        void Deallocate(void* ptr) override
        {
            // Deallocating memory from a linear allocator is not supported.
            throw std::runtime_error("Deallocating memory from a linear allocator is not supported.");
        }

        /// @brief Resets the allocator to its initial state.
        /// @details    This function resets the current pointer to the start of the buffer.
        ///             Accessing any objects previously allocated from the allocator will be undefined behaviour
        /// @note This function does not destruct any objects allocated from the allocator. @see NGIN::Memory::IAllocator::Delete
        void Reset() override
        {
            currentPtr = buffer.get();
        }

        /// @brief Checks if the allocator owns the given pointer.
        /// @details The allocator owns the pointer if the pointer is within the buffer.
        /// @param ptr The pointer to check.
        /// @return True if the allocator owns the pointer, otherwise false.
        [[nodiscard]] bool Owns(const void* ptr) override
        {
            const Byte* const start = buffer.get();
            return ptr >= start && ptr < start + totalSize;
        }

    private:
        /// @brief The buffer owned by the allocator.
        Scope<Byte[]> buffer;
        /// @brief The current offset in the buffer.
        Byte* currentPtr;
        /// @brief The size of the buffer, in bytes.
        Size totalSize;
    };

}// namespace NGIN::Memory
