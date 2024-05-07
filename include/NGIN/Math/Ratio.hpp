#pragma once

#include <NGIN/Common/Defines.hpp>
#include <NGIN/Types/Primitives.hpp>
#include <ratio>
#include <numeric>

namespace NGIN::Math
{
    ///@brief Represents a ratio of two integers.
    ///@tparam Numerator The numerator of the ratio.
    ///@tparam Denominator The denominator of the ratio.
    ///@note Denominator cannot be zero.
    template <Size Numerator, Size Denominator>
    struct Ratio
    {
        static_assert(Denominator != 0, "Denominator cannot be zero in a Ratio.");

        ///The standard ratio type.
        using STLRatioType = std::ratio<Numerator, Denominator>;
        using GCD = Ratio<Numerator / std::gcd(Numerator, Denominator), Denominator / std::gcd(Numerator, Denominator)>;

        static constexpr Size NUMERATOR = Numerator;
        static constexpr Size DENOMINATOR = Denominator;
        static constexpr F64 VALUE = static_cast<F64>(Numerator) / static_cast<F64>(Denominator);
        static constexpr F64 INVERSE = static_cast<F64>(Denominator) / static_cast<F64>(Numerator);


        template <Size N2, Size D2>
        using Multiply = Ratio<(NUMERATOR * N2) / std::gcd(NUMERATOR * N2, DENOMINATOR * D2),
                               (DENOMINATOR * D2) / std::gcd(NUMERATOR * N2, DENOMINATOR * D2)>;

        template <Size N2, Size D2>
        using Divide = Ratio<(NUMERATOR * D2) / std::gcd(NUMERATOR * D2, DENOMINATOR * N2),
                             (DENOMINATOR * N2) / std::gcd(NUMERATOR * D2, DENOMINATOR * N2)>;

        template <Size N2, Size D2>
        using Add = Ratio<(NUMERATOR * D2 + N2 * DENOMINATOR) / std::gcd(
                              NUMERATOR * D2 + N2 * DENOMINATOR, DENOMINATOR * D2),
                          (DENOMINATOR * D2) / std::gcd(NUMERATOR * D2 + N2 * DENOMINATOR, DENOMINATOR * D2)>;

        template <Size N2, Size D2>
        using Subtract = Ratio<(NUMERATOR * D2 - N2 * DENOMINATOR) / std::gcd(
                                   NUMERATOR * D2 - N2 * DENOMINATOR, DENOMINATOR * D2),
                               (DENOMINATOR * D2) / std::gcd(NUMERATOR * D2 - N2 * DENOMINATOR, DENOMINATOR * D2)>;
    };
} // namespace NGIN
