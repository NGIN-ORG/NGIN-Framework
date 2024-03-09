//
// Created by Maximiliam Berggren on 03/03/2024.
//

export module NGIN.Memory:AlignmentUtils;

export import NGIN.Types;

namespace NGIN::Memory
{
    /// @brief Returns the number of bytes required to align the given pointer to the given alignment.
    /// @param ptr The pointer to align.
    /// @param alignment The alignment to use.
    /// @return The number of bytes required to align the pointer.
    export [[nodiscard]] inline Size AlignForwardAdjustment(const void* ptr, const Size alignment)
    {
        return (alignment - (reinterpret_cast<Size>(ptr) % alignment)) % alignment;
    }

    /// @brief Returns the number of bytes required to align the given address to the given alignment.
    /// @param address The address to align.
    /// @param alignment The alignment to use.
    /// @return The number of bytes required to align the address.
    export [[nodiscard]] inline Size AlignForwardAdjustment(const Size address, const Size alignment)
    {
        return (alignment - (address % alignment)) % alignment;
    }

    /// @brief Returns a aligned pointer based on the given pointer and power of two alignment.
    /// @param ptr The pointer to align.
    /// @param alignment The alignment to use.
    /// @return The aligned pointer.
    /// @note The alignment must be a power of two.
    export [[nodiscard]] inline void* AlignPtr(void* ptr, Size alignment)
    {
        return reinterpret_cast<void*>((reinterpret_cast<Size>(ptr) + (alignment - 1)) & ~(alignment - 1));
    }
}// namespace NGIN::Memory