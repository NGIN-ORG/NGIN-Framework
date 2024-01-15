#include <NGIN/Memory/LinearAllocator.hpp>
#include <NGIN/Memory/Internal/Alignment.hpp>

namespace NGIN::Memory
{

    LinearAllocator::LinearAllocator(Size sizeBytes)
        : memory(CreateScope<Byte[]>(sizeBytes)), current(memory.get()), end(memory.get() + sizeBytes)
    {
    }

    LinearAllocator::LinearAllocator(LinearAllocator&& other) noexcept
        : memory(std::move(other.memory)), current(std::move(other.current)), end(std::move(other.end))
    {
        other.current = nullptr;
        other.end = nullptr;
    }


    LinearAllocator& LinearAllocator::operator=(LinearAllocator&& other) noexcept
    {
        if (this != &other)
        {
            // Release any resources that *this may hold
            memory.reset();

            memory = std::move(other.memory);
            current = other.current;
            end = other.end;

            other.current = nullptr;
            other.end = nullptr;
        }

        return *this;
    }

    Void* LinearAllocator::Allocate(Size size, Size alignment, const std::source_location& location)
    {
        const Size padding = Internal::GetAlignmentPadding(current, alignment);
        if (current + padding + size > end)
            return nullptr;

        Void* alignedPtr = Internal::AlignPtr(current + padding, alignment);
        current = static_cast<Byte*>(alignedPtr) + size;
        return alignedPtr;
    }

    Void LinearAllocator::Deallocate(void* ptr)
    {
        NGIN_ERROR("Cannot deallocate from a linear allocator.");
    }

    Bool LinearAllocator::Owns(void* ptr) const
    {
        UIntPtr startAddress = reinterpret_cast<UIntPtr>(memory.get());
        UIntPtr endAddress = reinterpret_cast<UIntPtr>(end);
        UIntPtr targetAddress = reinterpret_cast<UIntPtr>(ptr);

        return targetAddress >= startAddress && targetAddress < endAddress;
    }

    void LinearAllocator::Reset()
    {
        current = memory.get();
    }

}// namespace NGIN::Memory