#pragma once
#include <NGIN/Common/Types/Primitive.hpp>
#include <cstddef>

namespace NGIN::Memory::Internal
{
    /**
     * @brief Aligns a pointer to the given alignment.
     *
     * @param ptr The pointer to align.
     * @param alignment The alignment to use.
     * @return The aligned pointer.
     */
    [[nodiscard]] inline Void* AlignPtr(Void* ptr, Size alignment)
    {
        return reinterpret_cast<Void*>((reinterpret_cast<Size>(ptr) + (alignment - 1)) & ~(alignment - 1));
    }

    /**
     * @brief Returns true if the given pointer is aligned to the given alignment.
     *
     * @param ptr The pointer to check.
     * @param alignment The alignment to check.
     * @return True if the pointer is aligned, false otherwise.
     */
    [[nodiscard]] inline Bool IsPtrAligned(Void* ptr, Size alignment)
    {
        return reinterpret_cast<Size>(ptr) % alignment == 0;
    }

    /**
     * @brief Returns the number of bytes required to align the given pointer to the given alignment.
     *
     * @param ptr The pointer to align.
     * @param alignment The alignment to use.
     * @return The number of bytes required to align the pointer.
     */
    [[nodiscard]] inline Size GetAlignmentPadding(Void* ptr, Size alignment)
    {
        return (alignment - (reinterpret_cast<Size>(ptr) % alignment)) % alignment;
    }
}// namespace NGIN::Memory::Internal