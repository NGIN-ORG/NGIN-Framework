export module NGIN.Time:Ratio;

export import NGIN.Types;
export import std;

export namespace NGIN::Time
{
    template <Size Numerator, Size Denominator>
    struct Ratio
    {
        static_assert(Denominator != 0, "Denominator cannot be zero in a Ratio.");

        using STDRatioType = std::ratio<Numerator, Denominator>;

        static constexpr Int64 numerator = Numerator;
        static constexpr Int64 denominator = Denominator;
        static constexpr F64 value = static_cast<F64>(Numerator) / static_cast<F64>(Denominator);
        static constexpr F64 inverse = static_cast<F64>(Denominator) / static_cast<F64>(Numerator);
    };
}// namespace NGIN::Time
