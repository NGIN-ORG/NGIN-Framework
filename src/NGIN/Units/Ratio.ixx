export module NGIN.Units:Ratio;

export import NGIN.Types;
export import std;

export namespace NGIN
{
    template<Size Numerator, Size Denominator>
    struct Ratio
    {
        using STDRatioType = std::ratio<Numerator, Denominator>;
        using ReducedRatioType = Ratio<Numerator / std::gcd(Numerator, Denominator), Denominator / std::gcd(Numerator, Denominator)>;

        static constexpr Int64 numerator = Numerator;
        static constexpr Int64 denominator = Denominator;
        static constexpr F64 value = static_cast<F64>(Numerator) / static_cast<F64>(Denominator);
        static constexpr F64 inverse = static_cast<F64>(Denominator) / static_cast<F64>(Numerator);
    };
}// namespace NGIN::Time