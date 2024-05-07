#pragma once

#include <NGIN/Common/Defines.hpp>
#include <NGIN/Types/Primitives.hpp>

namespace NGIN::Memory
{
    /// @brief Returns the number of bytes required to align the given pointer to the given alignment.
    /// @param ptr The pointer to align.
    /// @param alignment The alignment to use.
    /// @return The number of bytes required to align the pointer.
    NGIN_API [[nodiscard]] inline Size AlignForwardAdjustment(const void* ptr, const Size alignment) { return (alignment - (reinterpret_cast<Size>(ptr) % alignment)) % alignment; }

    /// @brief Returns the number of bytes required to align the given address to the given alignment.
    /// @param address The address to align.
    /// @param alignment The alignment to use.
    /// @return The number of bytes required to align the address.
    NGIN_API [[nodiscard]] inline Size AlignForwardAdjustment(const Size address, const Size alignment) { return (alignment - (address % alignment)) % alignment; }

    /// @brief Returns a aligned pointer based on the given pointer and power of two alignment.
    /// @param ptr The pointer to align.
    /// @param alignment The alignment to use.
    /// @return The aligned pointer.
    /// @note The alignment must be a power of two.
    NGIN_API [[nodiscard]] inline void* AlignPtr(void* ptr, Size alignment) { return reinterpret_cast<void*>((reinterpret_cast<Size>(ptr) + (alignment - 1)) & ~(alignment - 1)); }
}